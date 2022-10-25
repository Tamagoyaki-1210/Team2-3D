//=============================================================================
//
// game.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "mode.h"

//---------------------------
//�O���錾
//---------------------------
class CMeshfield;
class CPlayer;

//---------------------------
//�N���X�錾
//---------------------------
class CGame : public CMode
{
public:
	CGame();
	~CGame();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static void SetPause(bool bUse) { m_bPause = bUse; }	// �|�[�Y��Ԃ�ݒ肷��
	static void SetEndGame() { m_bEndGame = true; }			// �Q�[���I����ݒ肷��

	static bool GetPause() { return m_bPause; }				// �|�[�Y��Ԏ擾
	static CMeshfield* GetField(void) { return m_pField; }		// ���b�V���t�B�[���h�̎擾����
	static CPlayer* GetPlayer(void) { return m_pPlayer; }	// �v���C���[�̎擾����

	static CGame* Create(void);			//��������
private:
	static bool m_bPause;
	static bool m_bEndGame;
	static CMeshfield* m_pField;
	static CPlayer* m_pPlayer;							//�v���C���[�̃C���X�^���X�ւ̃|�C���^
};

#endif // !_GAME_H_
