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

	//static void SetPause(bool bUse) { m_bPause = bUse; }	// �|�[�Y��Ԃ�ݒ肷��
	static void SetEndGame() { m_bEndGame = true; }			// �Q�[���I����ݒ肷��

	//static bool GetPause() { return m_bPause; }				// �|�[�Y��Ԏ擾

private:
	//static bool m_bPause;
	static bool m_bEndGame;
};

#endif // !_GAME_H_
