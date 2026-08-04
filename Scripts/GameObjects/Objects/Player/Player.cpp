/*
 * FileName:     Player.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/08/04
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

	Systems::JsonSerializer serializer{ pIGameObjectFinder };
	serializer.AddParameter(&m_params.moveMaxSpeed, "MoveMaxSpeed");
	serializer.AddParameter(&m_params.moveAcceleration, "MoveAcceleration");
	serializer.AddParameter(&fallMaxSpeed, "FallMaxSpeed");
	serializer.AddParameter(&m_params.fallAcceleration, "FallAcceleration");
	serializer.AddParameter(&m_params.cameraVelocityCoefficient, "CameraVelocityCoefficient");
	serializer.AddParameter(&m_pCameraScreen, "CameraScreen");
	serializer.Load(json);

	m_fallSpeed.Initialize(0.0f, 0.0f, fallMaxSpeed);
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

	// 当たり判定の更新
	m_pBoxCollider->ApplyTransform();
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
	const Math::Box& box = m_pBoxCollider->GetWorldBox();
	// 外接する非回転直方体
	Math::NonRotatingBox nonRotatingBox = m_pBoxCollider->GetWorldBox().CreateNonRotatingBox();

	// 最短距離
	float distance = Math::INFTY;
	Math::Vector3 direction{};

	for (const auto& face : mesh.f)
	{
		// メッシュの三角形を取得
		Math::Triangle triangle = Math::Triangle{ mesh.v.at(face.at(0)), mesh.v.at(face.at(1)) , mesh.v.at(face.at(2)) };
		// 外接する非回転直方体が触れていなければ何もしない
		if (!Math::Geometry::IsCollide(nonRotatingBox, triangle.CreateNonRotatingBox()))
		{
			continue;
		}

		float newDistance = Math::INFTY;
		Math::Vector3 newDirection{};

		newDistance = Math::Geometry::Distance(triangle, box, &newDirection);

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
		m_pBoxCollider->ApplyTransform();
	}
}

// 中心座標を取得
const Math::Vector3& Player::GetPosition() const
{
	return m_pBoxCollider->GetWorldBox().position;
}

// カメラの目標座標を取得
Math::Vector3 Player::GetCameraTarget() const
{
	return GetPosition() + m_moveVelocity * m_params.cameraVelocityCoefficient;
}
