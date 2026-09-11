/*
 * FileName:     BlackBelt.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/11
 *
 * 上下の黒帯
 */

#pragma once

#include "Scripts/Commons/Components/Component.h"

namespace Components
{
	class RectTransform;
}
namespace Renderings
{
	class Image;
}

// 上下の黒帯
class BlackBelt : public Component
{

public:


	/* メンバ関数 */

	// コンストラクタ
	BlackBelt(const ComponentDesc& desc);

	// 初期化処理
	void Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder) override;

	// 更新処理
	void Update(float elapsedTime);

	// 出現
	void Appear(bool isAppear);

	// 幅を設定
	void SetWidth(float width);


private:


	/* メンバ変数 */

	// 移動時間
	float m_moveTime;

	// 高さ
	float m_height;

	// 移動率
	Easing::Value<float> m_moveRate;

	// 上の画像のトランスフォーム
	RectTransform* m_pTopImageTransform;
	// 上の画像
	Renderings::Image* m_pTopImage;
	// 下の画像のトランスフォーム
	RectTransform* m_pBottomImageTransform;
	// 下の画像
	Renderings::Image* m_pBottomImage;

};
