/*
 * FileName:     Utility.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * 便利関数群
 */

#include "Pch.h"

// 条件を満たしたら例外処理
void Libraries::Utility::ThrowIf(bool value)
{
	if (value)
	{
		throw std::exception("Error!");
	}
}

// 失敗したら例外処理
void Libraries::Utility::ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw std::exception("HRESULT: %08x", static_cast<UINT>(hr));
	}
}

// string -> wstring
std::wstring Libraries::Utility::string2wstring(const std::string& value)
{
	// 文字列の長さ
	int size = MultiByteToWideChar(CP_UTF8, 0, value.c_str(), -1, nullptr, 0) - 1;
	// 変換
	std::wstring wstr(size, 0);
	MultiByteToWideChar(CP_UTF8, 0, value.c_str(), -1, &wstr[0], size);
	return wstr;
}

// wstring -> string
std::string Libraries::Utility::wstring2string(const std::wstring& value)
{
	// 文字列の長さ
	int size = WideCharToMultiByte(CP_UTF8, 0, value.c_str(), -1, nullptr, 0, nullptr, nullptr) - 1;
	// 変換
	std::string str(size, 0);
	WideCharToMultiByte(CP_UTF8, 0, value.c_str(), -1, &str[0], size, nullptr, nullptr);
	return str;
}

// wstring -> float
float Libraries::Utility::wstring2float(const std::wstring& value)
{
	std::wstringstream x;
	float y = 0;
	x << value;
	x >> y;

	return Math::Abs(y) > Math::INFTY ? 0.0f : y;
}

// wstring -> float
std::wstring Libraries::Utility::float2wstring(float value)
{
	std::wstringstream x;
	x << value;
	return x.str();
}
