/*
 * FileName:     GameObject.h
 * Author:       Takao Hayata
 * Last Updated: 2026/06/30
 *
 * ゲームオブジェクト
 */

#pragma once

namespace Objects
{
	// 前方宣言
	class Component;

	class GameObject
	{

	public:


		/* メンバ関数 */

		// コンストラクタ
		GameObject();


	private:


		/* メンバ変数 */

		// コンポーネント
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;

	};
}
