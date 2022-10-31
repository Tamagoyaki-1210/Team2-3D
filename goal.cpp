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
#include "message.h"
#include "gamerace.h"

bool CGoal::m_bGoal = false;									//ゴールしたかどうか

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
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bGoal = false;

	return S_OK;
}

//終了
void CGoal::Uninit(void)
{
}

//更新
void CGoal::Update(void)
{
	m_bGoal = GetGoal();

	if (m_bGoal)
	{
		CGameRace::Get()->GoalMessage();
	}
}

//描画
void CGoal::Draw(void)
{
}

//位置
void CGoal::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//サイズの情報
const D3DXVECTOR2 CGoal::GetSize(void)
{
	return (D3DXVECTOR2)m_size;
}

//位置の情報
const D3DXVECTOR3 CGoal::GetPos(void)
{
	return m_pos;
}

void CGoal::SetGoal(bool bGoal)
{
	m_bGoal = bGoal;
}

bool CGoal::GetGoal()
{
	return m_bGoal;
}

//生成
CGoal * CGoal::Create()
{
	//インスタンスを生成する
	CGoal* pGoal = new CGoal;		

	//プレイヤーの初期化処理
	if (FAILED(pGoal->Init()))
	{
		return nullptr;
	}

	return pGoal;
}
