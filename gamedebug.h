//=============================================================================
//
// gamedebug.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _GAMEDEBUG_H_
#define _GAMEDEBUG_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "game.h"

//---------------------------
//前方宣言
//---------------------------
class CMeshfield;
class CPlayer;
class CHalfSphere;

//---------------------------
//クラス宣言
//---------------------------
class CGameDebug : public CGame
{
public:
	CGameDebug();
	~CGameDebug();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static CMeshfield* GetField(void) { return m_pField; }		// メッシュフィールドの取得処理
	static CPlayer* GetPlayer(void) { return m_pPlayer[0]; }	// プレイヤーの取得処理

	static CGameDebug* Create(void);			//生成処理
private:
	static CMeshfield* m_pField;
	static CPlayer* m_pPlayer[PLAYER_MAX];							//プレイヤーのインスタンスへのポインタ
	static CHalfSphere* m_pSphere[PLAYER_MAX];
};

#endif // !_GAMEDEBUG_H_
