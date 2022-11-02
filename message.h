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

	void SetCountDown(int nNum);
	void CountDown();
	void StartMessage(void);
	void GoalMessage(int nMessageIdx);

	static CMessage* Create();			//��������
	static bool GetStart(void) { return m_bStart; }

private:
	static const int CountDownLife = 60;
	static bool m_bStart;

	int m_nMessageCounter;		// ���b�Z�[�W�\������
	int m_nNum;					// �J�E���g�_�E�����݈ʒu
	bool m_bCountDown;
	bool m_bEndGame;
	CObject_2D* m_pObj2D;
};

#endif // !_MESSAGE_H
