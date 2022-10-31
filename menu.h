//=============================================================================
//
// menu.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _MENU_H_
#define _MENU_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "choice.h"

//---------------------------
// �O���錾
//---------------------------
class CChoice;

//---------------------------
//�N���X�錾
//---------------------------
class CMenu
{
public:
	CMenu();
	~CMenu();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Input(void);

	static CMenu* Create(void);
private:
	static const int MaxChoice = 10;			// �I������

	static int m_nNumAll;						// �I�����̑S�̐�
	static int m_nSelectNum;					// ���ݑI������Ă���ԍ�
	static CChoice* m_pChoice[MaxChoice];
};

#endif // !_MENU_H_
