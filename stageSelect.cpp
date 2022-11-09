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
#include <random>
#include <iostream>//�p����w�b�_�t�@�C�����ς��܂��B


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

	CObject_2D* pObj = CObject_2D::Create();
	pObj->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	pObj->SetSize(D3DXVECTOR2(6400.0, (float)SCREEN_HEIGHT * 0.5f));
	pObj->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pObj->SetTexture(CObject::TEXTURE_STAGE_SELECT_BG);
	pObj->MoveTexCoordinates(D3DXVECTOR2(0.00002f, 0.0f));
	pObj->SetPriority(3);

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
		if (CInputKeyboard::GetKeyboardTrigger(DIK_A) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_LEFT, 0))
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
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_D) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_RIGHT, 0))
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
		if (CInputKeyboard::GetKeyboardTrigger(DIK_BACK) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_A, 0))
		{// BACKSPACE�L�[����������
			CApplication::SetMode(CApplication::Mode_PlayerSelect);
			pSound->Play(CSound::SOUND_LABEL_SE_NO);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 0))
		{// Enter�L�[����������

			// �����_�����I�΂ꂽ�ꍇ
			if (m_nSelectNum == m_nNumAll - 1)
			{
				std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
				std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
				std::uniform_int_distribution<> rand100(0, m_nNumAll - 2);   // [0, 99] �͈͂̈�l����

				//m_nSelectNum = rand() % (m_nNumAll - 2);
				m_nSelectNum = rand100(mt);
			}

			CApplication::SetStageSelect(m_nSelectNum);
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