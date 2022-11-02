//=============================================================================
//
// gamerace.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "gamerace.h"
#include "input.h"
#include "application.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "message.h"
#include "fade.h"
#include "stage.h"

CMessage* CGameRace::m_pMessage = nullptr;
CStage* CGameRace::m_pStage = nullptr;

//=====================================
// デフォルトコンストラクタ
//=====================================
CGameRace::CGameRace()
{

}

//=====================================
// デストラクタ
//=====================================
CGameRace::~CGameRace()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CGameRace::Init(void)
{
    CGame::Init();

	m_pStage = CStage::Create();

	// メッセージの生成
	m_pMessage = CMessage::Create();

	// カウントダウンメッセージ表示
	m_pMessage->SetCountDown(3);

	//m_pMessage->GoalMessage();

    return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CGameRace::Uninit(void)
{
    CGame::Uninit();

	if (m_pStage != nullptr)
	{
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = nullptr;
	}

	if (m_pMessage != nullptr)
	{
		m_pMessage->Uninit();
		delete m_pMessage;
		m_pMessage = nullptr;
	}
}

//=====================================
// 更新処理
//=====================================
void CGameRace::Update(void)
{
    CGame::Update();

	if (m_pMessage != nullptr)
	{
		m_pMessage->Update();
	}

	if (m_pStage != nullptr)
	{
		m_pStage->Update();
	}

#ifdef _DEBUG

    CDebugProc::Print("\n[F2] : デバッグモードへ移動\n");

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_F2))
		{// F2キーを押したら
			CApplication::SetMode(CApplication::Mode_Game_Debug);
		}
		if (CInputKeyboard::GetKeyboardTrigger(DIK_BACK))
		{// Enterキーを押したら
			SetEndGame();
		}
		if (CInputKeyboard::GetKeyboardTrigger(DIK_G))
		{// Gキーを押したら
			m_pMessage->GoalMessage(0);
		}
	}

#endif // _DEBUG
}

//=====================================
// 生成処理
//=====================================
CGameRace* CGameRace::Create(void)
{
    CGameRace* pGameRace = new CGameRace;

    if (FAILED(pGameRace->Init()))
    {
        return nullptr;
    }

    return pGameRace;
}