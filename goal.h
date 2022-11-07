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
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================

class CGoal : public CModel
{
public:
	CGoal();										//コンストラクタ
	~CGoal() override;								//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	static void SetGoal(bool bGoal, int nWinnerIdx);

	static CGoal* Create(D3DXVECTOR3 pos);	//生成処理

private:


	static int m_nWinnerIdx;
	static bool m_bGoal;									//ゴールしたかどうか
};

#endif