/*
 * FileName:     Mesh.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/24
 *
 * メッシュ
 */

#include "Pch.h"

// コンストラクタ
Libraries::Mesh::Mesh()
	: v{}
	, f{}
{
}

// ロード（失敗したらfalse）
bool Libraries::Mesh::Load(const std::string& filePath)
{
	v.clear();
	f.clear();

	// ファイル
	std::ifstream fileStream{ filePath };
	// 開けなかったら終了
	if (!fileStream.is_open())
	{
		fileStream.close();
		return false;
	}

	while (true)
	{
		// 1行読み込む
		std::string s{};
		std::getline(fileStream, s);
		if (s.empty())
		{
			break;
		}
		std::stringstream ss{ s };

		// 識別子
		std::string id{};
		ss >> id;
		if (id == "v")
		{
			Math::Vector3 vertex{};
			ss >> vertex.x >> vertex.y >> vertex.z;
			v.push_back(vertex);
		}
		else if (id == "f")
		{
			size_t v1, v2, v3;
			ss >> v1 >> v2 >> v3;
			f.push_back(std::array<size_t, 3>{ v1, v2, v3 });
		}
	}

	fileStream.close();
	return true;
}

// 行列を適用
void Libraries::Mesh::ApplyMatrix(const Math::Matrix& matrix)
{
	for (auto& vertex : v)
	{
		vertex = Math::Vector3::Transform(vertex, matrix);
	}
}
