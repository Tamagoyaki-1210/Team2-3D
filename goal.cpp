//=============================================================================
//
// goal.cpp
// Author : Kajita Hiromu
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "application.h"
#include "goal.h"
#include "rendering.h"

bool CGoal::m_bGoal = false;									//ゴールしたかどうか
int CGoal::m_nWinnerIdx = 0;

//コンストラクタ
CGoal::CGoal()
{
}

//デストラクタ
CGoal::~CGoal()
{
}

//初期化
HRESULT CGoal::Init(void)
{
	//初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}
	m_bGoal = false;

	return S_OK;
}

//終了
void CGoal::Uninit(void)
{
	//基本クラスの終了処理
	CModel::Uninit();
}

//更新
void CGoal::Update(void)
{
	//基本クラスの更新処理
	CModel::Update();
}

//描画
void CGoal::Draw(void)
{
	CModel::Draw();
}

void CGoal::SetGoal(bool bGoal,int nWinnerIdx)
{
	m_bGoal = bGoal;
	m_nWinnerIdx = nWinnerIdx;
}

//生成
CGoal * CGoal::Create(D3DXVECTOR3 pos)
{
	//インスタンスを生成する
	CGoal* pGoal = new CGoal;		

	//プレイヤーの初期化処理
	if (FAILED(pGoal->Init()))
	{
		return nullptr;
	}

	pGoal->SetModel(MODEL_GOAL);	//モデルの設定処理
	pGoal->SetPos(pos);				//位置の設定処理
	pGoal->SetShadowDraw(false);

	return pGoal;
}
