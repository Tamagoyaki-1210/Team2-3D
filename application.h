//=============================================================================
//
// �A�v���P�[�V����
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_ 

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <d3dx9.h>

//---------------------------
//�O���錾
//---------------------------
class CRenderer;
class CInput;
class CTexture;
class CMode;
class CFade;
//class CSound;
class CCamera;
class CLight;

//---------------------------
//�N���X�錾
//---------------------------
class CApplication
{
public:
	CApplication();
	~CApplication();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	static CRenderer *GetRenderer() { return m_pRenderer; }	//�����_���[�擾����
	static CInput *GetInput() { return m_pInput; }			//���͎擾����
	static CTexture *GetTexture() { return m_pTexture; }	//�摜�擾����
	static CMode *GetMode() { return m_pMode; }				//���[�h�擾����
	//static CSound *GetSound() { return m_pSound; }		//�T�E���h�擾����
	static CCamera *GetCamera() { return m_pCamera; }		//�J�����擾����
	static CLight *GetLight() { return m_pLight; }			//�J�����擾����
private:
	static CRenderer *m_pRenderer;
	static CInput *m_pInput;
	static CTexture *m_pTexture;
	static CMode *m_pMode;
	//static CSound *m_pSound;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
};

#endif // !_APPLICATION_H_
