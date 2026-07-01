/*
 * FileName:     Model3D.cpp
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * 3Dモデル
 */

#include "Pch.h"
#include "Model3D.h"

Renderings::Model3D::Model3D(const ComponentCreatePermit& permit, GameObject* pOwner)
	: Component{ permit, pOwner }
	, m_modelName{}
{
}