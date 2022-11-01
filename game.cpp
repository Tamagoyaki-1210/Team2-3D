//=============================================================================
//
// game.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "game.h"
#include "inputKeyboard.h"
#include "application.h"

bool CGame::m_bPause = false;		//�|�[�Y�g�p����
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
	return S_OK;
}

//=====================================
// �I������
//=====================================
void CGame::Uninit(void)
{
	m_bEndGame = false;
	m_bPause = false;
}

//=====================================
// �X�V����
//=====================================
void CGame::Update(void)
{
	//P�Ń|�[�Y�؂�ւ�
	if (CInputKeyboard::GetKeyboardTrigger(DIK_P))
	{
		m_bPause = !m_bPause;	//�|�[�Y�؂�ւ�����
	}

	//�Q�[���I�����̏���
	if (m_bEndGame == true)
	{
		CApplication::SetMode(CApplication::Mode_Result);
		m_bEndGame = false;
	}
}