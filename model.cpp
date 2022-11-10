//=============================================================================
//
// model.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"
#include "application.h"
#include "rendering.h"
#include "directionalLight.h"

LPD3DXMESH		CModel::m_pMeshAll[MODEL_MAX] = {};					//メッシュ情報へのポインタ
LPD3DXBUFFER	CModel::m_pBuffMatAll[MODEL_MAX] = {};				//マテリアル情報へのポインタ
DWORD			CModel::m_nNumMatAll[MODEL_MAX] = {};				//マテリアル情報の数
std::vector <LPDIRECT3DTEXTURE9>     CModel::m_vModelTexture[CModel::MODEL_MAX];		//モデルのテクスチャへのポインタのベクトル

char*			CModel::m_pModelPass[MODEL_MAX] =
{
	{ "data\\MODELS\\Player02\\Player02_Body.x" },
	{ "data\\MODELS\\Player02\\Player02_Head.x"},
	{ "data\\MODELS\\Player02\\Player02_Arm_Left.x" },
	{ "data\\MODELS\\Player02\\Player02_Hand_Left.x" },
	{ "data\\MODELS\\Player02\\Player02_Arm_Right.x" },
	{ "data\\MODELS\\Player02\\Player02_Hand_Right.x" },
	{ "data\\MODELS\\Player02\\Player02_Leg_Left.x" },
	{ "data\\MODELS\\Player02\\Player02_Foot_Left.x" },
	{ "data\\MODELS\\Player02\\Player02_Leg_Right.x" },
	{ "data\\MODELS\\Player02\\Player02_Foot_Right.x" },

	{ "data\\MODELS\\Player02\\PlayerParts\\SantaHead.x" },
	{ "data\\MODELS\\Player02\\PlayerParts\\PumpHead.x" },
	{ "data\\MODELS\\Player02\\PlayerParts\\TopHatHead.x" },
	{ "data\\MODELS\\Player02\\PlayerParts\\KatanaHead.x" },
	{ "data\\MODELS\\Player02\\PlayerParts\\DragonHead.x" },
	{ "data\\MODELS\\Player02\\PlayerParts\\oqtoHead.x" },
	{ "data\\MODELS\\Player02\\PlayerParts\\snowman.x" },
	{ "data\\MODELS\\Player02\\PlayerParts\\ToyBoxHead.x" },
	{ "data\\MODELS\\Player02\\PlayerParts\\SummerTimeHead.x" },

	{ "data\\MODELS\\Coin\\Coin00.x" },
	{ "data\\MODELS\\Coin\\Coin01.x" },
	{ "data\\MODELS\\Coin\\Coin02.x" },
	{ "data\\MODELS\\Coin\\Coin03.x" },

	{ "data\\MODELS\\Environment\\Mountains\\Fuji.x" },
	{ "data\\MODELS\\Environment\\Mountains\\FujiYuki.x" },
	{ "data\\MODELS\\Environment\\Balloon\\Balloon.x" },
	{ "data\\MODELS\\Environment\\tree\\tree1.x" },
	{ "data\\MODELS\\Environment\\tree\\tree2.x" },
	{ "data\\MODELS\\Environment\\windmill\\windmill.x" },
	{ "data\\MODELS\\Environment\\airship\\airship.x" },
	{ "data\\MODELS\\Environment\\stone\\stone.x" },

	{ "data\\MODELS\\Stage_Debug\\Stage_Debug_Obstade.x" },
	{ "data\\MODELS\\Stage_Debug\\Stage_Debug_Obstade_Ball.x" },
	{ "data\\MODELS\\Stage_Debug\\Stage_Debug_Obstade_Cylinder.x" },
	{ "data\\MODELS\\Stage_Debug\\Stage_Debug_Obstade_Needle.x" },

	{ "data\\MODELS\\Stage_gimmick\\NeedleBall\\NeedleBall.x" },
	{ "data\\MODELS\\Stage_gimmick\\LavaFloor\\Lava.x" },
	{ "data\\MODELS\\Stage_gimmick\\BoundPole\\BoundPole.x" },

	{ "data\\MODELS\\traps\\jump\\jump.x" },
	{ "data\\MODELS\\traps\\fallstone\\fallstone.x" },
	{ "data\\MODELS\\traps\\IcePillar\\IcePillar_TrapType.x" },

	{ "data\\MODELS\\sign\\fallstonesign.x" },
	{ "data\\MODELS\\Stage_gimmick\\GrassTable\\GrassTable.x" },

	{ "data\\MODELS\\Goal\\Goal01.x" },
};

