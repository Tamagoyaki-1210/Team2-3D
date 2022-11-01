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
class CMeshfield;
class CPlayer;
class CHalfSphere;
class CMessage;

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

	static CMeshfield* GetField(void) { return m_pField; }		// ���b�V���t�B�[���h�̎擾����
	static CPlayer* GetPlayer(int nCnt) { return m_pPlayer[nCnt]; }	// �v���C���[�̎擾����
	static CMessage* Get(void) { return m_pMessage; }

	static CGameRace* Create(void);			//��������
private:
	static CMeshfield* m_pField;
	static CPlayer* m_pPlayer[PLAYER_MAX];							//�v���C���[�̃C���X�^���X�ւ̃|�C���^
	static CHalfSphere* m_pSphere[PLAYER_MAX];
	static CMessage* m_pMessage;
};

#endif // !_GAMERACE_H_

