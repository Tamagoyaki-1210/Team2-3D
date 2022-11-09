//=============================================================================
//
// stageSelect.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "stageSelect.h"
#include "Application.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "fade.h"
#include <stdio.h>

CFontString* CStageSelect::m_pStr = nullptr;
CObject_2D* CStageSelect::m_pFrame = nullptr;
//=====================================
// デフォルトコンストラクタ
//=====================================
CStageSelect::CStageSelect()
{

}

//=====================================
// デストラクタ
//=====================================
CStageSelect::~CStageSelect()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CStageSelect::Init(void)
{
	m_pStr = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), "ステージセレクト");

	m_pFrame = CObject_2D::Create();
	m_pFrame->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pFrame->SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));
	m_pFrame->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pFrame->SetTexture(CObject::TEXTURE_NULL);
	m_pFrame->SetPriority(3);

	if (m_pFrame == nullptr)
	{
		m_pFrame = CObject_2D::Create();
		m_pFrame->SetPos(D3DXVECTOR3(240.0f, 300.0f, 0.0f));
		m_pFrame->SetSize(D3DXVECTOR2(105, 105));
		m_pFrame->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pFrame->SetTexture(CObject::TEXTURE_SELECT_FRAME);
		m_pFrame->SetPriority(4);
	}

	m_nNumAll = 4;

	for(int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		CObject_2D *pObj2D = CObject_2D::Create();
		pObj2D->SetPos(D3DXVECTOR3(240.0f + (240.0f * nCnt), 300.0f, 0.0f));
		pObj2D->SetSize(D3DXVECTOR2(100, 100));
		pObj2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObj2D->SetPriority(4);

		if (nCnt == 0)
		{
			pObj2D->SetTexture(CObject::TEXTURE_STAGESEL01);
		}
		else if (nCnt == 1)
		{
			pObj2D->SetTexture(CObject::TEXTURE_STAGESEL02);
		}
		else if (nCnt == 2)
		{
			pObj2D->SetTexture(CObject::TEXTURE_STAGESEL03);
		}
		else if (nCnt == 3)
		{
			pObj2D->SetTexture(CObject::TEXTURE_STAGESELR);
		}
	}

	m_nSelectNum = 0;

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CStageSelect::Uninit(void)
{
	if (m_pStr != nullptr)
	{
		m_pStr->Uninit();
		m_pStr = nullptr;
	}

	if (m_pFrame != nullptr)
	{
		m_pFrame->Release();
		m_pFrame = nullptr;
	}
	m_nSelectNum = 0;
}

//=====================================
// 更新処理
//=====================================
void CStageSelect::Update(void)
{
	if (m_pStr != nullptr)
	{
		m_pStr->Update();
	}

	if (m_pFrame != nullptr)
	{
		m_pFrame->Update();
	}
	Input();
}

//=====================================
// 入力処理
//=====================================
void CStageSelect::Input(void)
{
	CSound *pSound = CApplication::GetSound();

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_A) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_LEFT, 0))
		{// Wキーが押された場合
			m_nSelectNum--;

			// 現在位置が0より下の場合
			if (m_nSelectNum < 0)
			{
				m_nSelectNum = m_nNumAll - 1;
			}
			m_pFrame->SetPos(D3DXVECTOR3(240.0f + (240.0f * m_nSelectNum), 300.0f, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_SELECT);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_D) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_RIGHT, 0))
		{// Sキーが押された場合
			m_nSelectNum++;

			// 現在位置が最大数より大きい場合
			if (m_nSelectNum >= m_nNumAll)
			{
				m_nSelectNum = 0;
			}
			m_pFrame->SetPos(D3DXVECTOR3(240.0f + (240.0f * m_nSelectNum), 300.0f, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_SELECT);
		}
		if (CInputKeyboard::GetKeyboardTrigger(DIK_BACK) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_A, 0))
		{// BACKSPACEキーを押したら
			CApplication::SetMode(CApplication::Mode_PlayerSelect);
			pSound->Play(CSound::SOUND_LABEL_SE_NO);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 0))
		{// Enterキーを押したら

			// ランダムが選ばれた場合
			if (m_nSelectNum == m_nNumAll - 1)
			{
				m_nSelectNum = rand() % (m_nNumAll - 2);
			}

			CApplication::SetStageSelect(m_nSelectNum);
			CApplication::SetMode(CApplication::Mode_Game_Race);
			pSound->Play(CSound::SOUND_LABEL_SE_YES_STAGE);
		}
	}
}

//=====================================
// 生成処理
//=====================================
CStageSelect* CStageSelect::Create(void)
{
	CStageSelect* pStaeSelect = new CStageSelect;

	if (FAILED(pStaeSelect->Init()))
	{
		return nullptr;
	}

	return pStaeSelect;
}