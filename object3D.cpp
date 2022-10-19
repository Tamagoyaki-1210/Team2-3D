//=============================================================================
//
// オブジェクト3D
// Author : tanimoto kosuke
//
//=============================================================================
#include "object3D.h"
#include "renderer.h"
#include "application.h"

//=====================================
//デフォルトコンストラクタ
//=====================================
CObject3D::CObject3D(int priority) : CObject(priority), m_pVtxBuff(nullptr)
{

}

//=====================================
//デストラクタ
//=====================================
CObject3D::~CObject3D()
{

}

//=====================================
//初期化処理
//=====================================
void CObject3D::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldmtx = D3DXMATRIX();

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=====================================
//終了処理
//=====================================
void CObject3D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	//オブジェクトの破棄
	Release();
}

//=====================================
//更新処理
//=====================================
void CObject3D::Update()
{

}

//=====================================
//描画処理
//=====================================
void CObject3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_worldmtx);

	//向きを反映(YaW : y,Pitch : x,Roll : z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_worldmtx);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	////インデックスバッファをデータストリームに設定
	//pDevice->SetIndices(g_pIdxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	////ポリゴンの描画
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMeshVertex, 0, m_nMeshPlimitive);
}

//=====================================
//UV設定処理
//=====================================
void CObject3D::SetUV()
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[0].pos.y = m_pos.y;
	pVtx[0].pos.z = m_pos.z + cosf(m_fAngle + m_rot.z) * m_fLength;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[1].pos.y = m_pos.y;
	pVtx[1].pos.z = m_pos.z + cosf(m_fAngle - m_rot.z) * m_fLength;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[2].pos.y = m_pos.y;
	pVtx[2].pos.z = m_pos.z - cosf(m_fAngle - m_rot.z) * m_fLength;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[3].pos.y = m_pos.y;
	pVtx[3].pos.z = m_pos.z - cosf(m_fAngle + m_rot.z) * m_fLength;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=====================================
//色設定処理(頂点別)
//=====================================
void CObject3D::SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3)
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col0;
	pVtx[1].col = col1;
	pVtx[2].col = col2;
	pVtx[3].col = col3;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=====================================
//色設定処理(全体)
//=====================================
void CObject3D::SetColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=====================================
//オブジェクト設定処理
//=====================================
void CObject3D::SetType(Object_Type type)
{
	CObject::SetType(type);
}

//=====================================
//サイズ設定処理
//=====================================
void CObject3D::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_fAngle = atan2f(fWidth, fHeight);
	m_fLength = sqrtf((fWidth * fWidth) + (fHeight * fHeight)) / 2;

	SetUV();
}

//=====================================
//オブジェクト2D生成処理
//=====================================
CObject3D *CObject3D::Create(D3DXVECTOR3 pos)
{
	CObject3D *pObject3D = new CObject3D;	//オブジェクト2Dポインタ

	if (pObject3D != nullptr)
	{
		pObject3D->Init();
		pObject3D->SetPos(pos);
	}
	return pObject3D;
}