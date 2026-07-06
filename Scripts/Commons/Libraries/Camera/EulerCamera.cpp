/*
 * FileName:     EulerCamera.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/06
 *
 * カメラ（オイラー角）
 */

#include "Pch.h"

// ビュー行列を作成
Math::Matrix Libraries::Camera::EulerCamera::CreateViewMatrix() const
{
	// 四元数
	Math::Quaternion q         = rotation.CreateQuaternion();
	// カメラの向き
	Math::Vector3    direction = Math::Vector3::Transform(Math::Vector3::Forward, q);
	// カメラの上方向
	Math::Vector3    up        = Math::Vector3::Transform(Math::Vector3::Up, q);

	return Math::Matrix::CreateLookAt(position, position + direction, up);
}
