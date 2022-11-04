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
class CMessage;

//---------------------------
//�N���X�錾
//---------------------------
class CStage
{
public:
	//�X�e�[�W�̎��
	enum StageType
	{
		STAGE_TYPE_1 = 0,
		STAGE_TYPE_MAX
	};

	//��Q���̎��
	enum ModelType
	{
		MODEL_SPIKEBALL = 0,
		MODEL_TYPE_MAX
	};

	CStage();
	~CStage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void Load(void);

	static void SetModelType(D3DXVECTOR3 pos, ModelType type);

	static CMeshfield* GetField(void) { return m_pField; }			// ���b�V���t�B�[���h�̎擾����
	static CPlayer* GetPlayer(int nCnt) { return m_pPlayer[nCnt]; }	// �v���C���[�̎擾����
	static CMessage* GetMsg(void) { return m_pMessage; }

	static CStage* Create(void);			//��������

	void GameResult();
	static bool GetResult() { return m_bResult; }

	static void ScoreComparison();

private:
	//int m_nSelectStage;										// ���ݑI������Ă���X�e�[�W
	static char* m_pStagePass[STAGE_TYPE_MAX];				//�X�e�[�W�̊O���t�@�C���̑��΃p�X
	static ModelType m_ModelType;

	static CMeshfield* m_pField;
	static CPlayer* m_pPlayer[PLAYER_MAX];					//�v���C���[�̃C���X�^���X�ւ̃|�C���^
	static CHalfSphere* m_pSphere[PLAYER_MAX];
	static CMessage* m_pMessage;

	static bool m_bResult;
};

#endif // !_STAGE_H_

