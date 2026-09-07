/*
 * FileName:     Action.h
 * Author:       Takao Hayata
 * Last Updated: 2026/09/07
 *
 * アクション
 */

#pragma once

class GamePlaySceneInternals;

// アクション
class Action
{

public:


	/* メンバ関数 */

	// コンストラクタ
	Action();
	// デストラクタ
	virtual ~Action() = default;

	// 開始処理
	virtual void Enter(GamePlaySceneInternals* pInternals);
	// 更新処理
	virtual void Update(GamePlaySceneInternals* pInternals, float elapsedTime);
	// 終了処理
	virtual void Exit(GamePlaySceneInternals* pInternals);

	// 次のアクションに移動するかどうかを取得
	bool IsNext() const { return m_isNext; }


protected:


	/* メンバ関数 */

	// 次のアクションに移動
	void GoNext() { m_isNext = true; }


private:


	/* メンバ変数 */

	// 次のアクションに移動するかどうか
	bool m_isNext;

};