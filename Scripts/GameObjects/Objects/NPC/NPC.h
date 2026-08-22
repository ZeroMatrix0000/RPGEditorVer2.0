/*
 * FileName:     NPC.h
 * Author:       Takao Hayata
 * Last Updated: 2026/08/22
 *
 * NPC
 */

#pragma once

#include "Scripts/Commons/Components/Component.h"

namespace Components
{
	class Transform;
}
namespace Colliders
{
	class BoxCollider;
}

// NPC
class NPC : public Component
{

public:


	/* メンバ関数 */

	// コンストラクタ
	NPC(const ComponentDesc& desc);

	// 初期化処理
	void Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder) override;

	// 更新処理
	void Update(float elapsedTime);

	// 回転を設定
	void SetRotation(const Math::Quaternion* rotation = nullptr);

	// 会話判定距離を取得
	float GetFocusDistance() const { return m_focusDistance; }

	// 中心座標を取得
	const Math::Vector3& GetPosition() const;
	// 当たり判定を取得
	const Math::Box& GetBox() const;


private:


	/* メンバ変数 */

	// 会話判定距離
	float m_focusDistance;

	// 基準回転
	Math::Quaternion m_baseRotation;

	// 回転
	Spring<Math::Quaternion> m_rotation;

	// トランスフォーム
	Transform* m_pTransform;
	// 長方形の当たり判定
	Colliders::BoxCollider* m_pBoxCollider;

};
