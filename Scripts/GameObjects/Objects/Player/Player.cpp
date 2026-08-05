/*
 * FileName:     Player.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/08/05
 *
 * プレイヤー
 */

#include "Pch.h"
#include "Player.h"

#include "Scripts/Commons/GameObjects/GameObject.h"
#include "Scripts/Commons/GameObjects/IGameObjectFinder.h"
#include "Scripts/Commons/Components/Transform.h"
#include "Scripts/Commons/Colliders/BoxCollider.h"
#include "Scripts/Commons/Systems/JsonSerializer.h"

// コンストラクタ
Player::Player(const ComponentDesc& desc)
	: Component{ desc }
	, m_params{}
	, m_moveVelocity{}
	, m_fallSpeed{}
	, m_rotation{}
	, m_fallState{}
	, m_coyoteTime{}
	, m_pTransform{ GetPOwner()->GetNullReferences<Transform>() }
	, m_pBoxCollider{ GetPOwner()->GetNullReferences<Colliders::BoxCollider>() }
	, m_pCameraScreen{ GetPOwner()->GetNullReferences<Renderings::CameraScreen<Camera::EulerTargetCamera>>() }
{
}

// 初期化処理
void Player::Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder)
{
	m_pTransform = GetPOwner()->GetComponent<Transform>();
	m_rotation.SetValue(m_pTransform->GetRotation());

	m_pBoxCollider = GetPOwner()->GetComponent<Colliders::BoxCollider>();

	float fallMaxSpeed = m_fallSpeed.GetMax();
	float coyoteTime = m_coyoteTime.GetMax();

	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_params.moveMaxSpeed, "MoveMaxSpeed");
	serializer.AddParameter(&m_params.moveAcceleration, "MoveAcceleration");
	serializer.AddParameter(&fallMaxSpeed, "FallMaxSpeed");
	serializer.AddParameter(&m_params.fallAcceleration, "FallAcceleration");
	serializer.AddParameter(&m_params.cameraVelocityCoefficient, "CameraVelocityCoefficient");
	serializer.AddParameter(&coyoteTime, "CoyoteTime");
	serializer.AddParameter(&m_pCameraScreen, "CameraScreen");
	serializer.Load(json);

	m_fallSpeed.Initialize(0.0f, 0.0f, fallMaxSpeed);

	m_fallState = FallState::OnGround;
	m_coyoteTime.Initialize(0.0f, 0.0f, coyoteTime);
}

// 更新処理
void Player::Update(float elapsedTime, const Math::Vector3& move)
{
	// カメラのY軸回転
	Math::Quaternion cameraRotation = Math::Quaternion::CreateFromAxisAngle(Math::Vector3::UnitY, Math::Deg2Rad(m_pCameraScreen->GetCamera().rotation.y));

	// 加速度がない
	if (move == Math::Vector3::Zero)
	{
		// 速さ
		Limited speed = Limited::Create(m_moveVelocity.Length(), 0.0f, m_params.moveMaxSpeed);
		// 遅くして速度に適用
		speed -= m_params.moveAcceleration * elapsedTime;
		m_moveVelocity.Normalize();
		m_moveVelocity *= speed;
	}
	// 加速度がある
	else
	{
		// 速度に加速度を足す
		m_moveVelocity += Math::Vector3::Transform(move, cameraRotation) * m_params.moveAcceleration * elapsedTime;
		// 速さを最大に収める
		if (m_moveVelocity.Length() > m_params.moveMaxSpeed)
		{
			m_moveVelocity.Normalize();
			m_moveVelocity *= m_params.moveMaxSpeed;
		}

		m_rotation.SetTarget(Math::Quaternion::CreateFromAxisAngle(Math::Vector3::UnitY, Math::Arctan2(m_moveVelocity.x, m_moveVelocity.z)));
	}

	m_fallSpeed += m_params.fallAcceleration * elapsedTime;

	// 回転の更新
	m_rotation.Tick(elapsedTime);

	// 位置に速度を足す
	m_pTransform->Translate((m_moveVelocity - Math::Vector3::UnitY * m_fallSpeed) * elapsedTime);
	// 回転させる
	m_pTransform->SetRotation(m_rotation.GetCurrent());

	// 落下猶予
	m_coyoteTime -= elapsedTime;

	// 当たり判定の更新
	ApplyTransform();
}

// 直方体による座標補正
void Player::BoxCorrect(const Math::Box& box)
{
	// 直方体
	const Math::Box& playerBox = m_pBoxCollider->GetWorldBox();

	// 外接する非回転直方体同士が触れていなければ何もしない
	if (!Math::Geometry::IsCollide(playerBox.CreateNonRotatingBox(), box.CreateNonRotatingBox()))
	{
		return;
	}

	// 距離の方向
	Math::Vector3 direction{};
	// 距離
	float distance = Math::Geometry::Distance(playerBox, box, &direction);
	// めり込んでいるなら
	if (distance < 0.0f)
	{
		m_pTransform->Translate(direction * distance);
	}
}

