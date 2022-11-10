//=============================================================================
//
// lavaFloor.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "lavaFloor.h"
#include "BoxHitbox.h"
#include "application.h"
#include "camera.h"


//コンストラクタ
CLavaFloor::CLavaFloor()
{
	m_pHitbox = nullptr;
}

//デストラクタ
CLavaFloor::~CLavaFloor()
{

}

//初期化処理
HRESULT CLavaFloor::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return 1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CLavaFloor::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CModel::Uninit();
}

//更新処理
void CLavaFloor::Update(void)
{
	CModel::Update();

	if (GetPos().z < CApplication::GetCamera()->GetPos().z - 100.0f)
	{
		Release();
	}
}

//描画処理
void CLavaFloor::Draw(void)
{
	if (GetPos().z < CApplication::GetCamera()->GetPos().z + 650.0f)
	{
		CModel::Draw();
	}
}






//生成処理
CLavaFloor* CLavaFloor::Create(const D3DXVECTOR3 pos)
{
	CLavaFloor* pObj = new CLavaFloor;

	if (FAILED(pObj->Init()))
	{
		return nullptr;
	}

	pObj->SetPos(pos);
	pObj->SetModel(CModel::MODEL_LAVA_FLOOR);
	pObj->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(25.0f, 5.0f, 25.0f), CHitbox::TYPE_OBSTACLE, pObj, -30, CHitbox::EFFECT_LAUNCH);

	return pObj;
}