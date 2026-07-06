/*
 * FileName:     Vector3Int.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * 整数の3次元座標
 */

#pragma once

namespace Libraries
{
	namespace Math
	{
		// 整数の3次元座標
		struct Vector3Int
		{

			/* メンバ関数 */

			// コンストラクタ
			constexpr Vector3Int()
				: x{}
				, y{}
				, z{}
			{
			}
			// コンストラクタ
			constexpr Vector3Int(int x, int y, int z)
				: x{ x }
				, y{ y }
				, z{ z }
			{
			}
			// コンストラクタ
			Vector3Int(const Vector3& v)
				: x{ Math::RoundInt(v.x) }
				, y{ Math::RoundInt(v.y) }
				, z{ Math::RoundInt(v.z) }
			{
			}

			// 大きさを取得
			float Length() const { return Math::Sqrt(static_cast<float>(x * x + y * y + z * z)); }


			/* 演算子オーバーロード */

			constexpr bool operator==(const Vector3Int& v) const { return x == v.x && y == v.y && z == v.z; }

			constexpr Vector3Int& operator+=(const Vector3Int& v)
			{
				x += v.x;
				y += v.y;
				z += v.z;
				return *this;
			}

			constexpr operator Vector3() const { return Vector3{ static_cast<float>(x), static_cast<float>(y) , static_cast<float>(z) }; }


			/* 静的関数 */

			// 内積を求める
			static constexpr int Dot(const Vector3Int& v1, const Vector3Int& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }


			/* メンバ変数 */

			int x;
			int y;
			int z;

		};

		/* 演算子オーバーロード */

		constexpr Vector3Int operator+(const Vector3Int& v1, const Vector3Int& v2) { return Vector3Int{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z }; }
		constexpr Vector3    operator+(const Vector3&    v1, const Vector3Int& v2) { return Vector3   { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z }; }
		constexpr Vector3    operator+(const Vector3Int& v1, const Vector3&    v2) { return Vector3   { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z }; }
		constexpr Vector3Int operator-(const Vector3Int& v1, const Vector3Int& v2) { return Vector3Int{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z }; }
		constexpr Vector3    operator-(const Vector3&    v1, const Vector3Int& v2) { return Vector3   { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z }; }
		constexpr Vector3    operator-(const Vector3Int& v1, const Vector3&    v2) { return Vector3   { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z }; }
		constexpr Vector3    operator*(const Vector3Int&  v, float              k) { return Vector3   {  v.x *    k,  v.y *    k,  v.z *    k }; }
		constexpr Vector3    operator*(float              k, const Vector3Int&  v) { return Vector3   {    k *  v.x,    k *  v.y,    k *  v.z }; }
		constexpr Vector3    operator/(const Vector3Int&  v, float              k) { return Vector3   {  v.x /    k,  v.y /    k,  v.z /    k }; }
		constexpr Vector3    operator/(float              k, const Vector3Int&  v) { return Vector3   {    k /  v.x,    k /  v.y,    k /  v.z }; }
	}
}
