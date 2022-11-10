//=============================================================================
//
// tutorial.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "mode.h"

//---------------------------
//�O���錾
//---------------------------
class CStage;

//---------------------------
//�N���X�錾
//---------------------------
class CTutorial : public CMode
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static void SetEndTutorial();			// �Q�[���I����ݒ肷��
	static bool GetEndTutorial() { return m_bEndTutorial; }

	static CStage* GetStage(void) { return m_pStage; }

	static CTutorial* Create(void);			//��������
private:
	static CStage* m_pStage;
	static bool m_bEndTutorial;
};

#endif // !_GAME_H_
