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
	static CPlayer* GetPlayer(void) { return m_pPlayer; }	// �v���C���[�̎擾����

	static CGameRace* Create(void);			//��������
private:
	static CMeshfield* m_pField;
	static CPlayer* m_pPlayer;							//�v���C���[�̃C���X�^���X�ւ̃|�C���^
};

#endif // !_GAMERACE_H_
