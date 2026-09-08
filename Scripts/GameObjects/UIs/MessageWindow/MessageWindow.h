/*
 * FileName:     MessageWindow.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/08
 *
 * メッセージウィンドウ
 */

#pragma once

#include "Scripts/Commons/Components/Component.h"

namespace Components
{
	class RectTransform;
}
namespace Renderings
{
	class Text;
	class Image;
}

// メッセージウィンドウ
class MessageWindow : public Component
{

public:


	/* メンバ関数 */

	// コンストラクタ
	MessageWindow(const ComponentDesc& desc);

	// 初期化処理
	void Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder) override;

	// 更新処理
	void Update(float elapsedTime);

	// 出現
	void Appear(bool isAppear);


private:


	/* メンバ変数 */

	// 移動時間
	float m_moveTime;

	// 背景サイズ
	Math::Vector2 m_backgroundSize;
	// キャラクター名サイズ
	Math::Vector2 m_characterSize;
	// テキストサイズ
	Math::Vector2 m_textSize;

	// キャラクター名フォントサイズ
	float m_characterFontSize;
	// テキストフォントサイズ
	float m_textFontSize;

	// 移動率
	Easing::Value<float> m_moveRate;

	// 背景のトランスフォーム
	RectTransform* m_pBackgroundTransform;
	// 背景
	Renderings::Image* m_pBackground;

	// キャラクター名のトランスフォーム
	RectTransform* m_pCharacterTransform;
	// キャラクター名
	Renderings::Text* m_pCharacter;

	// テキストのトランスフォーム
	RectTransform* m_pTextTransform;
	// テキスト
	Renderings::Text* m_pText;


};
