//============================================================================
//
// モデルの処理
// Author:谷本康輔
//
//============================================================================
#include "model.h"		//作成したplayer.hをインクルードする
#include "input.h"		//作成したinput.hをインクルードする
#include "camera.h"		//作成したcamera.hをインクルードする
#include "application.h"
#include "renderer.h"
#include "texture.h"
#include "debugproc.h"
#include "light.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CModel::CModel()
{

}

//=====================================
// デストラクタ
//=====================================
CModel::~CModel()
{

}

//=====================================
//初期化処理
//=====================================
void CModel::Init(char *xFail)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//Xファイルの読み込み(体)
	D3DXLoadMeshFromX(
		//"Data\\Model\\00_niwamaru_body.x",
		(LPCSTR)xFail,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh
	);

	m_pParent = nullptr;
}

//=====================================
//初期化処理
//=====================================
void CModel::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldmtx = D3DXMATRIX();
}

//=====================================
//終了処理
//=====================================
void CModel::Uninit()
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=====================================
//更新処理
//=====================================
void CModel::Update()
{

}


//=====================================
//描画処理
//=====================================
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxParent;						//親用マトリクス
	D3DMATERIAL9 matDef;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_worldmtx);
	
	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	//向きを反映(YaW : y,Pitch : x,Roll : z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetWorldMtx();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//親モデルのマトリックスとの掛け算
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxParent);

	//++++++++++++++++++++++++++
	// 平面投影法
	//++++++++++++++++++++++++++
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;

	//シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	D3DLIGHT9 light = CApplication::GetLight()->GetLight();
	vecLight = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	D3DXMatrixMultiply(&mtxShadow, &m_worldmtx, &mtxShadow);

	//シャドウマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//現在のマテリアルのポインタを取得
	D3DXMATERIAL *pMatShadow = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//テクスチャの読み出し
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//影用マトリックス生成
		D3DMATERIAL9 matShadow = pMatShadow[nCntMat].MatD3D;

		//影の色を黒色にする
		matShadow.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//マテリアルの設定
		pDevice->SetMaterial(&matShadow);
		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_worldmtx);

	//現在のマテリアルのポインタを取得
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//テクスチャの読み出し
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保持してたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=====================================
//モデル生成処理
//=====================================
CModel *CModel::Create(D3DXVECTOR3 pos, char *xFail)
{
	CModel *pModel = new CModel;		//プレイヤーポインタ

	if (pModel != nullptr)
	{
		pModel->Init(xFail);
		pModel->SetPos(pos);
	}
	return pModel;
}