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
#include "fade.h"
#include "stage.h"
#include "lavaFloor.h"
#include "object3D.h"

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

	CLavaFloor::Create(D3DXVECTOR3(-100.0f, -149.9f, 500.0f), D3DXVECTOR2(100.0f, 15.0f));
	

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
}

//=====================================
// 更新処理
//=====================================
void CGameRace::Update(void)
{
    CGame::Update();

	if (m_pStage != nullptr)
	{
		m_pStage->Update();
	}

#ifdef _DEBUG

    CDebugProc::Print("\n[F2] : デバッグモードへ移動\n");

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_BACK))
		{// Enterキーを押したら
			SetEndGame();
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