//コンストラクタ
CModel::CModel()
{
	m_pMesh = nullptr;								//メッシュ情報へのポインタ
	m_pBuffMat = nullptr;							//マテリアル情報へのポインタ
	m_nNumMat = 0;									//マテリアル情報の数
	m_pos = Vec3Null;								//現在の位置
	m_LastPos = Vec3Null;							//前回の位置
	m_move = Vec3Null;								//モデルの移動量
	m_rot = Vec3Null;								//向き
	m_frameRot = Vec3Null;							//1フレームの回転角度
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;							//モデルの頂点座標の最小値と最大値
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_type = CModel::MODEL_BODY;
	m_vCol.clear();
	m_bShadow = true;
	m_fShadowHeight = 0.0f;
}

CModel::CModel(const int nPriority) : CObject::CObject(nPriority)
{
	m_pMesh = nullptr;								//メッシュ情報へのポインタ
	m_pBuffMat = nullptr;							//マテリアル情報へのポインタ
	m_nNumMat = 0;									//マテリアル情報の数
	m_pos = Vec3Null;								//現在の位置
	m_LastPos = Vec3Null;							//前回の位置
	m_move = Vec3Null;								//モデルの移動量
	m_rot = Vec3Null;								//向き
	m_frameRot = Vec3Null;							//1フレームの回転角度
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;								//モデルの頂点座標の最小値と最大値
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_type = CModel::MODEL_BODY;
	m_vCol.clear();
	m_bShadow = true;
	m_fShadowHeight = 0.0f;
}

//デストラクタ
CModel::~CModel()
{

}

//初期化処理
HRESULT CModel::Init(void)
{
	m_pMesh = nullptr;								//メッシュ情報へのポインタ
	m_pBuffMat = nullptr;							//マテリアル情報へのポインタ
	m_nNumMat = 0;									//マテリアル情報の数
	m_pos = Vec3Null;								//現在の位置
	m_LastPos = Vec3Null;							//前回の位置
	m_move = Vec3Null;								//モデルの移動量
	m_rot = Vec3Null;								//向き
	m_frameRot = Vec3Null;							//1フレームの回転角度
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;							//モデルの頂点座標の最小値と最大値
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_vCol.clear();
	m_bShadow = true;
	m_fShadowHeight = -149.9f;

	/*std::vector <LPDIRECT3DTEXTURE9> v;

	v.clear();

	LPDIRECT3DTEXTURE9 pText = CObject_2D::GetTexturePointer(CObject::TextureNumbers);
	
	v.push_back(nullptr);
	v.push_back(pText);

	LPDIRECT3DTEXTURE9 a = v.data()[0];
	LPDIRECT3DTEXTURE9 b = v.data()[1];*/

	return S_OK;
}

//終了処理
void CModel::Uninit(void)
{
	m_vCol.clear();
}

//更新処理
void CModel::Update(void)
{
	m_LastPos = m_pos;

	if (m_frameRot != nullptr)
	{
		m_rot += m_frameRot;
	}
}

//描画処理
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxShadow;							//計算用マトリックス
	D3DMATERIAL9 matDef;									//現在のマテリアル保存用
	D3DXMATERIAL *pMat;										//マテリアルデータへのポインタ
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, Normal;
	D3DXPLANE planeField;

	
		D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
		D3DXVec3Normalize(&dir, &dir);

		vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);
		pos = D3DXVECTOR3(0.0f, m_fShadowHeight, 0.0f);
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

		if (m_bShadow)
		{

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
			pDevice->SetTexture(0, m_vModelTexture[m_type].data()[nCntMat]);

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
	}


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
		pDevice->SetTexture(0, m_vModelTexture[m_type].data()[nCntMat]);

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
		pDevice->SetTexture(0, m_vModelTexture[m_type].data()[nCntMat]);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);

		if (bCol)
		{
			pMat[nCntMat].MatD3D.Diffuse = c;
		}
	}

	//保持しいたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//位置の設定処理
void CModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//位置の取得処理
const D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

void CModel::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

const D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//ポリゴンのサイズの取得処理
const D3DXVECTOR2 CModel::GetSize(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}

