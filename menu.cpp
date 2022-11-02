//=============================================================================
//
// menu.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "menu.h"
#include "Application.h"
#include "mode.h"
#include "fontString.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "game.h"
#include "fade.h"

int CMenu::m_nNumAll = 0;
int CMenu::m_nSelectNum = 0;
CFontString* CMenu::m_pChoice[MaxChoice] = {};
CFontString* CMenu::m_pPause = nullptr;
CObject_2D* CMenu::m_pObj2D = nullptr;

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

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�X�^�[�g");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�����");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();
		break;
	case CApplication::Mode_Game_Race:
		break;
	case CApplication::Mode_Result:
		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "���g���C");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�^�C�g���ɂ��ǂ�");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();
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
			m_pChoice[nCnt] = nullptr;
		}
	}

	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		m_pPause = nullptr;
	}

	if (m_pObj2D != nullptr)
	{
		m_pObj2D->Release();
		m_pObj2D = nullptr;
	}

	m_nSelectNum = 0;
	m_nNumAll = 0;
}

//=====================================
// �X�V����
//=====================================
void CMenu::Update(void)
{
	if (CApplication::GetMode() == CApplication::Mode_Game_Race)
	{
		// �|�[�Y���łȂ��ꍇ�̂ݍX�V
		if (CApplication::GetPause() == true)
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
	else
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
	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
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
					CApplication::SetMode(CApplication::Mode_PlayerSelect);
				}
				else if (m_nSelectNum == 1)
				{
					ExitExe();
				}
				break;
			case CApplication::Mode_Game_Race:
				if (m_nSelectNum == 0)
				{
					CApplication::SetPause(false);
					PauseChange(false);
				}
				else if (m_nSelectNum == 1)
				{
					CApplication::SetMode(CApplication::Mode_Game_Race);
				}
				else if (m_nSelectNum == 2)
				{
					CApplication::SetMode(CApplication::Mode_Title);
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
}

//=====================================
// �|�[�Y�I��������
//=====================================
void CMenu::PauseChange(bool bPause)
{
	if (bPause == true)
	{
		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�Â���");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "���Ȃ���");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�^�C�g���ɂ��ǂ�");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();

		m_pPause = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), "�|�[�Y");

		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		m_pObj2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.1f));
		m_pObj2D->SetTexture(CObject::TEXTURE_NULL);
		m_pObj2D->SetPriority(4);
	}
	else
	{
		for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
		{
			if (m_pChoice[nCnt] != nullptr)
			{
				m_pChoice[nCnt]->Uninit();
				m_pChoice[nCnt] = nullptr;
			}
		}

		if (m_pPause != nullptr)
		{
			m_pPause->Uninit();
			m_pPause = nullptr;
		}

		if (m_pObj2D != nullptr)
		{
			m_pObj2D->Release();
			m_pObj2D = nullptr;
		}

		m_nSelectNum = 0;
		m_nNumAll = 0;
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