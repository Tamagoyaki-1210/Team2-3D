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
#include "main.h"

//---------------------------
//�O���錾
//---------------------------
class CMeshField;
class CPlayer;

//---------------------------
//�N���X�錾
//---------------------------
class CGame
{
public:
	CGame();
	~CGame();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	static void SetPause(bool bUse) { m_bPause = bUse; }	// �|�[�Y��Ԃ�ݒ肷��
	static void SetEndGame() { m_bEndGame = true; }			// �Q�[���I����ݒ肷��

	static bool GetPause() { return m_bPause; }				// �|�[�Y��Ԏ擾
	static CMeshField *GetField() { return m_pField; }
	static CPlayer* GetPlayer(void) { return m_pPlayer; }	// �v���C���[�̎擾����
private:
	static bool m_bPause;
	static bool m_bEndGame;
	static CMeshField *m_pField;
	static CPlayer* m_pPlayer;							//�v���C���[�̃C���X�^���X�ւ̃|�C���^
};

#endif // !_GAME_H_
