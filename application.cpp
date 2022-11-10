//=============================================================================
//
// application.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "application.h"
#include "rendering.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "inputPad.h"
#include "directionalLight.h"
#include "camera.h"
#include "model.h"
#include "debugProc.h"
#include "animator.h"
#include "title.h"
#include "playerSelect.h"
#include "stageSelect.h"
#include "gamerace.h"
#include "fade.h"
#include "menu.h"
#include "hitbox.h"
#include "score.h"
#include "tutorial.h"

//�ÓI�����o�[�ϐ��̐錾
HWND CApplication::m_hWnd;
CRenderer* CApplication::m_pRenderer = nullptr;			//�����f�B���O�C���X�^���X�ւ̃|�C���^
CInput* CApplication::m_pInput[2] = {};					//�C���v�b�g�C���X�^���X�ւ̃|�C���^
CInputMouse* CApplication::m_pMouse = nullptr;			//�}�E�X�C���X�^���X�ւ̃|�C���^
CInputPad* CApplication::m_pPad = nullptr;
CSound* CApplication::m_pSound = nullptr;
CFade* CApplication::m_pFade = nullptr;
CCamera* CApplication::m_pCamera = nullptr;
CMode* CApplication::m_pMode = nullptr;					// ���[�h�ւ̃|�C���^
CMenu* CApplication::m_pMenu = nullptr;					// ���j���[�ւ̃|�C���^
CDebugProc* CApplication::m_pDebug = nullptr;
CApplication::Mode CApplication::m_mode = CApplication::Mode_Title;
CApplication::Mode CApplication::m_modeNext = CApplication::Mode_Title;
bool CApplication::m_bPause = false;
int CApplication::m_nStageSelect = 0;

//�R���X�g���N�^
CApplication::CApplication()
{
	
}

//�f�X�g���N�^
CApplication::~CApplication()
{
	
}

//����������
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd;

	//�����f�B���O�C���X�^���X�̐�������
	if (m_pRenderer == nullptr)
	{//�|�C���^��null�ł͂Ȃ�������
		m_pRenderer = new CRenderer;
	}

	//�����f�B���O�C���X�^���X�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}

	m_pDebug = CDebugProc::Create();

	//�e�N�X�`���S�������[�h����
	CObject_2D::LoadTextures();

	//���f���S�������[�h����
	CModel::LoadAllModels();

	CAnimator::LoadAllAnimation();

	m_pSound = CSound::Create(hWnd);


	CLight::ReleaseAll();
	CDirectionalLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(2, -5, 2));
	CDirectionalLight::Create(D3DXCOLOR(0.75f, 0.75f, 0.75f, 0.75f), D3DXVECTOR3(-0.2f, 0.2f, 1.0f));

	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, -200.0f, 100.0f));

	// ���[�h�C���X�^���X�̐�������
	m_pMode = CTitle::Create();
	m_mode = Mode_Title;
	m_modeNext = Mode_Title;
	m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	// �t�F�[�h����
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create();
		m_pFade->SetFade();
	}

	//�L�[�{�[�h�C���X�^���X�̐�������
	m_pInput[0] = new CInputKeyboard;

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pInput[0]->Init(hInstance, hWnd, GUID_SysKeyboard)))
	{
		return -1;
	}

	m_pMouse = new CInputMouse;

	if (m_pMouse != nullptr)
	{
		m_pMouse->Init(hInstance, hWnd, GUID_SysMouse);
	}

	m_pPad = new CInputPad;

	if (m_pPad != nullptr)
	{
		m_pPad->Init(hInstance, hWnd, GUID_SysMouse);
	}

	//�L�[�{�[�h�̏���������
	/*if (FAILED(m_pMouse->Init(hInstance, hWnd, GUID_SysMouse)))
	{
		return -1;
	}*/

	// ���j���[����
	if (m_pMenu == nullptr)
	{
		m_pMenu = CMenu::Create();
	}


	//m_pSphear->Init();

	//FILE*pFile;				//�t�@�C���|�C���^��錾����

	//						//�t�@�C�����J��
	//pFile = fopen("data\\charData.txt", "wb");

	//if (pFile != NULL)
	//{//�t�@�C�����J�����ꍇ
	// //�t�@�C���Ƀ����L���O���������o��

	//	char cData = 33;		//for (int nCnt = 0; nCnt < 93; nCnt++)
	//	char dData[100] = {};

	//	for (int nCnt = 0; nCnt < 93; nCnt++)
	//	{
	//		dData[nCnt] = cData;

	//		fwrite(&cData, sizeof(char), 1, pFile);

	//		cData++;
	//	}

	//	//�t�@�C�������
	//	fclose(pFile);

	//	int a = 0;
	//}
	//else
	//{//�t�@�C�����J���Ȃ������ꍇ
	//	printf("XXXXX �Z�[�u�t�@�C�����J���܂���ł��� XXXXX");
	//}

	m_bPause = false;	//�|�[�Y�𖢎g�p�ɂ���

	m_nStageSelect = 0;

	return S_OK;
}

