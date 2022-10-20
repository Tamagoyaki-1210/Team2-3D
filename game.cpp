//=============================================================================
//
// �Q�[��
// Author : tanimoto kosuke
//
//=============================================================================
#include "game.h"
//#include "score.h"
//#include "menu.h"
#include "input.h"
#include "application.h"
#include "mode.h"
//#include "fade.h"
#include "object.h"
//#include "effect.h"
//#include "UI.h"
#include "meshfield.h"
#include "player.h"
#include "billboard.h"

bool CGame::m_bPause = true;		//�|�[�Y�g�p����
bool CGame::m_bEndGame = false;		//�Q�[���I������
CMeshField *CGame::m_pField = nullptr;
//CScore *CGame::m_pScore = nullptr;

//=====================================
//�f�t�H���g�R���X�g���N�^
//=====================================
CGame::CGame()
{

}

//=====================================
//�f�X�g���N�^
//=====================================
CGame::~CGame()
{

}

//=====================================
//����������
//=====================================
void CGame::Init()
{
	//UI
	//m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 140.0f, 50.0f, 0.0f));
	//CMenu::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CMenu::TYPE_NONE, CMenu::MODE_GAME);

	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CBillBoard *p = CBillBoard::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f));

	p->SetType(CObject::TYPE_OBSTACLE);
	p->SetSize(10, 10);

	m_pField = CMeshField::Create(D3DXVECTOR3(0.0f, -2.0f, 0.0f));

	m_bPause = false;	//�|�[�Y���g�p
}

//=====================================
//�I������
//=====================================
void CGame::Uninit()
{
	CObject::ReleaseAll();
	//CEffect::ReleaseAll();
	//CUI::ReleaseAll();
	m_bPause = true;	//�|�[�Y�g�p
}

//=====================================
//�X�V����
//=====================================
void CGame::Update()
{
	//CFade *pFade = CMode::GetFade();

	////�t�F�[�h���Ă��Ȃ��ꍇ
	//if (pFade->GetFade() == CFade::FADE_NONE)
	//{
	//	CInput *pInput = CApplication::GetInput();

	//	//P�Ń|�[�Y�؂�ւ�
	//	if (pInput->GetKeyboardTrigger(DIK_P))
	//	{
	//		if (!m_bPause)
	//		{
	//			CSound::PlaySound(SOUND_LABEL_SE_WHISTLE_STOP);
	//		}
	//		else
	//		{
	//			CSound::PlaySound(SOUND_LABEL_SE_WHISTLE_START);
	//		}
	//		m_bPause = !m_bPause;
	//	}

	//	//�Q�[���I�����̏���
	//	if (m_bEndGame == true)
	//	{
	//		CMode *pMode = CApplication::GetMode();

	//		pMode->ChangeMode(CMode::MODE_RESULT);

	//		m_bEndGame = false;

	//		m_pScore->Save();
	//	}
	//}
}

//=====================================
//�`�揈��
//=====================================
void CGame::Draw()
{
	
}
