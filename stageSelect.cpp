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

	if (m_pFrame == nullptr)
	{
		m_pFrame = CObject_2D::Create();
		m_pFrame->SetPos(D3DXVECTOR3(240.0f, 300.0f, 0.0f));
		m_pFrame->SetSize(D3DXVECTOR2(105, 105));
		m_pFrame->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pFrame->SetTexture(CObject::TEXTURE_SELECT_FRAME);
		m_pFrame->SetPriority(4);
	}

	m_nNumAll = 2;

	for(int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		CObject_2D *pObj2D = CObject_2D::Create();
		pObj2D->SetPos(D3DXVECTOR3(240.0f + (240.0f * nCnt), 300.0f, 0.0f));
		pObj2D->SetSize(D3DXVECTOR2(100, 100));
		pObj2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObj2D->SetPriority(4);

		if (nCnt == 0)
		{
			pObj2D->SetTexture(CObject::TEXTURE_NULL);
		}
		else if (nCnt == 1)
		{
			pObj2D->SetTexture(CObject::TEXTURE_BLOCK);
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
		if (CInputKeyboard::GetKeyboardTrigger(DIK_A) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
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
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_D) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
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
		if (CInputKeyboard::GetKeyboardTrigger(DIK_BACK))
		{// BACKSPACEキーを押したら
			CApplication::SetMode(CApplication::Mode_PlayerSelect);
			pSound->Play(CSound::SOUND_LABEL_SE_NO);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
		{// Enterキーを押したら
			Save();
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

//=====================================
// 選択されたステージの読み込み処理
//=====================================
void CStageSelect::Save()
{
	char aStr[256] = {};		//読み込む用文字列

								//ファイルを開く
	FILE* pFile = fopen("data\\STAGESET\\SelectStage.txt", "w");

	if (pFile != nullptr)
	{//ファイルが開いた場合
		fprintf(pFile, "%d\n", m_nSelectNum);
	}
	//ファイルを閉じる
	fclose(pFile);
}