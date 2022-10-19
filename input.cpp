//=============================================================================
//
// ���͏���
// Author : tanimoto kosuke
//
//=============================================================================

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "input.h"

LPDIRECTINPUTDEVICE8 CInput::m_pDevKeyboard = nullptr;
LPDIRECTINPUT8 CInput::m_pInput = nullptr;
BYTE CInput::m_aKeyState[NUM_KEY_MAX] = {};
BYTE CInput::m_aKeyStateTrigger[NUM_KEY_MAX] = {};
BYTE CInput::m_aKeyStateRelease[NUM_KEY_MAX] = {};

//=====================================
//�f�t�H���g�R���X�g���N�^
//=====================================
CInput::CInput()
{
}

//=====================================
//�f�X�g���N�^
//=====================================
CInput::~CInput()
{

}

//=====================================
//���͏����S�Ă̏�����
//=====================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//=====================================
//���͏����S���̏I������
//=====================================
void CInput::Uninit(void)
{
	//�L�[�{�[�h�̏I������
	UninitKeyboard();
}

//=====================================
//���͏����S���̍X�V����
//=====================================
void CInput::Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();
}

//********************************
//�L�[�{�[�h���͏���
//********************************
//=====================================
//�L�[�{�[�h����������
//=====================================
HRESULT CInput::InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevKeyboard->Acquire();

	return S_OK;
}

//=====================================
//�L�[�{�[�h�I������
//=====================================
void CInput::UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̕���
	if (m_pDevKeyboard != NULL)
	{
		m_pDevKeyboard->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=====================================
//�L�[�{�[�h�X�V����
//=====================================
void CInput::UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//�L�[�{�[�h�̓��͏��

										//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = ~m_aKeyState[nCntKey] & aKeyState[nCntKey];	//�L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyStateRelease[nCntKey] = m_aKeyState[nCntKey] & ~aKeyState[nCntKey];	//�L�[�{�[�h�̃����[�X����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];									//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=====================================
//�L�[�{�[�h�̑S�L�[�v���X�����擾
//=====================================
bool CInput::GetKeyboardPress(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (GetKeyboardPress(nCntKey))
		{
			return true;
		}
	}
	return false;
}

//=====================================
//�L�[�{�[�h�̃v���X�����擾
//=====================================
bool CInput::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=====================================
//�L�[�{�[�h�̑S�L�[�g���K�[�����擾
//=====================================
bool CInput::GetKeyboardTrigger(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (GetKeyboardTrigger(nCntKey))
		{
			return true;
		}
	}
	return false;
}

//=====================================
//�L�[�{�[�h�̃g���K�[�����擾
//=====================================
bool CInput::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}