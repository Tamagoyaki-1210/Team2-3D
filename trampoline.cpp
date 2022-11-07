//=============================================================================
//
// trampoline.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "trampoline.h"
#include "CylinderHitbox.h"

//コンストラクタ
CTrampoline::CTrampoline()
{
	m_pHitbox = nullptr;
}

//デストラクタ
CTrampoline::~CTrampoline()
{

}

//初期化処理
HRESULT CTrampoline::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CTrampoline::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CModel::Uninit();
}

//更新処理
void CTrampoline::Update(void)
{
	CModel::Update();
}




//生成処理
CTrampoline* CTrampoline::Create(const D3DXVECTOR3 pos)
{
	CTrampoline* pModel = new CTrampoline;

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->SetModel(CModel::MODEL_HEAD);
	pModel->SetPos(pos);
	pModel->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(20.0f, 2.0f, 20.0f), CHitbox::TYPE_OBSTACLE, 0, nullptr, CHitbox::EFFECT_JUMP);

	return pModel;
}