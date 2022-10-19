//=============================================================================
//
// �}�l�[�W���[
// Author : tanimoto kosuke
//
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"
//#include "fade.h"
#include "mode.h"
#include "camera.h"
#include "light.h"

CRenderer *CApplication::m_pRenderer = nullptr;	// �����_���[�|�C���^
CInput *CApplication::m_pInput = nullptr;		// ���̓|�C���^
CTexture *CApplication::m_pTexture = nullptr;	// �摜�|�C���^
CMode *CApplication::m_pMode = nullptr;			// ���[�h�|�C���^
//CSound *CApplication::m_pSound = nullptr;		// �T�E���h�|�C���^
CCamera *CApplication::m_pCamera = nullptr;		// �J�����|�C���^
CLight *CApplication::m_pLight = nullptr;		// ���C�g�|�C���^

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CApplication::CApplication()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CApplication::~CApplication()
{

}

//=====================================
// ����������
//=====================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_pRenderer = new CRenderer;
	m_pInput = new CInput;
	m_pTexture = new CTexture;
	m_pMode = new CMode;
	//m_pSound = new CSound;
	m_pCamera = new CCamera;
	m_pLight = new CLight;

	// �L�[�{�[�h�̏���������
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// true : �E�B���h�E�T�C�Y, false : �S���
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	m_pTexture->Load();

	//�ŏ��̃��[�h
	m_pMode->FirstMode(CMode::MODE_GAME);

	//m_pSound->Init(hWnd);

	m_pCamera->Init();

	m_pLight->Init();

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CApplication::Uninit()
{
	//CObject::ReleaseAll();

	// �摜
	if (m_pTexture != nullptr)
	{
		m_pTexture->Uninit();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// ����
	if (m_pInput != nullptr)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = nullptr;
	}

	// �����_�����O
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

	//// �T�E���h
	//if (m_pSound != nullptr)
	//{
	//	//CSound::StopSound();
	//	//m_pSound->Uninit();
	//	delete m_pSound;
	//	m_pSound = nullptr;
	//}

	// �T�E���h
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//=====================================
//�X�V����
//=====================================
void CApplication::Update()
{
	m_pInput->Update();
	m_pRenderer->Update();
	m_pMode->Update();
	m_pMode->SetMode();
	m_pCamera->Update();
}

//=====================================
//�`�揈��
//=====================================
void CApplication::Draw()
{
	m_pRenderer->Draw();
	m_pMode->Draw();
}