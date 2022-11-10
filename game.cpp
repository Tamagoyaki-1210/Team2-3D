//=============================================================================
//
// game.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "game.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "application.h"
#include "menu.h"

bool CGame::m_bEndGame = false;		//ゲーム終了判定

//=====================================
// デフォルトコンストラクタ
//=====================================
CGame::CGame()
{

}

//=====================================
// デストラクタ
//=====================================
CGame::~CGame()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CGame::Init(void)
{
	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CGame::Uninit(void)
{
	m_bEndGame = false;
}

//=====================================
// 更新処理
//=====================================
void CGame::Update(void)
{
	//ゲーム中の処理
	if (m_bEndGame == false)
	{
		//Pでポーズ切り替え
		if (CInputKeyboard::GetKeyboardTrigger(DIK_P) 
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 0)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 1)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 2)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 3))
		{
			bool bPause = !CApplication::GetPause();	//ポーズ切り替え処理
			CApplication::SetPause(bPause);
			CMenu::PauseChange(bPause);		// ポーズ処理
		}
	}
}

//=====================================
// 更新処理
//=====================================
void CGame::SetEndGame(void)
{
	m_bEndGame = true;
}