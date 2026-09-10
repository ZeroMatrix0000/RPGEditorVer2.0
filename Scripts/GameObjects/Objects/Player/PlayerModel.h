/*
 * FileName:     PlayerModel.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/10
 *
 * プレイヤーのモデル
 */

#pragma once

#include "Scripts/Commons/Components/Component.h"

namespace Components
{
	class Transform;
}

// プレイヤーのモデル
class PlayerModel : public Component
{

public:


	/* メンバ関数 */

	// コンストラクタ
	PlayerModel(const ComponentDesc& desc);

	// 初期化処理
	void Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder) override;

	// 更新処理
	void Update(float elapsedTime);

	// トランスフォームを設定
	void SetTransform(const Transform& transform);


private:


	/* 列挙型 */

	// 落下状態
	enum class FallState
	{
		OnGround,
		OnAir,
		Falling
	};


	/* メンバ変数 */

	// 自身のトランスフォーム
	Transform* m_pTransform;

};
