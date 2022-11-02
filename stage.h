//=============================================================================
//
// stage.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//---------------------------
//�O���錾
//---------------------------
class CMeshfield;
class CPlayer;
class CHalfSphere;

//---------------------------
//�N���X�錾
//---------------------------
class CStage
{
public:
	CStage();
	~CStage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CMeshfield* GetField(void) { return m_pField; }		// ���b�V���t�B�[���h�̎擾����
	static CPlayer* GetPlayer(int nCnt) { return m_pPlayer[nCnt]; }	// �v���C���[�̎擾����

	static CStage* Create(void);			//��������
private:
	static CMeshfield* m_pField;
	static CPlayer* m_pPlayer[PLAYER_MAX];							//�v���C���[�̃C���X�^���X�ւ̃|�C���^
	static CHalfSphere* m_pSphere[PLAYER_MAX];
};

#endif // !_STAGE_H_
