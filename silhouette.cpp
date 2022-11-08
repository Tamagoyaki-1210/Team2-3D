//=============================================================================
//
// silhouette.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "silhouette.h"
#include "application.h"
#include "rendering.h"


//コンストラクタ
CSilhouette::CSilhouette() : CObject_2D(4)
{

}

//デストラクタ
CSilhouette::~CSilhouette()
{

}

HRESULT CSilhouette::Init(void)
{
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));
	SetTexture(CObject::TEXTURE_NULL);
	SetTextureParameter(1, 1, 1, INT_MAX);
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	return S_OK;
}


void CSilhouette::Uninit(void)
{
	CObject_2D::Uninit();
}


void CSilhouette::Draw(void)
{
	//デバイスの取得処理
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//ステンシルバッファを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//ステンシルバッファと比較する参照値設定
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	//ステンシルバッファの値に対してのマスク設定
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//ステンシルテストの比較方法の設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	//ステンシルテストの結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	CObject_2D::Draw();

	//ステンシルバッファを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

CSilhouette* CSilhouette::Create(void)
{
	CSilhouette* pObj = new CSilhouette;

	if (FAILED(pObj->Init()))
	{
		return nullptr;
	}

	return pObj;
}