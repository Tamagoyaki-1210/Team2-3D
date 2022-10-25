//=============================================================================
//
// application.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "application.h"
#include "rendering.h"
#include "object.h"
#include "object2D.h"
#include "input.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "sound.h"
#include "directionalLight.h"
#include "camera.h"
#include "model.h"
#include "player.h"
#include "debugProc.h"
#include "billboard.h"
#include "meshfield.h"
#include "Letter.h"
#include "UIString.h"
#include "animator.h"
#include "mode.h"

//�ÓI�����o�[�ϐ��̐錾
HWND CApplication::m_hWnd;
CRenderer* CApplication::m_pRenderer = nullptr;			//�����f�B���O�C���X�^���X�ւ̃|�C���^
CInput* CApplication::m_pInput[2] = {};					//�C���v�b�g�C���X�^���X�ւ̃|�C���^
CInputMouse* CApplication::m_pMouse = nullptr;			//�}�E�X�C���X�^���X�ւ̃|�C���^
CSound* CApplication::m_pSound = nullptr;
CFade* CApplication::m_pFade = nullptr;
CCamera* CApplication::m_pCamera = nullptr;
bool CApplication::m_bFade = false;
CMode *CApplication::m_pMode = nullptr;					// ���[�h�ւ̃|�C���^
CDebugProc* CApplication::m_pDebug = nullptr;


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

	// ���[�h�C���X�^���X�̐�������
	m_pMode = new CMode;

	//�ŏ��̃��[�h
	m_pMode->FirstMode(CMode::MODE_GAME);

	m_pDebug = CDebugProc::Create();

	//�e�N�X�`���S�������[�h����
	CObject_2D::LoadTextures();

	//���f���S�������[�h����
	CModel::LoadAllModels();

	CAnimator::LoadAllAnimation();

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

	//�L�[�{�[�h�̏���������
	/*if (FAILED(m_pMouse->Init(hInstance, hWnd, GUID_SysMouse)))
	{
		return -1;
	}*/

	m_pSound = CSound::Create(hWnd);

	/*if (m_pSound != nullptr)
	{
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
	}*/

	//m_pFade = CFade::Create();
	m_bFade = false;

	CLight::ReleaseAll();
	CDirectionalLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(2, -5, 2));

	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, -200.0f, 300.0f));

	CObject_2D* pObj2D = CObject_2D::Create();
	pObj2D->SetPos(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	pObj2D->SetSize(D3DXVECTOR2(20.0f, 20.0f));
	pObj2D->SetTexture(CObject::TEXTURE_LETTERS);
	pObj2D->SetTextureParameter(5, 13, 2, 60);
	pObj2D->SetAnimPattern(15);
	pObj2D->SetAnimationBase(15);

	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-1000.0f, -150.0f, 1000.0f), Vec3Null, D3DXVECTOR2(50.0f, 50.0f), 30, 30, 3);
	pField->SetTexture(CObject::TEXTURE_BLOCK);
	pField->SetTextureTiling(0.33f);

	CModel::Create(CModel::MODEL_JEWEL_TEAR, D3DXVECTOR3(0.0f, -100.0f, -150.0f));
	CModel::Create(CModel::MODEL_JEWEL_TEAR, D3DXVECTOR3(0.0f, -100.0f, 150.0f));

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, -100.0f, -100.0f));

	CBillboard* pBillboard = CBillboard::Create(D3DXVECTOR3(-150.0f, 0.0f, 300.0f), D3DXVECTOR2(50.0f, 50.0f), 3);
	pBillboard->SetTexture(CObject::TEXTURE_BLOCK);

	CLetter::Create(D3DXVECTOR3(200.0f, 100.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 'r', 5);

	CLetter::Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 4, 5);

	CUIString::Create(D3DXVECTOR3(100.0f, 200.0f, 0.0f), D3DXVECTOR2(250.0f, 25.0f), D3DXCOLOR(0.2f, 1.0f, 0.5f, 1.0f), "Sentence A, 125 $%&");

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

	return S_OK;
}

//�I������
void CApplication::Uninit(void)
{
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

	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	if (m_pDebug != nullptr)
	{
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	//�I�u�W�F�N�g�S�̂̏I������
	CObject::ReleaseAll();

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
	CDebugProc::Print("\n�A���[�L�[�Ŏ��_�̈ړ�\n�}�E�X�Œ����_�̈ړ�\nWASD�L�[�Ń��f���̈ړ�");

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

	if (m_pMode != nullptr)
	{
		m_pMode->Update();
		m_pMode->SetMode();
	}

	if (m_pMouse != nullptr)
	{
		m_pMouse->Update();
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	/*if (CInputKeyboard::GetKeyboardTrigger(DIK_C))
	{
		CObject_2D* pObj2D = CObject_2D::Create();
		pObj2D->SetPos(D3DXVECTOR3((float)CObject::random(50, SCREEN_WIDTH - 50), (float)CObject::random(50, SCREEN_HEIGHT - 50), 0.0f));
		pObj2D->SetSize(D3DXVECTOR2(50.0f, 50.0f));
		pObj2D->SetTexture(CObject::TEXTURE_LETTERS);
		pObj2D->SetTextureParameter(1, 13, 2, INT_MAX);
		pObj2D->SetAnimPattern(CObject::random(0, 25));
		pObj2D->SetPriority(5);
	}
	if (CInputKeyboard::GetKeyboardTrigger(DIK_X))
	{
		CObject::DebugDestroy();
	}

	if (m_pStr != nullptr)
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_Z))
		{
			m_pStr->Release();
			m_pStr = nullptr;
		}
	}*/
}

//�`�揈��
void CApplication::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
	if (m_pMode != nullptr)
	{
		m_pMode->Draw();
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

CMode* CApplication::GetMode(void)
{
	return m_pMode;
}