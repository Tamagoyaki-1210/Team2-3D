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
// �f�t�H���g�R���X�g���N�^
//=====================================
CStageSelect::CStageSelect()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CStageSelect::~CStageSelect()
{

}

//=====================================
// ����������
//=====================================
HRESULT CStageSelect::Init(void)
{
	m_pStr = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), "�X�e�[�W�Z���N�g");

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
// �I������
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
// �X�V����
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
// ���͏���
//=====================================
void CStageSelect::Input(void)
{
	CSound *pSound = CApplication::GetSound();

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_A) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
		{// W�L�[�������ꂽ�ꍇ
			m_nSelectNum--;

			// ���݈ʒu��0��艺�̏ꍇ
			if (m_nSelectNum < 0)
			{
				m_nSelectNum = m_nNumAll - 1;
			}
			m_pFrame->SetPos(D3DXVECTOR3(240.0f + (240.0f * m_nSelectNum), 300.0f, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_SELECT);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_D) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
		{// S�L�[�������ꂽ�ꍇ
			m_nSelectNum++;

			// ���݈ʒu���ő吔���傫���ꍇ
			if (m_nSelectNum >= m_nNumAll)
			{
				m_nSelectNum = 0;
			}
			m_pFrame->SetPos(D3DXVECTOR3(240.0f + (240.0f * m_nSelectNum), 300.0f, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_SELECT);
		}
		if (CInputKeyboard::GetKeyboardTrigger(DIK_BACK))
		{// BACKSPACE�L�[����������
			CApplication::SetMode(CApplication::Mode_PlayerSelect);
			pSound->Play(CSound::SOUND_LABEL_SE_NO);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
		{// Enter�L�[����������
			Save();
			CApplication::SetMode(CApplication::Mode_Game_Race);
			pSound->Play(CSound::SOUND_LABEL_SE_YES_STAGE);
		}
	}
}

//=====================================
// ��������
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
// �I�����ꂽ�X�e�[�W�̓ǂݍ��ݏ���
//=====================================
void CStageSelect::Save()
{
	char aStr[256] = {};		//�ǂݍ��ޗp������

								//�t�@�C�����J��
	FILE* pFile = fopen("data\\STAGESET\\SelectStage.txt", "w");

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ
		fprintf(pFile, "%d\n", m_nSelectNum);
	}
	//�t�@�C�������
	fclose(pFile);
}