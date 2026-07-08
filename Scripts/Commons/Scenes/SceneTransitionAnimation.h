/*
 * FileName:     SceneTransitionAnimation.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * シーン遷移時のアニメーション
 */

#pragma once

#include "../GameObjects/GameObject.h"

namespace GameObjects
{
	class RectTransform;
	class IComponentManager;
}

namespace Scenes
{
	class SceneTransitionAnimation
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		SceneTransitionAnimation();

		// 初期化処理
		void Initialize(const Math::Vector2& outputSize, const IComponentManager& iComponentManager);
		// 更新処理
		void Update(float elapsedTime);

		// キャンバスサイズの変更
		void SetCanvasSize(const Math::Vector2& outputSize);

		// 切り替え率を設定
		void SetAnimation(bool isEnter);

		// 切り替え中かどうか
		bool IsChanging() const { return m_changingRate.IsMoving(); }


	private:


		/* 定数 */

		// 切り替えの角度
		static constexpr float CHANGE_ANGLE = 15.0f;
		// 切り替えにかける時間
		static constexpr float CHANGE_TIME = 0.5f;

		// 画像のレイヤー順
		static constexpr int ORDER_IN_LAYER = 32767;
		// 画像色
		static constexpr Math::Color COLOR = Math::Color{ 0.0f, 0.0f, 0.0f, 1.0f };


		/* メンバ変数 */

		// 切り替え率
		Easing::Value<float> m_changingRate;

		// 画像
		GameObject m_image;
		// 画像の2D用トランスフォーム
		RectTransform* m_imageRectTransform;


		// キャンバス
		GameObject m_canvas;

	};
}
