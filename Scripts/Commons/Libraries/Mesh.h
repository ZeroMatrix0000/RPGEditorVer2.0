/*
 * FileName:     Mesh.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * メッシュ
 */

#pragma once

namespace Libraries
{
	struct Mesh
	{

		/* メンバ関数 */

		// コンストラクタ
		Mesh();

		// ロード（失敗したらfalse）
		bool Load(const std::string& filePath);

		// 拡大
		void Scaling(float scale);


		/* メンバ変数 */

		// 頂点情報
		std::vector<Math::Vector3> v;

		// 面情報（三角形のみ）
		std::vector<std::array<size_t, 3>> f;

	};
}
