//=============================================================================
//
// message.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _MESSAGE_H
#define _MESSAGE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"

//---------------------------
//�N���X�錾
//---------------------------
class CMessage
{
public:
	CMessage();
	~CMessage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void GoalMessage(void);

	static CMessage* Create();			//��������

private:
	int m_nMessageCounter;			// ���b�Z�[�W�\������
	CObject_2D* m_pObj2D;
};

#endif // !_MESSAGE_H