// メッシュによる座標補正
void Player::MeshCorrect(const Mesh& mesh)
{
	// 直方体
	Math::Box box = m_pBoxCollider->GetWorldBox();
	// 外接する非回転直方体（少し広めに）
	Math::NonRotatingBox nonRotatingBox = m_pBoxCollider->GetWorldBox().CreateNonRotatingBox();
	nonRotatingBox.size += Math::Vector3::One;

	// 壁リスト
	std::vector<Math::Triangle> walls{};
	// 床リスト
	std::vector<Math::Triangle> floors{};

	for (const auto& face : mesh.f)
	{
		// メッシュの三角形を取得
		Math::Triangle triangle = Math::Triangle{ mesh.v.at(face.at(0)), mesh.v.at(face.at(1)) , mesh.v.at(face.at(2)) };
		// 外接する非回転直方体が触れていなければ何もしない
		if (!Math::Geometry::IsCollide(nonRotatingBox, triangle.CreateNonRotatingBox()))
		{
			continue;
		}

		// 傾斜が 45° 以上なら
		if (Math::Abs(triangle.GetNormal().Dot(Math::Vector3::Down)) < 1.0f / 1.41421356f)
		{
			// 壁
			walls.push_back(triangle);
		}
		else
		{
			// 床
			floors.push_back(triangle);
		}
	}

	// 最短距離
	float distance = Math::INFTY;
	// 押出方向
	Math::Vector3 direction{};

	// 床
	for (const auto& floor : floors)
	{
		Math::Vector3 newDirection{};

		float newDistance = Math::Geometry::Distance(floor, box, &newDirection);

		float arccos = newDirection.Dot(Math::Vector3::UnitY);

		// 押出方向の傾斜が 45° 以上なら何もしない
		if (Math::Abs(arccos) < 1.0f / 1.41421356f)
		{
			continue;
		}

		newDistance /= Math::Abs(arccos);

		// 最短距離を更新
		if (newDistance < distance)
		{
			distance = newDistance;
			direction = newDirection;
		}
	}

	// 落下状態ごとの処理
	switch (m_fallState)
	{
	case Player::FallState::OnGround:
		if (distance < box.size.y / 8.0f)
		{
			float arccos = direction.Dot(Math::Vector3::UnitY);

			if (distance < 0.0f || Math::Sign(arccos) == -1)
			{
				m_pTransform->Translate(Math::Vector3::UnitY * (Math::Sign(arccos) * distance));
				box.position += Math::Vector3::UnitY * (Math::Sign(arccos) * distance);
				m_fallSpeed = 0.0f;
				m_coyoteTime = m_coyoteTime.GetMax();
				break;
			}
		}
		m_fallState = FallState::OnAir;
		break;
	case Player::FallState::OnAir:
		if (distance < 0.0f)
		{
			float arccos = direction.Dot(Math::Vector3::UnitY);

			m_pTransform->Translate(Math::Vector3::UnitY * (Math::Sign(arccos) * distance));
			box.position += Math::Vector3::UnitY * (Math::Sign(arccos) * distance);
			m_fallSpeed = 0.0f;
			m_fallState = FallState::OnGround;
			m_coyoteTime = m_coyoteTime.GetMax();
			break;
		}
		if (m_coyoteTime.IsMin())
		{
			m_fallState = FallState::Falling;
		}
		break;
	case Player::FallState::Falling:
		if (distance < 0.0f)
		{
			float arccos = direction.Dot(Math::Vector3::UnitY);

			m_pTransform->Translate(Math::Vector3::UnitY * (Math::Sign(arccos) * distance));
			box.position += Math::Vector3::UnitY * (Math::Sign(arccos) * distance);
			m_fallSpeed = 0.0f;
			m_fallState = FallState::OnGround;
			m_coyoteTime = m_coyoteTime.GetMax();
			break;
		}
		break;
	default:
		break;
	}
	
	// めり込んでいるなら
	if (distance < 0.0f)
	{
		float arccos = direction.Dot(Math::Vector3::UnitY);

		m_pTransform->Translate(Math::Vector3::UnitY* (Math::Sign(arccos)* distance));
		box.position += Math::Vector3::UnitY * (Math::Sign(arccos) * distance);
		m_fallSpeed = 0.0f;
	}

	distance = Math::INFTY;
	direction = Math::Vector3::Zero;

	// 壁
	for (const auto& wall : walls)
	{
		Math::Vector3 newDirection{};

		float newDistance = Math::Geometry::Distance(wall, box, &newDirection);

		// 最短距離を更新
		if (newDistance < distance)
		{
			distance = newDistance;
			direction = newDirection;
		}
	}

	// めり込んでいるなら
	if (distance < 0.0f)
	{
		m_pTransform->Translate(direction * distance);
		box.position += direction * distance;
	}

	ApplyTransform();
}

// トランスフォームを適用
void Player::ApplyTransform()
{
	m_pBoxCollider->ApplyTransform();
}

// 中心座標を取得
const Math::Vector3& Player::GetPosition() const
{
	return m_pBoxCollider->GetWorldBox().position;
}

// カメラの目標座標を取得
Math::Vector3 Player::GetCameraTarget() const
{
	return GetPosition() + (m_moveVelocity + m_fallSpeed * Math::Vector3::Down) * m_params.cameraVelocityCoefficient;
}
