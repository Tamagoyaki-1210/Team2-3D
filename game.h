//=============================================================================
//
// �Q�[��
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
//class CScore;

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
	//static CScore *GetScore() { return m_pScore; }
private:
	static bool m_bPause;
	static bool m_bEndGame;
	static CMeshField *m_pField;
	//static CScore *m_pScore;
};

#endif // !_GAME_H_
