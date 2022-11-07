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
	if (FAILED(CObject_3D::Init()))
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

	CObject_3D::Uninit();
}

//更新処理
void CLavaFloor::Update(void)
{
	CObject_3D::Update();
}






//生成処理
CLavaFloor* CLavaFloor::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size)
{
	CLavaFloor* pObj = new CLavaFloor;

	if (FAILED(pObj->Init()))
	{
		return nullptr;
	}

	pObj->SetPos(pos);
	pObj->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(size.x, 5.0f, size.y), CHitbox::TYPE_OBSTACLE, pObj, -30, CHitbox::EFFECT_LAUNCH);
	//pObj->m_pHitbox->SetLinePos(D3DXVECTOR3(0.0f, 0.0f, -size.y));
	pObj->SetStartingRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	pObj->SetPos(D3DXVECTOR3(-100.0f, -149.0f, 400.0f));
	pObj->SetSize(size);
	pObj->SetTexture(CObject::TEXTURE_LAVA);
	pObj->SetTextureParameter(1, 1, 1, INT_MAX);
	pObj->SetPriority(4);
	pObj->SetColor(ColorWhite);
	pObj->MoveTexCoordinates(D3DXVECTOR2(0.001f, -0.0005f));

	return pObj;
}