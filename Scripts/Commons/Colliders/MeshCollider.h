/*
 * FileName:     MeshCollider.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/24
 *
 * メッシュの当たり判定
 */

#pragma once

#include "../Components/Component.h"

namespace Renderings
{
	class IColliderRenderer;
	class ICameraScreen;
}
namespace Systems
{
	class IResources;
}

namespace Colliders
{
	// 長方形の当たり判定
	class MeshCollider : public Component
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		MeshCollider(const ComponentDesc& desc, Renderings::IColliderRenderer* pIColliderRenderer, const Systems::IResources& iResources);
		// デストラクタ
		~MeshCollider();

		// 初期化処理
		void Initalize(const nlohmann::ordered_json& json, IGameObjectFinder* pIGameObjectFinder) override;

		// メッシュを設定
		void SetMesh(const std::string& meshName);
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
		const Mesh& GetWorldMesh() const { return m_worldMesh; }

		// 色を取得
		const Math::Color& GetColor() const { return m_color; }

		// 映るカメラ画面のポインタリストを取得
		const std::unordered_set<const Renderings::ICameraScreen*>& GetPICameraScreens() const { return m_pICameraScreens; }

	private:


		/* メンバ変数 */

		// ワールドメッシュ
		Mesh m_worldMesh;

		// 色
		Math::Color m_color;

		// メッシュのポインタ
		const Mesh* m_pMesh;

		// 映るカメラ画面のポインタリスト
		std::unordered_set<const Renderings::ICameraScreen*> m_pICameraScreens;

		// 当たり判定描画インタフェースのポインタ
		Renderings::IColliderRenderer* m_pIColliderRenderer;

		// リソース管理
		const Systems::IResources& m_refIResources;

	};
}
