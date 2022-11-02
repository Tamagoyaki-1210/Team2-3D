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
	// ���b�Z�[�W���
	enum MESSAGE
	{
		MESSAGE_COUNTDOWN = 0,
		MESSAGE_START,
		MESSAGE_GOAL,
		MESSAGE_WIN,
		MESSAGE_MAX
	};
	CMessage();
	~CMessage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetCountDown(int nNum);
	void StartMessage(void);
	void GoalMessage(int nMessageIdx);
	void WinMessage();

	void Destroy();

	static CMessage* Create();			//��������
	static bool GetStart(void) { return m_bStart; }

private:
	static const int CountDownLife = 60;
	static bool m_bStart;

	int m_nMessageIdx;
	int m_nMessageCounter;		// ���b�Z�[�W�\������
	int m_nNum;					// �J�E���g�_�E�����݈ʒu
	CObject_2D* m_pObj2D;
	MESSAGE m_type;
};

#endif // !_MESSAGE_H
