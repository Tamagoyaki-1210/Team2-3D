//=============================================================================
//
// gamerace.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _GAMERACE_H_
#define _GAMERACE_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "game.h"

//---------------------------
//�O���錾
//---------------------------
class CMessage;
class CStage;

//---------------------------
//�N���X�錾
//---------------------------
class CGameRace : public CGame
{
public:
	CGameRace();
	~CGameRace();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static CMessage* Get(void) { return m_pMessage; }

	static CGameRace* Create(void);			//��������
private:
	static CMessage* m_pMessage;
	static CStage* m_pStage;
};

#endif // !_GAMERACE_H_

