//=============================================================================
//
// game.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "game.h"
#include "inputKeyboard.h"
#include "application.h"

//bool CGame::m_bPause = true;		//�|�[�Y�g�p����
bool CGame::m_bEndGame = false;		//�Q�[���I������

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CGame::CGame()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CGame::~CGame()
{

}

//=====================================
// ����������
//=====================================
HRESULT CGame::Init(void)
{
	//m_bPause = false;	//�|�[�Y���g�p

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CGame::Uninit(void)
{
	//m_bPause = true;
}

//=====================================
// �X�V����
//=====================================
void CGame::Update(void)
{
	////P�Ń|�[�Y�؂�ւ�
	//if (pInput->GetKeyboardTrigger(DIK_P))
	//{
	//	if (!m_bPause)
	//	{
	//		CSound::PlaySound(SOUND_LABEL_SE_WHISTLE_STOP);
	//	}
	//	else
	//	{
	//		CSound::PlaySound(SOUND_LABEL_SE_WHISTLE_START);
	//	}
	//	m_bPause = !m_bPause;
	//}

	//�Q�[���I�����̏���
	if (m_bEndGame == true)
	{
		CApplication::SetMode(CApplication::Mode_Result);
		m_bEndGame = false;
	}
}