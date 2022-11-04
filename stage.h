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
		STAGE_TYPE_MAX
	};

	//障害物の種類
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

	static CMeshfield* GetField(void) { return m_pField; }			// メッシュフィールドの取得処理
	static CPlayer* GetPlayer(int nCnt) { return m_pPlayer[nCnt]; }	// プレイヤーの取得処理

	static CStage* Create(void);			//生成処理
private:
	//int m_nSelectStage;										// 現在選択されているステージ
	static char* m_pStagePass[STAGE_TYPE_MAX];				//ステージの外部ファイルの相対パス
	static ModelType m_ModelType;

	static CMeshfield* m_pField;
	static CPlayer* m_pPlayer[PLAYER_MAX];					//プレイヤーのインスタンスへのポインタ
	static CHalfSphere* m_pSphere[PLAYER_MAX];
};

#endif // !_STAGE_H_

