//=============================================================================
//
// menu.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "menu.h"
#include "Application.h"
#include "font.h"
#include "mode.h"
#include "choice.h"
#include "inputKeyboard.h"
#include "inputPad.h"

int CMenu::m_nNumAll = 0;
int CMenu::m_nSelectNum = 0;
CChoice* CMenu::m_pChoice[MaxChoice] = {};

//-----------------------------------------
//�v���g�^�C�v�錾
//-----------------------------------------
void ExitExe(void);

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CMenu::CMenu()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CMenu::~CMenu()
{

}

//=====================================
// ����������
//=====================================
HRESULT CMenu::Init(void)
{
	switch (CApplication::GetMode())
	{
	case CApplication::Mode_Title :

		m_pChoice[m_nNumAll] = CChoice::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�X�^�[�g");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CChoice::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�����");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();
		break;
	case CApplication::Mode_Game_Race:
		break;
	case CApplication::Mode_Result:
		m_pChoice[m_nNumAll] = CChoice::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "���g���C");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CChoice::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�^�C�g���ɂ��ǂ�");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();
		break;
	case CApplication::Mode_Game_Debug:
		break;
	default:
		break;
	}

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CMenu::Uninit(void)
{
	for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
	{
		if (m_pChoice[nCnt] != nullptr)
		{
			m_pChoice[nCnt]->Uninit();
		}
	}
	m_nSelectNum = 0;
	m_nNumAll = 0;
}

//=====================================
// �X�V����
//=====================================
void CMenu::Update(void)
{
	if (CApplication::GetMode() == CApplication::Mode_Title || CApplication::GetMode() == CApplication::Mode_Result)
	{
		for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
		{
			if (m_pChoice[nCnt] != nullptr)
			{
				m_pChoice[nCnt]->Update();
			}
		}
		Input();
	}
}

//=====================================
// ���͏���
//=====================================
void CMenu::Input(void)
{
	if (CInputKeyboard::GetKeyboardTrigger(DIK_W) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).y < -0.3f)
	{// W�L�[�������ꂽ�ꍇ
		m_pChoice[m_nSelectNum]->SizeReset();
		m_nSelectNum--;

		// ���݈ʒu��0��艺�̏ꍇ
		if (m_nSelectNum < 0)
		{
			m_nSelectNum = m_nNumAll - 1;
		}
		m_pChoice[m_nSelectNum]->SetSellect();
	}
	else if (CInputKeyboard::GetKeyboardTrigger(DIK_S) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).y > 0.3f)
	{// S�L�[�������ꂽ�ꍇ
		m_pChoice[m_nSelectNum]->SizeReset();
		m_nSelectNum++;

		// ���݈ʒu���ő吔���傫���ꍇ
		if (m_nSelectNum >= m_nNumAll)
		{
			m_nSelectNum = 0;
		}
		m_pChoice[m_nSelectNum]->SetSellect();
	}
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{
		switch (CApplication::GetMode())
		{
		case CApplication::Mode_Title:

			if (m_nSelectNum == 0)
			{
				CApplication::SetMode(CApplication::Mode_Game_Race);
			}
			else if (m_nSelectNum == 1)
			{
				ExitExe();
			}
			break;
		case CApplication::Mode_Result:
			if (m_nSelectNum == 0)
			{
				CApplication::SetMode(CApplication::Mode_Game_Race);
			}
			else if (m_nSelectNum == 1)
			{
				CApplication::SetMode(CApplication::Mode_Title);
			}
			break;
		default:
			break;
		}
	}
}

//=====================================
// ��������
//=====================================
CMenu* CMenu::Create(void)
{
	CMenu* pMenu = new CMenu;

	if (FAILED(pMenu->Init()))
	{
		return nullptr;
	}

	return pMenu;
}