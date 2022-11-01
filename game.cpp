//=============================================================================
//
// game.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "game.h"
#include "inputKeyboard.h"
#include "application.h"

bool CGame::m_bPause = false;		//ポーズ使用判定
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
	m_bPause = false;
}

//=====================================
// 更新処理
//=====================================
void CGame::Update(void)
{
	//Pでポーズ切り替え
	if (CInputKeyboard::GetKeyboardTrigger(DIK_P))
	{
		m_bPause = !m_bPause;	//ポーズ切り替え処理
	}

	//ゲーム終了時の処理
	if (m_bEndGame == true)
	{
		CApplication::SetMode(CApplication::Mode_Result);
		m_bEndGame = false;
	}
}