//=============================================================================
//
// game.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "mode.h"

//---------------------------
//クラス宣言
//---------------------------
class CGame : public CMode
{
public:
	CGame();
	~CGame();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	//static void SetPause(bool bUse) { m_bPause = bUse; }	// ポーズ状態を設定する
	static void SetEndGame() { m_bEndGame = true; }			// ゲーム終了を設定する

	//static bool GetPause() { return m_bPause; }				// ポーズ状態取得

private:
	//static bool m_bPause;
	static bool m_bEndGame;
};

#endif // !_GAME_H_
