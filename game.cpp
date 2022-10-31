//=============================================================================
//
// game.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "game.h"
#include "inputKeyboard.h"
#include "application.h"

//bool CGame::m_bPause = true;		//ポーズ使用判定
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
	//m_bPause = false;	//ポーズ未使用

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CGame::Uninit(void)
{
	//m_bPause = true;
}

//=====================================
// 更新処理
//=====================================
void CGame::Update(void)
{
	////Pでポーズ切り替え
	//if (pInput->GetKeyboardTrigger(DIK_P))
	//{
	//	if (!m_bPause)
	//	{
	//		CSound::PlaySound(SOUND_LABEL_SE_WHISTLE_STOP);
	//	}
	//	else
	//	{
	//		CSound::PlaySound(SOUND_LABEL_SE_WHISTLE_START);
	//	}
	//	m_bPause = !m_bPause;
	//}

	//ゲーム終了時の処理
	if (m_bEndGame == true)
	{
		CApplication::SetMode(CApplication::Mode_Result);
		m_bEndGame = false;
	}
}