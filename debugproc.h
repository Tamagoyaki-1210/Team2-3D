//============================================================================
//
//
// �f�o�b�O�p
// Author:�J�{�N��
//
//============================================================================
#ifndef _DEBUGPROC_H_						//���̃}�N����`������ĂȂ�������
#define _DEBUGPROC_H_						//2�A�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//****************************************************************************
//�}�N����`
//****************************************************************************
#define MAX_STR		(1024)		//�r���{�[�h�̍ő�ݒu��
#define MAX_LEN		(20)		//�ő�s��

class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void Init();
	void Uninit();

	static void Print(const char *format, ...);
	static void Draw();

	//static CDebugProc *Create(D3DXVECTOR3 pos);
private:
	static LPD3DXFONT m_pFont;
	static char m_aStr[MAX_STR];
	static int m_nLen[MAX_LEN];
};
#endif //!_DEBUGPROC_H_