//モデルの設定処理
void CModel::SetModel(const ModelType type)
{
	m_pMesh = m_pMeshAll[type];
	m_pBuffMat = m_pBuffMatAll[type];
	m_nNumMat = m_nNumMatAll[type];
	m_type = type;
}

//回転速度の設定処理
void CModel::StartRotation(const D3DXVECTOR3 frameRot)
{
	m_frameRot = frameRot;
}

//回転を止まる処理
void CModel::StopRotating(void)
{
	m_frameRot = Vec3Null;
}

//カーラーの設定処理
void CModel::SetModelColor(const int nNumMat, const D3DXCOLOR col)
{
	ModelColor mCol = {};
	mCol.nMatNumber = nNumMat;
	mCol.col = col;

	m_vCol.push_back(mCol);
}

//影が描画されているかどうかの設定処理
void CModel::SetShadowDraw(const bool bDraw)
{
	m_bShadow = bDraw;
}

void CModel::SetShadowHeight(const float fHeight)
{
	m_fShadowHeight = fHeight;
}






//モデル情報の取得処理
void CModel::GetModel(ModelType type, LPD3DXMESH* pMesh, LPD3DXBUFFER* pBuffMat, DWORD* numMat)
{
	*pMesh = m_pMeshAll[type];
	*pBuffMat = m_pBuffMatAll[type];
	*numMat = m_nNumMatAll[type];
}

//モデル全部の読み込み処理
void CModel::LoadAllModels(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < CModel::MODEL_MAX; nCnt++)
	{
		m_vModelTexture[nCnt].clear();

		//Xファイルの読み込み
		D3DXLoadMeshFromX(m_pModelPass[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMatAll[nCnt],
			NULL,
			&m_nNumMatAll[nCnt],
			&m_pMeshAll[nCnt]);

		D3DXMATERIAL *pMat = nullptr;

		//マテリアルデータへのポインタの取得
		pMat = (D3DXMATERIAL*)m_pBuffMatAll[nCnt]->GetBufferPointer();

		for (int a = 0; a < (int)m_nNumMatAll[nCnt]; a++)
		{
			LPDIRECT3DTEXTURE9 pTex = nullptr;

			D3DXCreateTextureFromFile(pDevice, pMat->pTextureFilename, &pTex);
			pMat++;
			m_vModelTexture[nCnt].push_back(pTex);
		}
	}	
}

//モデル全部の破棄処理
void CModel::DestroyAllModels(void)
{
	for (int nCnt = 0; nCnt < CModel::MODEL_MAX; nCnt++)
	{
		if (m_pMeshAll[nCnt] != nullptr)
		{
			m_pMeshAll[nCnt]->Release();
			m_pMeshAll[nCnt] = nullptr;
		}

		if (m_pBuffMatAll[nCnt] != nullptr)
		{
			m_pBuffMatAll[nCnt]->Release();
			m_pBuffMatAll[nCnt] = nullptr;
		}
	}
}

void CModel::GetTextures(std::vector <LPDIRECT3DTEXTURE9>& vTex, CModel::ModelType type)
{
	vTex.clear();

	for (int nCnt = 0; nCnt < (int)m_nNumMatAll[type]; nCnt++)
	{
		vTex.push_back(m_vModelTexture[type].data()[nCnt]);
	}
}

//生成処理
CModel* CModel::Create(ModelType type, D3DXVECTOR3 pos)
{
	CModel* pModel = new CModel(3);

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_LastPos = pos;
	pModel->m_move = Vec3Null;
	pModel->m_rot = Vec3Null;
	pModel->m_pMesh = m_pMeshAll[type];
	pModel->m_pBuffMat = m_pBuffMatAll[type];
	pModel->m_nNumMat = m_nNumMatAll[type];
	pModel->m_type = type;

	return pModel;
}

CModel* CModel::Create(ModelType type, D3DXVECTOR3 pos, const int nPriority)
{
	CModel* pModel = new CModel(nPriority);

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_LastPos = pos;
	pModel->m_move = Vec3Null;
	pModel->m_rot = Vec3Null;
	pModel->m_pMesh = m_pMeshAll[type];
	pModel->m_pBuffMat = m_pBuffMatAll[type];
	pModel->m_nNumMat = m_nNumMatAll[type];
	pModel->m_type = type;

	return pModel;
}