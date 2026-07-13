/*
 * FileName:     SelectMenu.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/13
 *
 * 選択メニュー
 */

#pragma once

#include "Scripts/Commons/GameObjects/Component.h"
#include "Scripts/Commons/GameObjects/GameObject.h"

namespace Renderings
{
	class Canvas;
}
namespace GameObjects
{
	class IComponentManager;
	class RectTransform;
}

 // 選択メニュー
class SelectMenu : public Component
{

public:


	/* メンバ関数 */

	// コンストラクタ
	SelectMenu(const ComponentCreatePermit& permit, GameObject* pOwner);

	// 初期化処理
	void Initialize
	(
		const IComponentManager&  iComponentManager,
		float                     width,
		const Math::Color&        color,
		const Math::Vector2&      position,
		Utility::AlignmentPoint   anchor,
		const Renderings::Canvas& canvas
	);

	// 更新処理
	void Update(float elapsedTime) override;

	// 選択肢を追加
	void AddOption(const IComponentManager& iComponentManager, const std::wstring& str, const std::function<void()>& Process);

	// 上の項目を選択
	void SelectUp();
	// 下の項目を選択
	void SelectDown();

	// 実行
	void Execute();


private:


	/* 定数 */

	// 高さ
	static constexpr float HEIGHT = 50.0f;

	// 間隔
	static constexpr float INTERVAL = 20.0f;

	// カーソルの移動時間
	static constexpr float CURSOR_MOVE_TIME = 0.25f;
	// カーソルの左右の揺れの周期
	static constexpr float CURSOR_SWAY_TIME = 2.0f;
	// カーソルの左右の揺れの大きさ
	static constexpr float CURSOR_SWAY_SIZE = 20.0f;


	/* メンバ変数 */

	// 幅
	float m_width;

	// 基準座標
	Math::Vector2 m_basePosition;

	// カーソル
	GameObject m_cursor;
	// カーソルの2D用トランスフォーム
	RectTransform* m_pCursorRectTransform;

	// 選択肢のテキスト
	std::vector<std::unique_ptr<GameObject>> m_texts;
	// 選択肢の処理
	std::vector<std::function<void()>> m_Processes;

	// 選択番号
	int m_selectNumber;
	// カーソルのY座標のズレ
	Easing::Value<float> m_cursorDelayY;
	// カーソルの左右の揺れの周期
	Cycled m_cursorSwayTimer;

};
