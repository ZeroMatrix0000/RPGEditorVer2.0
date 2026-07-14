/*
 * FileName:     SphereCollider.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/14
 *
 * 球の当たり判定
 */

#pragma once

#include "../Components/Component.h"

namespace Renderings
{
	class IColliderRenderer;
	class ICameraScreen;
}

namespace Colliders
{
	// 球の当たり判定
	class SphereCollider : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		SphereCollider(const ComponentCreatePermit& permit, GameObject* pOwner, Renderings::IColliderRenderer* pIColliderRenderer);
		// デストラクタ
		~SphereCollider();

		// 座標を設定
		void SetPosition(const Math::Vector3& position) { m_sphere.centerPosition = position; }
		// 半径を設定
		void SetRadius(float radius) { m_sphere.radius = radius; }
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

		// ワールド球を取得
		const Math::Sphere& GetWorldSphere() const { return m_worldSphere; }

		// 色を取得
		const Math::Color& GetColor() const { return m_color; }

		// 映るカメラ画面のポインタリストを取得
		const std::unordered_set<const Renderings::ICameraScreen*>& GetPICameraScreens() const { return m_pICameraScreens; }

	private:


		/* メンバ変数 */

		// 長方形
		Math::Sphere m_sphere;

		// ワールド長方形
		Math::Sphere m_worldSphere;

		// 色
		Math::Color m_color;

		// 映るカメラ画面のポインタリスト
		std::unordered_set<const Renderings::ICameraScreen*> m_pICameraScreens;

		// 当たり判定描画インタフェースのポインタ
		Renderings::IColliderRenderer* m_pIColliderRenderer;

	};
}
