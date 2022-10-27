//=============================================================================
//
// choice.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _CHOICE_H_
#define _CHOICE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "font.h"

//---------------------------
//�N���X�錾
//---------------------------
class CChoice
{
public:
	enum Choice
	{
		Choice_Start = 0,	//�����[��
		Choice_Finish,		//�����
		Choice_Max
	};
	CChoice();
	~CChoice();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CChoice* Create(void);			//��������
private:
	static const int MaxWordLenght = 24;

	CFont* m_pFont[MaxWordLenght];
	Choice* m_choice;
};

#endif // !_CHOICE_H_
