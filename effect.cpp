//=============================================================================
//
// effect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "effect.h"
#include "application.h"
#include "rendering.h"


//コンストラクタ
CEffect::CEffect()
{
	m_rotSpeed = Vec3Null;
	m_move = Vec3Null;
	m_deltaCol = ColorNull;
	m_fDeltaSize = 0.0f;
	m_nLife = 0;
}

//デストラクタ
CEffect::~CEffect()
{

}

//初期化処理
HRESULT CEffect::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{
		return -1;
	}

	m_rotSpeed = Vec3Null;
	m_move = Vec3Null;
	m_deltaCol = ColorNull;
	m_fDeltaSize = 0.0f;
	m_nLife = 0;

	return S_OK;
}

//終了処理
void CEffect::Uninit(void)
{
	CBillboard::Uninit();
}

//更新処理
void CEffect::Update(void)
{
	{
		m_nLife--;

		if (m_nLife <= 0)
		{
			Release();
			return;
		}

		D3DXVECTOR3 pos = GetPos();

		pos += m_move;

		SetPos(pos);

		D3DXVECTOR3 rot = GetRot();

		rot += m_rotSpeed;

		SetRot(rot);

		D3DXCOLOR col = GetColor();

		col += m_deltaCol;

		if (col.r <= 0.0f && col.g <= 0.0 && col.b <= 0.0f || col.a <= 0.0f)
		{
			Release();
			return;
		}

		SetColor(col);

		D3DXVECTOR2 Size = GetSize();
		Size.x += m_fDeltaSize;
		Size.y += m_fDeltaSize;
		
		if (Size.x <= 0.0f || Size.y <= 0.0f)
		{
			Release();
			return;
		}

		SetSize(Size);
	}

	CBillboard::Update();
}

//描画処理
void CEffect::Draw(void)
{
	//デバイスの取得処理
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->CRenderer::GetDevice();

	//加算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();

	// 設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}






CEffect* CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rotSpeed, const D3DXVECTOR3 move, const D3DXCOLOR col, const D3DXCOLOR deltaCol, const float fSize, const float fdeltaSize, const int nLife)
{
	CEffect* pEffect = new CEffect;

	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);
	pEffect->m_rotSpeed = rotSpeed;
	pEffect->m_move = move;
	pEffect->SetColor(col);
	pEffect->m_deltaCol = deltaCol;
	pEffect->SetSize(D3DXVECTOR2(fSize, fSize));
	pEffect->m_fDeltaSize = fdeltaSize;
	pEffect->m_nLife = nLife;
	pEffect->SetPriority(4);

	return pEffect;
}