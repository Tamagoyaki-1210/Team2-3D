//=============================================================================
//
// mode.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "mode.h"
//#include "title.h"
#include "game.h"
//#include "result.h"
//#include "fade.h"
//#include "menu.h"

#include <assert.h>

CMode::MODE CMode::m_mode = MODE_NONE;
CMode::MODE CMode::m_modeNext = MODE_NONE;
//CTitle *CMode::m_pTitle = nullptr;		//�^�C�g���|�C���^
CGame *CMode::m_pGame = nullptr;		//�Q�[���|�C���^
//CResult *CMode::m_pResult = nullptr;	//���U���g�|�C���^
//CFade *CMode::m_pFade = nullptr;		// �t�F�[�h�|�C���^
//=====================================
//�f�t�H���g�R���X�g���N�^
//=====================================
CMode::CMode()
{
	//m_pTitle = new CTitle;
	m_pGame = new CGame;
	//m_pResult = new CResult;
}

//=====================================
//�f�X�g���N�^
//=====================================
CMode::~CMode()
{

}

//=====================================
//����������
//=====================================
void CMode::Init()
{

}

//=====================================
//�I������
//=====================================
void CMode::Uninit()
{
	////�^�C�g��
	//if (m_pTitle != nullptr)
	//{
	//	m_pTitle->Uninit();
	//	delete m_pTitle;
	//	m_pTitle = nullptr;
	//}
	//�Q�[��
	if (m_pGame != nullptr)
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = nullptr;
	}
	////���U���g
	//if (m_pResult != nullptr)
	//{
	//	m_pResult->Uninit();
	//	delete m_pResult;
	//	m_pResult = nullptr;
	//}
}

//=====================================
//�X�V����
//=====================================
void CMode::Update()
{
	switch (m_mode)
	{//�ǂ̃��[�h��
	//case MODE_TITLE:
	//	m_pTitle->Update();
	//	break;
	case MODE_GAME:
		m_pGame->Update();
		break;
	//case MODE_RESULT:
	//	m_pResult->Update();
	//	break;
	case MODE_NONE:
		/* �������� */
		break;
	default:
		assert(false);
		break;
	}
}

//=====================================
//�`�揈��
//=====================================
void CMode::Draw()
{
	switch (m_mode)
	{//�ǂ̃��[�h��
	//case MODE_TITLE:
	//	m_pTitle->Draw();
	//	break;
	case MODE_GAME:
		m_pGame->Draw();
		break;
	//case MODE_RESULT:
	//	m_pResult->Draw();
	//	break;
	case MODE_NONE:
		/* �������� */
		break;
	default:
		assert(false);
		break;
	}
}

//=====================================
//���[�h�̐ݒ�
//=====================================
void CMode::SetMode()
{
	//CFade::FADE fade = m_pFade->GetFade();

	if (m_modeNext == MODE_NONE)
	{//���̃��[�h�����܂��Ă��Ȃ��ꍇ
		return;
	}
	
	//if (fade == CFade::FADE_NONE)
	//{//�������Ă��Ȃ���ԂȂ�@
	//	m_pFade->StartFadeOut();
	//}
	//if (fade != CFade::FADE_CHANGE)
	//{//�t�F�[�h�C����Ԃ���Ȃ�
	//	return;
	//}

	//float fAlpha = m_pFade->GetAlpha();

	switch (m_mode)
	{//���݃��[�h�̏I��
	//case MODE_TITLE:
	//	CSound::StopSound(SOUND_LABEL_BGM_TITLE);
	//	m_pTitle->Uninit();
	//	break;
	case MODE_GAME:
		//CSound::StopSound(SOUND_LABEL_BGM_TITLE);
		m_pGame->Uninit();
		break;
	//case MODE_RESULT:
	//	if (CStage::GetClear() == false)
	//	{
	//		CSound::StopSound(SOUND_LABEL_BGM_RESULT);
	//	}
	//	else
	//	{
	//		CSound::StopSound(SOUND_LABEL_BGM_CLEAR);
	//	}
	//	m_pResult->Uninit();
	//	break;
	case MODE_NONE:
		/* �������� */
		break;
	default:
		assert(false);
		break;
	}

	switch (m_modeNext)
	{//���̃��[�h�̏�����
	//case MODE_TITLE:
	//	CSound::PlaySound(SOUND_LABEL_BGM_TITLE);
	//	m_pTitle->Init();
	//	break;
	case MODE_GAME:
		//CSound::PlaySound(SOUND_LABEL_BGM_TITLE);
		m_pGame->Init();
		break;
	//case MODE_RESULT:
	//	if (CStage::GetClear() == false)
	//	{
	//		CSound::PlaySound(SOUND_LABEL_BGM_RESULT);
	//	}
	//	else
	//	{
	//		CSound::PlaySound(SOUND_LABEL_BGM_CLEAR);
	//	}
	//	m_pResult->Init();
	//	break;
	case MODE_NONE:
		/* �������� */
		break;
	default:
		assert(false);
		break;
	}
	m_mode = m_modeNext;	//���݂̉��(���[�h)��؂�ւ���
	m_modeNext = MODE_NONE;

	//m_pFade = CFade::Create(fAlpha, fade);
}

//=====================================
//���[�h�̕ύX
//=====================================
void CMode::ChangeMode(MODE mode)
{
	m_modeNext = mode;
}

//=====================================
//�ŏ��̃��[�h�ݒ�
//=====================================
void CMode::FirstMode(MODE mode)
{
	m_modeNext = mode;
	//m_pFade = CFade::Create(0.0f, CFade::FADE_NONE);
}

//=====================================
//���[�h�擾����
//=====================================
CMode::MODE CMode::GetMode()
{
	return m_mode;
}