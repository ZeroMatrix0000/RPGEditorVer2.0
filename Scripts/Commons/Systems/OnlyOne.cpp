/*
 * FileName:     OnlyOne.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * 2つ以上実体を生成するとエラーを吐くクラス
 */

#include "Pch.h"
#include "OnlyOne.h"

std::unordered_set<std::type_index> Systems::OnlyOne::s_indices{};

// コンストラクタ
Systems::OnlyOne::OnlyOne(const std::type_index& index)
	: m_index{ index }
{
	// インデックスリストに含まれていたら例外処理
	Utility::ThrowIf(s_indices.find(index) != s_indices.end());

	// インデックスリストに追加
	s_indices.emplace(index);
}

// デストラクタ
Systems::OnlyOne::~OnlyOne()
{
	// インデックスリストからインデックスを削除
	auto classesIt = s_indices.find(m_index);
	if (classesIt != s_indices.end())
	{
		s_indices.erase(classesIt);
	}
}
