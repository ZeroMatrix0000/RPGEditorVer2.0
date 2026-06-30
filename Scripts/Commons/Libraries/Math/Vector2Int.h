/*
 * FileName:     Vector2Int.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * 整数の2次元座標
 */

#pragma once

namespace Libraries
{
	namespace Math
	{
		struct Vector2Int
		{

			/* メンバ関数 */

			// コンストラクタ
			constexpr Vector2Int()
				: x{}
				, y{}
			{
			}
			// コンストラクタ
			constexpr Vector2Int(int x, int y)
				: x{ x }
				, y{ y }
			{
			}
			// コンストラクタ
			Vector2Int(const Vector2& v)
				: x{ Math::RoundInt(v.x) }
				, y{ Math::RoundInt(v.y) }
			{
			}

			// 大きさを取得
			float Length() const { return Math::Sqrt(static_cast<float>(x * x + y * y)); }


			/* 演算子オーバーロード */

			constexpr bool operator==(const Vector2Int& v) const { return x == v.x && y == v.y; }

			constexpr Vector2Int& operator+=(const Vector2Int& v)
			{
				x += v.x;
				y += v.y;
				return *this;
			}

			constexpr operator Vector2() const { return Vector2{ static_cast<float>(x), static_cast<float>(y) }; }


			/* 静的関数 */

			// 内積を求める
			static constexpr int Dot(const Vector2Int& v1, const Vector2Int& v2) { return v1.x * v2.x + v1.y * v2.y; }


			/* メンバ変数 */

			int x;
			int y;

		};

		/* 演算子オーバーロード */

		constexpr Vector2Int operator+(const Vector2Int& v1, const Vector2Int& v2) { return Vector2Int{ v1.x + v2.x, v1.y + v2.y }; }
		constexpr Vector2    operator+(const Vector2&    v1, const Vector2Int& v2) { return Vector2   { v1.x + v2.x, v1.y + v2.y }; }
		constexpr Vector2    operator+(const Vector2Int& v1, const Vector2&    v2) { return Vector2   { v1.x + v2.x, v1.y + v2.y }; }
		constexpr Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2) { return Vector2Int{ v1.x - v2.x, v1.y - v2.y }; }
		constexpr Vector2    operator-(const Vector2&    v1, const Vector2Int& v2) { return Vector2   { v1.x - v2.x, v1.y - v2.y }; }
		constexpr Vector2    operator-(const Vector2Int& v1, const Vector2&    v2) { return Vector2   { v1.x - v2.x, v1.y - v2.y }; }
		constexpr Vector2    operator*(const Vector2Int&  v, float              k) { return Vector2   {  v.x *    k,  v.y *    k }; }
		constexpr Vector2    operator*(float              k, const Vector2Int&  v) { return Vector2   {    k *  v.x,    k *  v.y }; }
		constexpr Vector2    operator/(const Vector2Int&  v, float              k) { return Vector2   {  v.x /    k,  v.y /    k }; }
		constexpr Vector2    operator/(float              k, const Vector2Int&  v) { return Vector2   {    k /  v.x,    k /  v.y }; }
	}
}
