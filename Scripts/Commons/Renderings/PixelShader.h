/*
 * FileName:     PixelShader.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/23
 *
 * ピクセルシェーダ
 */

#pragma once

#include "ConstantBuffer.h"

namespace Renderings
{
	class PixelShader
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		PixelShader();

		// 初期化処理
		void Initialize(ID3D11Device5* device, const std::wstring& filePath);

		// シェーダを取得
		auto* GetD3DShader() const { return m_d3dShader.Get(); }

		/* 静的関数 */

		// 生成
		static PixelShader Create(ID3D11Device5* device, const std::wstring& filePath);


	private:


		/* メンバ変数 */

		// シェーダ
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_d3dShader;

		// 定数バッファ
		ConstantBuffer m_constantBuffer;

	};
}