//=============================================================================
//
// ���[�h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _MODE_H_
#define _MODE_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//---------------------------
//�O���錾
//---------------------------
//class CTitle;
class CGame;
//class CResult;
//class CFade;

//---------------------------
//�N���X�錾
//---------------------------
class CMode
{
public:
	enum MODE
	{
		MODE_NONE = 0,
		//MODE_TITLE,		//�^�C�g��
		MODE_GAME,		//�Q�[��
		//MODE_RESULT,	//���U���g
		MODE_MAX
	};

	CMode();
	~CMode();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetMode();
	MODE GetMode();
	void ChangeMode(MODE mode);
	void FirstMode(MODE mode);

	//static CTitle *GetTitle() { return m_pTitle; }
	static CGame *GetGame() { return m_pGame; }
	//static CResult *GetResult() { return m_pResult; }
	//static CFade *GetFade() { return m_pFade; }
private:
	static MODE m_mode;		//���݃��[�h
	static MODE m_modeNext;	//���̃��[�h
	//static CTitle *m_pTitle;
	static CGame *m_pGame;
	//static CResult *m_pResult;
	//static CFade *m_pFade;
};

#endif // !_MODE_H_
