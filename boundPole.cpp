//=============================================================================
//
// boundPole.cpp
// Author : KAJITA HIROMU
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "boundPole.h"
#include "CylinderHitbox.h"

//コンストラクタ
CBoundPole::CBoundPole()
{
	m_pHitbox = nullptr;
}

//デストラクタ
CBoundPole::~CBoundPole()
{

}

//初期化処理
HRESULT CBoundPole::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CBoundPole::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CModel::Uninit();
}

//更新処理
void CBoundPole::Update(void)
{
	if (m_pHitbox != nullptr)
	{
		D3DXVECTOR3 newPos = GetPos() + m_pHitbox->GetRelativePos();
		m_pHitbox->SetPos(newPos);
	}

	CModel::Update();
}

//描画処理
void CBoundPole::Draw(void)
{
	CModel::Draw();
}






//生成処理
CBoundPole* CBoundPole::Create(const D3DXVECTOR3 pos)
{
	CBoundPole* pObs = new CBoundPole;

	if (FAILED(pObs->Init()))
	{
		return nullptr;
	}

	pObs->SetModel(CModel::MODEL_SPIKE_BALL);

	D3DXVECTOR3 rotation = D3DXVECTOR3((float)random(-100, 100), (float)random(-100, 100), (float)random(-100, 100));
	D3DXVec3Normalize(&rotation, &rotation);
	rotation.x *= 0.1f;
	rotation.y *= 0.1f;
	rotation.z *= 0.1f;
	pObs->StartRotation(rotation);
	pObs->SetPos(pos);

	pObs->m_pHitbox = CCylinderHitbox::Create(D3DXVECTOR3(pos.x, pos.y - 10.0f, pos.z), Vec3Null, D3DXVECTOR3(8.0f, 20.0f, 8.0f), CHitbox::TYPE_OBSTACLE, 0, pObs, CHitbox::EFFECT_LAUNCH);

	return pObs;
}