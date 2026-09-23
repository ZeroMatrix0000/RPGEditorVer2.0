/*
 * FileName:     ConstantBuffer.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/23
 *
 * 定数バッファ
 */

#pragma once

namespace Renderings
{
	class ConstantBuffer
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		ConstantBuffer();

		// 初期化処理
		void Initialize(ID3DBlob* pBlob);


	private:


		/* 構造体 */

		// 変数情報
		struct Variable
		{
			// 位置
			size_t offset;
			size_t size;
		};


		/* メンバ変数 */

		// データ
		std::vector<std::byte> m_data;

		// 変数リスト
		std::unordered_map<std::string, Variable> m_variables;

	};
}