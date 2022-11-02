//=============================================================================
//
// goal.h
// Author : Kajita Hiromu
//
//=============================================================================

#ifndef _GOAL_H_
#define _GOAL_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================

class CGoal : public CObject
{
public:
	CGoal();										//コンストラクタ
	~CGoal() override;								//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;	//位置の設定処理

	const D3DXVECTOR2 GetSize(void) override;		//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;		//位置の取得処理

	static void SetGoal(bool bGoal, int nWinnerIdx);

	static CGoal* Create();	//生成処理

private:
	LPDIRECT3DTEXTURE9 m_pTexture;					//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//頂点バッファへのポインタ

	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_size;								//サイズ
	D3DXVECTOR3 m_rot;								//向き
	D3DXMATRIX  m_mtxWorld;							//ワールドマトリックス

	static int m_nWinnerIdx;
	static bool m_bGoal;									//ゴールしたかどうか
};

#endif