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
		STAGE_TYPE_2,
		STAGE_TYPE_3,
		STAGE_TYPE_MAX
	};

	//���b�V���t�B�[���h�̎��
	enum FieldType
	{
		FIELD_NORMAL = 0,
		FIELD_SRIP,
		FIELD_TYPE_MAX
	};

	//��Q���̎��
	enum ModelType
	{
		MODEL_SPIKEBALL = 0,
		MODEL_BOUNCEPOLE,
		MODEL_TRAMPOLINE,
		MODEL_TYPE_MAX
	};

	//���̎��
	enum FloorType
	{
		FLOOR_LAVA = 0,
		FLOOR_SLIP,
		FLOOR_TYPE_MAX
	};

	//�����I�u�W�F�N�g�̎��
	enum SpawnerType
	{
		SPAWNER_FALLSTONE = 0,
		SPAWNER_ICEPILLAR,
		SPAWNER_TYPE_MAX
	};

	CStage();
	~CStage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void Load(void);

	static void SetFieldType(D3DXVECTOR3 pos, int line, float tiling, char* str, FieldType type);
	static void SetModelType(D3DXVECTOR3 pos, ModelType type);
	static void SetFloorType(D3DXVECTOR3 pos, FloorType type);
	static void SetSpawnerType(D3DXVECTOR3 pos, float width, float length, int collDown, SpawnerType type);

	static CMeshfield* GetField(void) { return m_pField[0]; }			// ���b�V���t�B�[���h�̎擾����
	static CPlayer* GetPlayer(int nCnt) { return m_pPlayer[nCnt]; }	// �v���C���[�̎擾����
	static CMessage* GetMsg(void) { return m_pMessage; }

	static CStage* Create(void);			//��������

	void GameResult();
	static bool GetResult() { return m_bResult; }

	static void ScoreComparison();

private:
	static char* m_pStagePass[STAGE_TYPE_MAX];				//�X�e�[�W�̊O���t�@�C���̑��΃p�X

	static CMeshfield* m_pField[2];
	static CPlayer* m_pPlayer[PLAYER_MAX];					//�v���C���[�̃C���X�^���X�ւ̃|�C���^
	static CHalfSphere* m_pSphere;
	static CMessage* m_pMessage;

	static bool m_bResult;
};

#endif // !_STAGE_H_

