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
class CMeshfield;
class CPlayer;
class CMessage;


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

	static CMeshfield* GetField(void) { return m_pField; }			// ���b�V���t�B�[���h�̎擾����
	static CPlayer* GetPlayer(int nCnt) { return m_pPlayer[nCnt]; }	// �v���C���[�̎擾����
	static CMessage* GetMsg(void) { return m_pMessage; }

	static CTutorial* Create(void);			//��������
private:
	static CMeshfield* m_pField;
	static CPlayer* m_pPlayer[PLAYER_MAX];					//�v���C���[�̃C���X�^���X�ւ̃|�C���^
	static CMessage* m_pMessage;

	static bool m_bEndTutorial;
};

#endif // !_GAME_H_