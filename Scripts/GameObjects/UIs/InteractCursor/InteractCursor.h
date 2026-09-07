/*
 * FileName:     InteractCursor.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/05
 *
 * 話しかける・調べる際のカーソル
 */

#pragma once

#include "Scripts/Commons/Components/Component.h"

namespace Components
{
	class RectTransform;
}
namespace Renderings
{
	class ICameraScreen;
	class Canvas;
	class Text;
	class Image;
}

// 話しかける・調べる際のカーソル
class InteractCursor : public Component
{

public:


	/* メンバ関数 */

	// コンストラクタ
	InteractCursor(const ComponentDesc& desc);

	// 初期化処理
	void Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder) override;

	// 更新処理
	void Update(float elapsedTime, bool isFocused);

	// 名前を設定
	void SetName(const std::wstring& name);

	// キャンバスを設定
	void SetCanvas(const Renderings::Canvas& canvas);

	// 座標を設定
	void SetPosition(const Math::Vector2& position);


private:


	/* メンバ変数 */

	// 不透明度の速度
	float m_alphaVelocity;

	// 不透明度
	Limited m_alpha;

	// テキストのトランスフォーム
	RectTransform* m_pTextTransform;
	// テキスト
	Renderings::Text* m_pText;

	// 画像のトランスフォーム
	RectTransform* m_pImageTransform;
	// 画像
	Renderings::Image* m_pImage;

};
