/*
 * FileName:     QuaternionCamera.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * カメラ（四元数）
 */

#include "Pch.h"

// ビュー行列を作成
Math::Matrix Libraries::Camera::QuaternionCamera::CreateViewMatrix() const
{
	// カメラの向き
	Math::Vector3 direction = Math::Vector3::Transform(Math::Vector3::Forward, rotation);
	// カメラの上方向
	Math::Vector3 up        = Math::Vector3::Transform(Math::Vector3::Up, rotation);

	return Math::Matrix::CreateLookAt(position, position + direction, up);
}
