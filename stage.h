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
	CStage();
	~CStage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CMeshfield* GetField(void) { return m_pField; }		// メッシュフィールドの取得処理
	static CPlayer* GetPlayer(int nCnt) { return m_pPlayer[nCnt]; }	// プレイヤーの取得処理

	static CStage* Create(void);			//生成処理

	void GameResult();
	static bool GetResult() { return m_bResult; }

	static int ScoreComparison();

private:
	static CMeshfield* m_pField;
	static CPlayer* m_pPlayer[PLAYER_MAX];							//プレイヤーのインスタンスへのポインタ
	static CHalfSphere* m_pSphere[PLAYER_MAX];

	static bool m_bResult;
};

#endif // !_STAGE_H_

