//=============================================================================
//
// 爆発
// Author : tanimoto kosuke
//
//=============================================================================
#include "shadow.h"
#include "application.h"
#include "texture.h"
#include "renderer.h"

//=====================================
//デフォルトコンストラクタ
//=====================================
CShadow::CShadow() : CObject3D(OBJECT_PRIORITY_CENTER)
{

}

//=====================================
//デストラクタ
//=====================================
CShadow::~CShadow()
{

}

//=====================================
//初期化処理
//=====================================
void CShadow::Init()
{
	CObject3D::Init();

	//オブジェクト設定処理
	CObject3D::SetType(TYPE_EFFECT);
	CObject3D::SetSize(m_fWidth, m_fHeight);
}

//=====================================
//終了処理
//=====================================
void CShadow::Uninit()
{
	CObject3D::Uninit();
}

//=====================================
//更新処理
//=====================================
void CShadow::Update()
{
	CObject3D::Update();
}

//=====================================
//描画処理
//=====================================
void CShadow::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//画像取得処理
	CApplication::GetTexture()->TextureType(CTexture::TYPE_SHADOW);
	CObject3D::Draw();

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//============================================================================
//影の位置更新処理
//============================================================================
void CShadow::SetShadow(D3DXVECTOR3 pos)
{
	float fSize = SHADOW_WIDTH + (pos.y / 2);
	SetPos(pos);		//引数で指定された番号のposを設定
	//SHADOW_WIDTH + (pos.y / 2), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1 - (pos.y / 100)));
	if (fSize > 0.0f)
	{
		SetSize(fSize, fSize);
	}
	else
	{
		SetSize(0.0f, 0.0f);
	}
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1 - (pos.y / 100)));
}

//=====================================
//影生成処理
//=====================================
CShadow *CShadow::Create(D3DXVECTOR3 pos)
{
	CShadow* pShadow;	//爆発ポインタ

	pShadow = new CShadow;

	if (pShadow != nullptr)
	{
		pShadow->Init();
		pShadow->SetPos(pos);
	}
	return pShadow;
}