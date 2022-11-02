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
// �f�t�H���g�R���X�g���N�^
//=====================================
CGameRace::CGameRace()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CGameRace::~CGameRace()
{

}

//=====================================
// ����������
//=====================================
HRESULT CGameRace::Init(void)
{
    CGame::Init();

	m_pStage = CStage::Create();

	// ���b�Z�[�W�̐���
	m_pMessage = CMessage::Create();

	// �J�E���g�_�E�����b�Z�[�W�\��
	m_pMessage->SetCountDown(3);

	//m_pMessage->GoalMessage();

    return S_OK;
}

//=====================================
// �I������
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
// �X�V����
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

    CDebugProc::Print("\n[F2] : �f�o�b�O���[�h�ֈړ�\n");

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_F2))
		{// F2�L�[����������
			CApplication::SetMode(CApplication::Mode_Game_Debug);
		}
		if (CInputKeyboard::GetKeyboardTrigger(DIK_BACK))
		{// Enter�L�[����������
			SetEndGame();
		}
		if (CInputKeyboard::GetKeyboardTrigger(DIK_G))
		{// G�L�[����������
			m_pMessage->GoalMessage(0);
		}
	}

#endif // _DEBUG
}

//=====================================
// ��������
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