//�I������
void CApplication::Uninit(void)
{
	CScore::Clear();

	//�����f�B���O�C���X�^���X�̔j��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// ���[�h
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	//�C���v�b�g�f�o�C�X�̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Uninit();
			delete m_pInput[nCnt];
			m_pInput[nCnt] = nullptr;
		}
	}

	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	if (m_pPad != nullptr)
	{
		m_pPad->Uninit();
		delete m_pPad;
		m_pPad = nullptr;
	}

	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	if (m_pMenu != nullptr)
	{
		m_pMenu->Uninit();
		delete m_pMenu;
		m_pMenu = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pDebug != nullptr)
	{
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	//�I�u�W�F�N�g�S�̂̏I������
	CObject::ReleaseAll();

	//�q�b�g�{�b�N�X�̔j������
	CHitbox::ReleaseAll();

	CLight::ReleaseAll();

	//�e�N�X�`���S���̔j��
	CObject_2D::DestroyLoadedTextures();

	CAnimator::DestroyLoadedAnimation();

	//���f���S���j���̔j������
	CModel::DestroyAllModels();
}

//�X�V����
void CApplication::Update(void)
{
	//CDebugProc::Print("\n�A���[�L�[�Ŏ��_�̈ړ�\n�}�E�X�Œ����_�̈ړ�\nWASD�L�[�Ń��f���̈ړ�\n");

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Update();
		}
	}

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	if (m_pFade != nullptr)
	{
		//�t�F�[�h���ǂݍ��܂�Ă��Ȃ��ꍇ
		if (m_pFade->GetFade() != CFade::FADE_NONE)
		{
			m_pFade->Update();
			ChangeMode();
		}
	}

	if (m_pMode != nullptr)
	{
		m_pMode->Update();
	}

	if (m_pMenu != nullptr)
	{
		m_pMenu->Update();
	}

	if (m_pMouse != nullptr)
	{
		m_pMouse->Update();
	}

	if (m_pPad != nullptr)
	{
		m_pPad->Update();
	}

	// �|�[�Y���łȂ��ꍇ�̂ݍX�V
	if (m_bPause == false)
	{
		if (m_pCamera != nullptr)
		{
			m_pCamera->Update();
		}
	}
}

//�`�揈��
void CApplication::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

CRenderer* CApplication::GetRenderer(void)
{
	return m_pRenderer;
}

CInputMouse* CApplication::GetMouse(void)
{
	return m_pMouse;
}

CInputPad * CApplication::GetPad(void)
{
	return m_pPad;
}

HWND CApplication::GetWindow(void)
{
	return m_hWnd;
}

//�T�E���h�̎擾����
CSound* CApplication::GetSound(void)
{
	return m_pSound;
}

CCamera* CApplication::GetCamera(void)
{
	return m_pCamera;
}

CFade* CApplication::GetFade(void)
{
	return m_pFade;
}

//=====================================
// ���[�h�擾����
//=====================================
CApplication::Mode CApplication::GetMode(void)
{
	return m_mode;
}

//=====================================
// ���[�h�ݒ菈��
//=====================================
void CApplication::SetMode(Mode mode)
{
	// �t�F�[�h�؂�ւ���Ԃł͂Ȃ��ꍇ
	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		m_modeNext = mode;
		m_pFade->SetFade();
	}
}

//=====================================
// ���[�h�؂�ւ�����
//=====================================
void CApplication::ChangeMode()
{
	if (m_pFade->GetFade() != CFade::FADE_CHANGE)
	{// �t�F�[�h�؂�ւ���Ԃ���Ȃ��ꍇ
		return;
	}

	// ���݃��[�h�̏I��
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	m_pMenu->Uninit();

	CObject::ReleaseAll();
	CHitbox::ReleaseAll();

	m_bPause = false;		// �|�[�Y�𖢎g�p�ɂ���

	// ���̃��[�h���X�e�[�W�I���łȂ����
	if (m_modeNext != Mode_StageSelect)
	{
		if (m_pSound != nullptr)
		{
			m_pSound->Stop();
		}
	}

	// ���[�h�𐶐�����
	switch (m_modeNext)
	{
	case CApplication::Mode_Title:
		m_pMode = CTitle::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		break;
	case CApplication::Mode_PlayerSelect:
		m_pMode = CPlayerSelect ::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_SELECT);
		break;
	case CApplication::Mode_StageSelect:
		m_pMode = CStageSelect::Create();
		break;
	case CApplication::Mode_Game_Race:
		m_pMode = CGameRace::Create();
		if (m_nStageSelect == 0)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME01);
		}
		else if (m_nStageSelect == 1)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME02);
		}
		else if (m_nStageSelect == 2)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME03);
		}
		break;
	case CApplication::Mode_Tutorial:
		m_pMode = CTutorial::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME01);
		break;
	default:
		break;
	}
	m_mode = m_modeNext;

	m_pMenu->Init();
}

//=====================================
// �|�[�Y�擾����
//=====================================
bool CApplication::GetPause()
{
	return m_bPause;
}

//=====================================
// �|�[�Y�ݒ菈��
//=====================================
void CApplication::SetPause(const bool bPause)
{
	m_bPause = bPause;
}