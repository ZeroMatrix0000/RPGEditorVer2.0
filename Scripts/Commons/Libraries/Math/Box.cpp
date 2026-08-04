/*
 * FileName:     Box.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/31
 *
 * 直方体
 */

#include "Pch.h"

// 外接する非回転直方体を生成
Math::NonRotatingBox Libraries::Math::Box::CreateNonRotatingBox() const
{
	auto vertices = GetVertices();

	// 各成分の最小値
	Vector3 min{ Math::INFTY };
	// 各成分の最小値
	Vector3 max{ -Math::INFTY };
	for (size_t i = 0; i < 8; i++)
	{
		// 頂点の位置
		Vector3 vertex = vertices.at(i);

		if (vertex.x < min.x) min.x = vertex.x;
		if (vertex.y < min.y) min.y = vertex.y;
		if (vertex.z < min.z) min.z = vertex.z;
		if (vertex.x > max.x) max.x = vertex.x;
		if (vertex.y > max.y) max.y = vertex.y;
		if (vertex.z > max.z) max.z = vertex.z;
	}

	return NonRotatingBox{ (min + max) / 2.0f, max - min };
}

// 頂点を取得
Math::Vector3 Libraries::Math::Box::GetVertex(bool isPositiveX, bool isPositiveY, bool isPositiveZ) const
{
	Vector3 direction = Vector3
	{
		size.x / (isPositiveX ? 2.0f : -2.0f),
		size.y / (isPositiveY ? 2.0f : -2.0f),
		size.z / (isPositiveZ ? 2.0f : -2.0f)
	};

	return position + Vector3::Transform(direction, rotation);
}

// 頂点の配列を取得
std::array<Math::Vector3, 8> Libraries::Math::Box::GetVertices() const
{
	Vector3 xAxis = Vector3::Transform(Vector3::UnitX, rotation);
	Vector3 yAxis = Vector3::Transform(Vector3::UnitY, rotation);
	Vector3 zAxis = Vector3::Transform(Vector3::UnitZ, rotation);

	return std::array<Vector3, 8>
	{
		position + xAxis * size.x / -2.0f + yAxis * size.y / -2.0f + zAxis * size.z / -2.0f,
		position + xAxis * size.x / -2.0f + yAxis * size.y / -2.0f + zAxis * size.z /  2.0f,
		position + xAxis * size.x / -2.0f + yAxis * size.y /  2.0f + zAxis * size.z / -2.0f,
		position + xAxis * size.x / -2.0f + yAxis * size.y /  2.0f + zAxis * size.z /  2.0f,
		position + xAxis * size.x /  2.0f + yAxis * size.y / -2.0f + zAxis * size.z / -2.0f,
		position + xAxis * size.x /  2.0f + yAxis * size.y / -2.0f + zAxis * size.z /  2.0f,
		position + xAxis * size.x /  2.0f + yAxis * size.y /  2.0f + zAxis * size.z / -2.0f,
		position + xAxis * size.x /  2.0f + yAxis * size.y /  2.0f + zAxis * size.z /  2.0f
	};
}
