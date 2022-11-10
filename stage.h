//=============================================================================
//
// stage.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//---------------------------
//前方宣言
//---------------------------
class CMeshfield;
class CPlayer;
class CHalfSphere;
class CMessage;

//---------------------------
//クラス宣言
//---------------------------
class CStage
{
public:
	//ステージの種類
	enum StageType
	{
		STAGE_TYPE_1 = 0,
		STAGE_TYPE_2,
		STAGE_TYPE_3,
		STAGE_TYPE_MAX
	};

	//メッシュフィールドの種類
	enum FieldType
	{
		FIELD_NORMAL = 0,
		FIELD_SRIP,
		FIELD_TYPE_MAX
	};

	//障害物の種類
	enum ModelType
	{
		MODEL_SPIKEBALL = 0,
		MODEL_BOUNCEPOLE,
		MODEL_TRAMPOLINE,
		MODEL_TYPE_MAX
	};

	//床の種類
	enum FloorType
	{
		FLOOR_LAVA = 0,
		FLOOR_SLIP,
		FLOOR_TYPE_MAX
	};

	//生成オブジェクトの種類
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

	static CMeshfield* GetField(void) { return m_pField[0]; }			// メッシュフィールドの取得処理
	static CPlayer* GetPlayer(int nCnt) { return m_pPlayer[nCnt]; }	// プレイヤーの取得処理
	static CMessage* GetMsg(void) { return m_pMessage; }

	static CStage* Create(void);			//生成処理

	void GameResult();
	static bool GetResult() { return m_bResult; }

	static void ScoreComparison();

private:
	static char* m_pStagePass[STAGE_TYPE_MAX];				//ステージの外部ファイルの相対パス

	static CMeshfield* m_pField[2];
	static CPlayer* m_pPlayer[PLAYER_MAX];					//プレイヤーのインスタンスへのポインタ
	static CHalfSphere* m_pSphere;
	static CMessage* m_pMessage;

	static bool m_bResult;
};

#endif // !_STAGE_H_

