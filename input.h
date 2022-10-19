//=============================================================================
//
// ���͏���
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//***********************************************
//���C�u�����[�t�@�C���̃����N
//***********************************************
#pragma comment(lib,"dxguid.lib")	//�ŗLID�iGUID�j���o�^����Ă��郉�C�u����
#pragma comment(lib,"dinput8.lib")	//���͏����Ɏg�p(�L�[�{�[�h)
#pragma comment(lib,"xinput.lib")	//���͏����Ɏg�p(�W���C�p�b�h)

//---------------------------
//�}�N���ϐ�
//---------------------------
#define NUM_KEY_MAX		(256)	//�L�[�̍ő吔(�L�[�{�[�h)
#define MOUSE_KEY_MAX	(8)		//�L�[�̍ő吔(�}�E�X)

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "main.h"
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

class CInput
{
public:
	CInput();
	~CInput();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	//�L�[�{�[�h
	bool GetKeyboardPress(void);
	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(void);
	bool GetKeyboardTrigger(int nKey);

private:
	//�L�[�{�[�h
	HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	void UninitKeyboard(void);
	void UpdateKeyboard(void);
	
	static LPDIRECTINPUTDEVICE8 m_pDevKeyboard;		//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	static LPDIRECTINPUT8 m_pInput;
	static BYTE m_aKeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̃v���X���
	static BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	//�L�[�{�[�h�̃g���K�[���
	static BYTE m_aKeyStateRelease[NUM_KEY_MAX];	//�L�[�{�[�h�̃����[�X���
};

#endif
