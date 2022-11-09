//=============================================================================
//
// title.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "title.h"
#include "Application.h"
#include "meshfield.h"
#include "camera.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CTitle::CTitle()
{

}

//=====================================
// デストラクタ
//=====================================
CTitle::~CTitle()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CTitle::Init(void)
{
	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f), Vec3Null, D3DXVECTOR2(100.0f, 100.0f), 5, 5);
	pField->SetTexture(CObject::TEXTURE_BLOCK);

	if (CApplication::GetCamera() != nullptr)
	{
		CApplication::GetCamera()->SetPos(D3DXVECTOR3(0.0f, 200.0f, -600.0f), D3DXVECTOR3(0.0f, -0.0f, 0.0f));
	}

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CTitle::Uninit(void)
{

}

//=====================================
// 更新処理
//=====================================
void CTitle::Update(void)
{

}

//=====================================
// 生成処理
//=====================================
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = new CTitle;

	if (FAILED(pTitle->Init()))
	{
		return nullptr;
	}

	return pTitle;
}