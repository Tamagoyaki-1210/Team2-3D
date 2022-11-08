//=============================================================================
//
// icePillar.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "icePillar.h"
#include "CylinderHitbox.h"
#include "application.h"
#include "rendering.h"
#include "meshfield.h"


//コンストラクタ
CIcePillar::CIcePillar()
{
	m_pMesh = nullptr;								//メッシュ情報へのポインタ
	m_pBuffMat = nullptr;							//マテリアル情報へのポインタ
	m_nNumMat = 0;									//マテリアル情報の数
	m_pos = Vec3Null;								//現在の位置
	m_LastPos = Vec3Null;							//前回の位置
	m_move = Vec3Null;								//モデルの移動量
	m_rot = Vec3Null;								//向き
	m_shadowPosY = 0.0f;
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_nLife = 0;
	m_type = (CModel::ModelType)0;
	m_vModelTexture.clear();
	m_pHitbox = nullptr;
	m_pDamageHitbox = nullptr;
}

//デストラクタ
CIcePillar::~CIcePillar()
{

}

//初期化処理
HRESULT CIcePillar::Init(void)
{
	m_pMesh = nullptr;								//メッシュ情報へのポインタ
	m_pBuffMat = nullptr;							//マテリアル情報へのポインタ
	m_nNumMat = 0;									//マテリアル情報の数
	m_pos = Vec3Null;								//現在の位置
	m_LastPos = Vec3Null;							//前回の位置
	m_move = Vec3Null;								//モデルの移動量
	m_rot = Vec3Null;								//向き
	m_shadowPosY = 0.0f;
	m_nLife = 0;
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_type = (CModel::ModelType)0;
	m_vModelTexture.clear();
	m_pHitbox = nullptr;
	m_pDamageHitbox = nullptr;

	return S_OK;
}

//終了処理
void CIcePillar::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
	if (m_pDamageHitbox != nullptr)
	{
		m_pDamageHitbox->Release();
		m_pDamageHitbox = nullptr;
	}
}

//更新処理
void CIcePillar::Update(void)
{
	if (m_move != Vec3Null)
	{
		m_pos += m_move;
	}

	if (m_move.y >= -7.0f)
	{
		m_move.y += -0.5f;
	}

	if (CMeshfield::FieldInteraction(this))
	{
		m_nLife++;

		if (m_pDamageHitbox != nullptr)
		{
			m_pDamageHitbox->Release();
			m_pDamageHitbox = nullptr;
		}

		if (m_nLife >= 300)
		{
			Release();
		}
	}

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(m_pos);
	}
	if (m_pDamageHitbox != nullptr)
	{
		m_pDamageHitbox->SetPos(m_pos);
	}
}

//描画処理
void CIcePillar::Draw(void)
{
	if (m_nLife < 100 || m_nLife % 30 < 15)
	{
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//デバイスの取得
		D3DXMATRIX mtxRot, mtxTrans, mtxShadow;							//計算用マトリックス
		D3DMATERIAL9 matDef;									//現在のマテリアル保存用
		D3DXMATERIAL *pMat;										//マテリアルデータへのポインタ
		D3DXVECTOR4 vecLight;
		D3DXVECTOR3 pos, Normal;
		D3DXPLANE planeField;


		D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		D3DXVec3Normalize(&dir, &dir);

		vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);

		pos = D3DXVECTOR3(0.0f, m_shadowPosY, 0.0f);

		Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);
		D3DXMatrixIdentity(&mtxShadow);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		D3DXPlaneFromPointNormal(&planeField, &pos, &Normal);
		D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

		D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

		//現在のマテリアルを保持
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタの取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			D3DXCOLOR col = pMat[nCntMat].MatD3D.Diffuse;

			pMat[nCntMat].MatD3D.Diffuse.r = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.g = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.b = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.a = 0.5f;

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

			//モデルパーツの描画
			m_pMesh->DrawSubset(nCntMat);

			pMat[nCntMat].MatD3D.Diffuse.r = col.r;
			pMat[nCntMat].MatD3D.Diffuse.g = col.g;
			pMat[nCntMat].MatD3D.Diffuse.b = col.b;
			pMat[nCntMat].MatD3D.Diffuse.a = col.a;
		}


		//ステンシルバッファを有効にする
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		//ステンシルバッファと比較する参照値設定
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

		//ステンシルバッファの値に対してのマスク設定
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		//ステンシルテストの比較方法の設定
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

		//ステンシルテストの結果に対しての反映設定
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

		pMat = nullptr;

		//保持しいたマテリアルを戻す
		pDevice->SetMaterial(&matDef);


		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//現在のマテリアルを保持
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタの取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

			//モデルパーツの描画
			m_pMesh->DrawSubset(nCntMat);
		}

		//保持しいたマテリアルを戻す
		pDevice->SetMaterial(&matDef);

		//ステンシルバッファを無効にする
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

		pMat = nullptr;

		//保持しいたマテリアルを戻す
		pDevice->SetMaterial(&matDef);


		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//現在のマテリアルを保持
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタの取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

			//モデルパーツの描画
			m_pMesh->DrawSubset(nCntMat);
		}

		//保持しいたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//位置の設定処理
void CIcePillar::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//位置の取得処理
const D3DXVECTOR3 CIcePillar::GetPos(void)
{
	return m_pos;
}

//サイズの取得処理
const D3DXVECTOR2 CIcePillar::GetSize(void)
{
	return Vec2Null;
}







//生成処理
CIcePillar* CIcePillar::Create(CModel::ModelType type, D3DXVECTOR3 pos, const float ShadowHeight)
{
	CIcePillar* pPillar = new CIcePillar;

	if (FAILED(pPillar->Init()))
	{
		return nullptr;
	}

	pPillar->m_pos = pos;
	pPillar->m_rot = Vec3Null;
	pPillar->m_LastPos = pos;
	pPillar->m_type = type;
	pPillar->m_shadowPosY = ShadowHeight;

	CModel::GetModel(type, &pPillar->m_pMesh, &pPillar->m_pBuffMat, &pPillar->m_nNumMat);
	CModel::GetTextures(pPillar->m_vModelTexture, type);

	pPillar->m_pHitbox = CCylinderHitbox::Create(pos, (D3DXVECTOR3(0.0f, -47.5f, 0.0f)), D3DXVECTOR3(25.0f, 80.0f, 25.0f), CHitbox::TYPE_NEUTRAL, pPillar);
	pPillar->m_pDamageHitbox = CCylinderHitbox::Create(pos, (D3DXVECTOR3(0.0f, -67.5f, 0.0f)), D3DXVECTOR3(25.0f, 20.0f, 25.0f), CHitbox::TYPE_OBSTACLE, -30, pPillar, CHitbox::EFFECT_LAUNCH);

	return pPillar;
}