/*
 * FileName:     BoxCollider.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/08
 *
 * 長方形当たり判定
 */

#pragma once

#include "../GameObjects/Component.h"

namespace Renderings
{
	class IColliderRenderer;
	class ICameraScreen;
}

namespace Colliders
{
	// 長方形当たり判定
	class BoxCollider : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		BoxCollider(const ComponentCreatePermit& permit, GameObject* pOwner, Renderings::IColliderRenderer* pIColliderRenderer);
		// デストラクタ
		~BoxCollider();

		// 座標を設定
		void SetPosition(const Math::Vector3& position) { m_box.position = position; }
		// 大きさを設定
		void SetSize(const Math::Vector3& size) { m_box.size = size; }
		// 色を設定
		void SetColor(const Math::Color& color) { m_color = color; }
		// 色を設定
		void SetColor(const DirectX::XMVECTORF32& color) { m_color = color; }

		// 映るカメラ画面を追加
		void AddICameraScreen(const Renderings::ICameraScreen& iCameraScreen);
		// 映るカメラ画面を削除
		void RemoveICameraScreen(const Renderings::ICameraScreen& iCameraScreen);

		// トランスフォームを適用
		void ApplyTransform();

		// ワールド長方形を取得
		const Math::Box& GetWorldBox() const { return m_worldBox; }

		// 色を取得
		const Math::Color& GetColor() const { return m_color; }

		// 映るカメラ画面のポインタリストを取得
		const std::unordered_set<const Renderings::ICameraScreen*>& GetPICameraScreens() const { return m_pICameraScreens; }

	private:


		/* メンバ変数 */

		// 長方形
		Math::NonRotatingBox m_box;

		// ワールド長方形
		Math::Box m_worldBox;

		// 色
		Math::Color m_color;

		// 映るカメラ画面のポインタリスト
		std::unordered_set<const Renderings::ICameraScreen*> m_pICameraScreens;

		// 当たり判定描画インタフェースのポインタ
		Renderings::IColliderRenderer* m_pIColliderRenderer;

	};
}
