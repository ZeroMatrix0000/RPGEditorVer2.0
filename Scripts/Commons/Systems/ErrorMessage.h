/*
 * FileName:     ErrorMessage.h
 * Author:       Takao Hayata
 * Last Updated: 2026/07/24
 *
 * エラーメッセージ
 */

#pragma once

#include "IErrorMessage.h"

namespace Renderings
{
	class Text;
}
namespace GameObjects
{
	class GameObject;
	class IGameObjectInstantiator;
}

namespace Systems
{
	// エラーメッセージ
	class ErrorMessage : public IErrorMessage
	{

	public:

		/* メンバ関数 */


		// コンストラクタ
		ErrorMessage();

		// 初期化処理
		void Initialize(float displayTime, bool isActive);
		// 更新処理
		void Update(float elapsedTime);

		// オブジェクト生成
		void CreateObjects(IGameObjectInstantiator* pIGameObjectInstantiator);

		// メッセージを追加
		void AddMessage(const std::wstring& text) override;


	private:


		/* 構造体 */

		struct MessageData
		{
			/* メンバ変数 */

			// テキスト
			std::wstring text;
			// 表示時間
			Limited timer;
		};


		/* メンバ関数 */

		// 表示を適用
		void ApplyDisplayText();


		/* メンバ変数 */

		// メッセージリスト
		std::vector<MessageData> m_messages;
		// メッセージ数
		size_t                   m_messageCount;

		// 表示するテキストコンポーネント
		Renderings::Text* m_textComponent;

		// 表示する秒数
		float        m_displayTime;

		// アクティブフラグ
		bool m_isActive;

	};
}
