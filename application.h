//=============================================================================
//
// application.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef APPLICATION_H
#define APPLICATION_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//�O���錾
class CRenderer;
class CInput;
class CInputMouse;
class CSound;
class CFade;
class CCamera;
class CDebugProc;
class CMode;

//�A�v���P�[�V�����̃N���X
class CApplication
{
public:
	enum Mode
	{
		Mode_Title = 0,	//�^�C�g��
		Mode_Game,		//�Q�[��
		Mode_Result,	//���U���g
		Mode_Max
	};

	CApplication();										//�R���X�g���N�^
	~CApplication();									//�f�X�g���N�^
														
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	static CRenderer* GetRenderer(void);				//�����f�B���O�C���X�^���X�̎擾����
	static CInputMouse* GetMouse(void);					//�}�E�X�C���X�^���X�̎擾����
	static HWND GetWindow(void);						//�E�C���h�E�̎擾����
	static CSound* GetSound(void);						//�T�E���h�̎擾����
	static CCamera* GetCamera(void);					//�J�����̎擾����

	static Mode GetMode(void);
	static void SetMode(Mode mode);

private:
	static HWND m_hWnd;									//�N���C�G���g���
	static CRenderer* m_pRenderer;						//�����f�B���O�C���X�^���X�ւ̃|�C���^
	static CInput* m_pInput[2];							//�C���v�b�g�f�o�C�X�ւ̃|�C���^
	static CInputMouse* m_pMouse;						//�}�E�X�C���X�^���X
	static CSound* m_pSound;							//�T�E���h�̃C���X�^���X�ւ̃|�C���^
	static CFade* m_pFade;								//�t�F�[�h�̃C���X�^���X�ւ̃|�C���^
	static CCamera* m_pCamera;							//�J�����̃C���X�^���X�ւ̃|�C���^
	static CMode* m_pMode;								//���[�h�̃C���X�^���X�ւ̃|�C���^

	static CDebugProc* m_pDebug;						//

	static Mode m_mode;		//���݃��[�h

	static bool m_bFade;								//�t�F�[�h���ł��邩�ǂ���
};

#endif // !APPLICATION_H
