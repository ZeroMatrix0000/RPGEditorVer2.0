/*
 * FileName:     SceneFactory.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/01
 *
 * シーン工場
 */

#include "SampleScene.h"
#include "Scripts/Commons/GameObjects/ComponentFactory.h"

// 前方宣言
namespace GameObjects
{
	class GameObject;
}

// サンプルシーンコンポーネントを作成
template<>
inline std::unique_ptr<SampleScene> ComponentFactory::Create(GameObject*) const
{
	return std::make_unique<SampleScene>(m_permit);
};
