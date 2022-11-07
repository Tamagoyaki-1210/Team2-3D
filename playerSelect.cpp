//=============================================================================
//
// title.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "playerSelect.h"
#include "Application.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "fade.h"
#include "playerModel.h"
#include "camera.h"

CFontString* CPlayerSelect::m_pStr = nullptr;
//=====================================
// デフォルトコンストラクタ
//=====================================
CPlayerSelect::CPlayerSelect()
{

}

//=====================================
// デストラクタ
//=====================================
CPlayerSelect::~CPlayerSelect()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CPlayerSelect::Init(void)
{
	m_pStr = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), "キャラクターセレクト");

	CCamera* pCamera = CApplication::GetCamera();
	pCamera->SetPos(D3DXVECTOR3(50.0f, 230.0f, -200.0f), D3DXVECTOR3(50.0f, 220.0f, 100.0f));

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CPlayerSelect::Uninit(void)
{
	if (m_pStr != nullptr)
	{
		m_pStr->Uninit();
		m_pStr = nullptr;
	}
}

//=====================================
// 更新処理
//=====================================
void CPlayerSelect::Update(void)
{
	if (m_pStr != nullptr)
	{
		m_pStr->Update();
	}
	Input();
}

//=====================================
// 入力処理
//=====================================
void CPlayerSelect::Input(void)
{
	CSound *pSound = CApplication::GetSound();

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_BACK) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_A, 0))
		{// BACKSPACEキーを押したら
			CApplication::SetMode(CApplication::Mode_Title);
			pSound->Play(CSound::SOUND_LABEL_SE_NO);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 0))
		{// Enterキーを押したら
			CApplication::SetMode(CApplication::Mode_StageSelect);
			pSound->Play(CSound::SOUND_LABEL_SE_YES);
		}
	}
}

//=====================================
// 生成処理
//=====================================
CPlayerSelect* CPlayerSelect::Create(void)
{
	CPlayerSelect* pPlayerSelect = new CPlayerSelect;

	if (FAILED(pPlayerSelect->Init()))
	{
		return nullptr;
	}

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		CPlayerModel::Create(D3DXVECTOR3(-100.0f + (100.0f * nCnt), 220.0f, 100.0f), nCnt);
	}

	return pPlayerSelect;
}