//=============================================================================
//
// modelPart.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "modelPart.h"
#include "application.h"
#include "rendering.h"
#include "directionalLight.h"

//コンストラクタ
CModelPart::CModelPart()
{
	m_pMesh = nullptr;								//メッシュ情報へのポインタ
	m_pBuffMat = nullptr;							//マテリアル情報へのポインタ
	m_nNumMat = 0;									//マテリアル情報の数
	m_pos = Vec3Null;								//現在の位置
	m_LastPos = Vec3Null;							//前回の位置
	m_move = Vec3Null;								//モデルの移動量
	m_rot = Vec3Null;								//向き
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;							//モデルの頂点座標の最小値と最大値
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_type = CModel::MODEL_BODY;
	m_pParent = nullptr;
	m_vModelTexture.clear();
	m_vCol.clear();
}

//デストラクタ
CModelPart::~CModelPart()
{

}

//初期化処理
HRESULT CModelPart::Init(void)
{
	m_pMesh = nullptr;								//メッシュ情報へのポインタ
	m_pBuffMat = nullptr;							//マテリアル情報へのポインタ
	m_nNumMat = 0;									//マテリアル情報の数
	m_pos = Vec3Null;								//現在の位置
	m_LastPos = Vec3Null;							//前回の位置
	m_move = Vec3Null;								//モデルの移動量
	m_rot = Vec3Null;								//向き
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;							//モデルの頂点座標の最小値と最大値
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_type = CModel::MODEL_BODY;
	m_pParent = nullptr;
	m_vModelTexture.clear();
	m_vCol.clear();

	return S_OK;
}

//終了処理
void CModelPart::Uninit(void)
{
	m_vCol.clear();
}

//更新処理
void CModelPart::Update(void)
{

}

//描画処理
void CModelPart::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxShadow, mtxParent;		//計算用マトリックス
	D3DMATERIAL9 matDef;									//現在のマテリアル保存用
	D3DXMATERIAL *pMat;										//マテリアルデータへのポインタ
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, Normal;
	D3DXPLANE planeField;

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMatrix();
	}

	D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
	D3DXVec3Normalize(&dir, &dir);

	vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);
	pos = D3DXVECTOR3(0.0f, -149.0f, 0.0f);
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

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;

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

		D3DXCOLOR c = {};
		bool bCol = false;

		for (int i = 0; i < (int)m_vCol.size(); i++)
		{
			if (m_vCol.data()[i].nMatNumber == nCntMat)
			{
				bCol = true;
				c = pMat[nCntMat].MatD3D.Diffuse;
				pMat[nCntMat].MatD3D.Diffuse = m_vCol.data()[i].col;
				break;
			}
		}

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);

		if (bCol)
		{
			pMat[nCntMat].MatD3D.Diffuse = c;
		}
	}

	//保持しいたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//描画処理
void CModelPart::Draw(D3DXMATRIX mtxParent)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxShadow;		//計算用マトリックス
	D3DMATERIAL9 matDef;									//現在のマテリアル保存用
	D3DXMATERIAL *pMat;										//マテリアルデータへのポインタ
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, Normal;
	D3DXPLANE planeField;

	D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
	D3DXVec3Normalize(&dir, &dir);

	vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);
	pos = D3DXVECTOR3(0.0f, -149.0f, 0.0f);
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

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;

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

		D3DXCOLOR c = {};
		bool bCol = false;

		for (int i = 0; i < (int)m_vCol.size(); i++)
		{
			if (m_vCol.data()[i].nMatNumber == nCntMat)
			{
				bCol = true;
				c = pMat[nCntMat].MatD3D.Diffuse;
				pMat[nCntMat].MatD3D.Diffuse = m_vCol.data()[i].col;
				break;
			}
		}

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);

		if (bCol)
		{
			pMat[nCntMat].MatD3D.Diffuse = c;
		}
	}

	//保持しいたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	pDevice->SetTexture(0, nullptr);
}

//親の設定処理
void CModelPart::SetParent(CModelPart* pParent)
{
	m_pParent = pParent;
}

//親の取得処理
CModelPart* CModelPart::GetParent(void)
{
	return m_pParent;
}

//位置の設定処理
void CModelPart::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//位置の取得処理
const D3DXVECTOR3 CModelPart::GetPos(void)
{
	return m_pos;
}

//向きの設定処理
void CModelPart::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//向きの取得処理
const D3DXVECTOR3 CModelPart::GetRot(void)
{
	return m_rot;
}

//サイズの取得処理
const D3DXVECTOR3 CModelPart::GetSize(void)
{
	return Vec3Null;
}

D3DXMATRIX CModelPart::GetMatrix(void)
{
	return m_mtxWorld;
}

//カーラーの設定処理
void CModelPart::SetModelColor(const int nNumMat, const D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < (int)m_vCol.size(); nCnt++)
	{
		if (m_vCol.data()[nCnt].nMatNumber == nNumMat)
		{
			CModel::ModelColor mCol = {};
			mCol.nMatNumber = nNumMat;
			mCol.col = col;
			m_vCol.data()[nCnt] = mCol;
			return;
		}
	}

	CModel::ModelColor mCol = {};
	mCol.nMatNumber = nNumMat;
	mCol.col = col;

	m_vCol.push_back(mCol);
}







//生成処理
CModelPart* CModelPart::Create(CModel::ModelType type, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CModelPart* pModel = new CModelPart;

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_rot = rot;
	pModel->m_LastPos = pos;
	pModel->m_type = type;

	CModel::GetModel(type, &pModel->m_pMesh, &pModel->m_pBuffMat, &pModel->m_nNumMat);
	CModel::GetTextures(pModel->m_vModelTexture, type);

	return pModel;
}