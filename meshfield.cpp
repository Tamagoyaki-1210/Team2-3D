//============================================================================
//
//メッシュポリゴンの処理[meshfield.cpp] (ファイルヘッダコメント)
//Author:谷本康輔
//============================================================================
#include <assert.h>
#include <stdio.h>
#include "application.h"
#include "texture.h"
#include "renderer.h"
#include "meshfield.h"	//作成したmeshfield.hをインクルードする
#include "input.h"		//作成したinput.hをインクルードする
#include "debugproc.h"

//****************************************************************************
//グローバル変数
//****************************************************************************
//LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//インデックスバッファへのポインタ

//=====================================
// デフォルトコンストラクタ
//=====================================
CMeshField::CMeshField(int priority) : CObject(priority), m_pVtxBuff(nullptr), m_pIdxBuff(nullptr)
{

}

//=====================================
// デストラクタ
//=====================================
CMeshField::~CMeshField()
{

}

//============================================================================
//メッシュポリゴンの初期化処理
//============================================================================
void CMeshField::Init()
{
	m_nDebug = 0;
	m_nMeshX = MAX_MESHFIELD;
	m_nMeshZ = MAX_MESHFIELD;

	//メッシュ(面)合計数計算式 = (メッシュ最大数.横 * メッシュ最大数.縦 * 2) + 縮退ポリゴン数((メッシュ最大数.縦 - 1) * 4)
	m_nMeshPlimitive = (m_nMeshX * m_nMeshZ * 2) + ((m_nMeshZ - 1) * 4);

	//頂点バッファ合計数計算式 = (メッシュ最大数.横 + 1) * (メッシュ最大数.縦 + 1)
	m_nMeshVertex = (m_nMeshX + 1) * (m_nMeshZ + 1);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldmtx = D3DXMATRIX();

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nMeshVertex,
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

	//インデックス合計数計算式 = ((メッシュ最大数.横 + 1) * (メッシュ最大数.縦 * 2)) + 縮退ポリゴン最大数((メッシュ最大数.縦 - 1) * 2)
	m_nMeshIndex = ((m_nMeshX + 1) * (m_nMeshZ * 2)) + ((m_nMeshZ - 1) * 2);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nMeshIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	m_fWidth = MESHFIELD_WIDTH;
	m_fHeight = MESHFIELD_HEIGHT;

	//オブジェクト設定処理
	SetType(CObject::TYPE_OBSTACLE);
	SetSize(m_fWidth, m_fHeight);

	SetMesh();
}

//============================================================================
//メッシュポリゴンの終了処理
//============================================================================
void CMeshField::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	//インデックスバッファの破棄
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
	//オブジェクトの破棄
	Release();
}

//============================================================================
//メッシュポリゴンの更新処理
//============================================================================
void CMeshField::Update()
{
	//キーボード取得
	CInput *pInput = CApplication::GetInput();

	//508
	if (pInput->GetKeyboardPress(DIK_B) == true)
	{
		m_nDebug++;
	}

	if (pInput->GetKeyboardTrigger(DIK_N) == true)
	{
		m_nDebug++;
	}
	else if(pInput->GetKeyboardTrigger(DIK_M) == true)
	{
		m_nDebug--;
	}
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	CDebugProc::Print("デバッグ数値 : %d\n現在の位置x : %f\n現在の位置y : %f\n現在の位置z : %f\n", m_nDebug, pVtx[m_nDebug].pos.x, pVtx[m_nDebug].pos.y, pVtx[m_nDebug].pos.z);
	
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================================================================
//メッシュポリゴンの描画処理
//============================================================================
void CMeshField::Draw()
{
	CApplication::GetTexture()->TextureType(CTexture::TYPE_MESHFIELD_01);

	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_worldmtx);

	//向きを反映(YaW : y,Pitch : x,Roll : z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxTrans);

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_worldmtx);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMeshVertex, 0, m_nMeshPlimitive);
	CApplication::GetTexture()->TextureClear();
}

//============================================================================
//メッシュポリゴンの当たり判定処理
//============================================================================
bool CMeshField::FieldCollision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld)
{
	m_fVecNor = 0.0f;
	bool bRange = false;

	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファをロック
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < m_nMeshIndex - 2; nCnt++)
	{
		//3つの頂点
		D3DXVECTOR3 pos1 = pVtx[pIdx[nCnt]].pos;
		D3DXVECTOR3 pos2 = pVtx[pIdx[nCnt + 1]].pos;
		D3DXVECTOR3 pos3 = pVtx[pIdx[nCnt + 2]].pos;

		if (pos1 == pos2 || pos2 == pos3 || pos1 == pos3)
		{
			continue;
		}

		//ポリゴンの頂点とプレイヤーの位置差分
		D3DXVECTOR3 VecB1 = pos - pos1;
		D3DXVECTOR3 VecB2 = pos - pos2;
		D3DXVECTOR3 VecB3 = pos - pos3;

		if (nCnt % 2 != 0)
		{
			//ポリゴンを形成する3辺
			D3DXVECTOR3 VecA1 = pos2 - pos1;
			D3DXVECTOR3 VecA2 = pos3 - pos2;
			D3DXVECTOR3 VecA3 = pos1 - pos3;

			//3辺とプレイヤー位置差分の外積
			float fCross1 = (VecA1.x * VecB1.z) - (VecA1.z * VecB1.x);
			float fCross2 = (VecA2.x * VecB2.z) - (VecA2.z * VecB2.x);
			float fCross3 = (VecA3.x * VecB3.z) - (VecA3.z * VecB3.x);

			//3つの外積が全て+ 又は 全て-の場合(メッシュフィールドの範囲内の場合)
			if ((fCross1 >= 0 && fCross2 >= 0 && fCross3 >= 0)
				|| (fCross1 < 0 && fCross2 < 0 && fCross3 < 0))
			{
				bRange = true;
				//1個の頂点から2個の頂点までの辺を2個作る
				D3DXVECTOR3 VecC1 = pos2 - pos1;
				D3DXVECTOR3 VecC2 = pos3 - pos1;

				//面法線ベクトル
				D3DXVECTOR3 VecNor;

				//2個の辺の外積から面法線ベクトルを作る
				D3DXVec3Cross(&VecNor, &VecC1, &VecC2);
				//正規化
				D3DXVec3Normalize(&VecNor, &VecNor);

				//面法線ベクトルとプレイヤー位置差分の内積からプレイヤーの位置.yを逆算した値
 				m_fVecNor = pos1.y - (((pos.x - pos1.x) * VecNor.x) + ((pos.z - pos1.z) * VecNor.z)) / VecNor.y;
			}
		}
		else
		{
			//ポリゴンを形成する3辺
			D3DXVECTOR3 VecA1 = pos1 - pos2;
			D3DXVECTOR3 VecA2 = pos2 - pos3;
			D3DXVECTOR3 VecA3 = pos3 - pos1;

			//3辺とプレイヤー位置差分の外積
			float fCross1 = (VecA1.x * VecB1.z) - (VecA1.z * VecB1.x);
			float fCross2 = (VecA2.x * VecB2.z) - (VecA2.z * VecB2.x);
			float fCross3 = (VecA3.x * VecB3.z) - (VecA3.z * VecB3.x);

			//3つの外積が全て+ 又は 全て-の場合(メッシュフィールドの範囲内の場合)
			if ((fCross1 >= 0 && fCross2 >= 0 && fCross3 >= 0)
				|| (fCross1 < 0 && fCross2 < 0 && fCross3 < 0))
			{
				bRange = true;

				D3DXVECTOR3 VecC1 = pos2 - pos1;
				D3DXVECTOR3 VecC2 = pos3 - pos1;

				//面法線ベクトル
				D3DXVECTOR3 VecNor;
				//外積
				D3DXVec3Cross(&VecNor, &VecC1, &VecC2);
				//正規化
				D3DXVec3Normalize(&VecNor, &VecNor);

				//面法線ベクトルとプレイヤー位置差分の内積からプレイヤーの位置.yを逆算した値
				m_fVecNor = pos1.y - (((pos.x - pos1.x) * VecNor.x) + ((pos.z - pos1.z) * VecNor.z)) / VecNor.y;
			}
		}
	}
	//インデックスのアンロック
	m_pIdxBuff->Unlock();

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//if (pos->x < posMesh.x + (m_nMeshX * (MESHFIELD_WIDTH / 2))
	//	&& pos->x > posMesh.x - (m_nMeshX * (MESHFIELD_WIDTH / 2))
	//	&& pos->z < posMesh.z + (m_nMeshZ * (MESHFIELD_HEIGHT / 2))
	//	&& pos->z > posMesh.z - (m_nMeshZ * (MESHFIELD_HEIGHT / 2)))
	//{//床に乗っている場合
	//	if (pos->y <= posMesh.y && posOld->y >= posMesh.y)
	//	{//高さがメッシュより高い場合
	//		pos->y = posMesh.y;
	//		bIsGround = true;
	//	}
	//}
	return bRange;
}

//=====================================
//メッシュ設定処理
//=====================================
void CMeshField::SetMesh()
{
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMeshZ = 0; nCntMeshZ < m_nMeshZ + 1; nCntMeshZ++)
	{
		for (int nCntMeshX = 0; nCntMeshX < m_nMeshX + 1; nCntMeshX++)
		{
			//現在の頂点 = nVtx[メッシュ数x軸 + (メッシュ数z軸 * (メッシュ最大数.横 + 1))]
			int nVtx = nCntMeshX + (nCntMeshZ * (m_nMeshX + 1));
			//選択中頂点の位置設定
			pVtx[nVtx].pos = D3DXVECTOR3(
				(float)((nCntMeshX * MESHFIELD_WIDTH) - (m_nMeshX * MESHFIELD_WIDTH / 2)),		//各頂点の横位置 = (メッシュ数.横 * 長さ) - (メッシュ最大数.横 * 長さの半分)
				(float)(rand() % 100),
				//0.0f,
				(float)((-nCntMeshZ * MESHFIELD_HEIGHT) + (m_nMeshZ * MESHFIELD_HEIGHT / 2))	//各00頂点の縦位置 = -(メッシュ数.縦 * 長さ) + (メッシュ最大数.縦 * 長さの半分)
				);

			//選択中頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
			pVtx[nVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//選択中頂点のカラーの設定
			pVtx[nVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//選択中頂点のテクスチャ座標の設定
			pVtx[nVtx].tex = D3DXVECTOR2((float)nCntMeshX, (float)nCntMeshZ);
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファをロック
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nDeg = 0;		//縮退ポリゴン

	//インデックスの設定
	for (int nCntMeshZ = 0; nCntMeshZ < m_nMeshZ; nCntMeshZ++)
	{//z軸カウント
		if(nCntMeshZ != 0)
		{//縮退ポリゴンが必要な場合
			pIdx[(((m_nMeshX + 1) * 2) * nCntMeshZ) + nDeg] = (WORD)(((m_nMeshX + 1) * nCntMeshZ) - 1);		//pIdx[現最後のインデックス] = x,z軸計算
			pIdx[(((m_nMeshX + 1) * 2) * nCntMeshZ) + nDeg + 1] = (WORD)((m_nMeshX + 1) * (nCntMeshZ + 1));	//pIdx[現最後のインデックス + 1] = x,z軸計算
			nDeg += 2;	//縮退ポリゴンを2個分作る
		}
		//x軸カウント
		for (int nCntMeshX = 0; nCntMeshX < (m_nMeshX + 1); nCntMeshX++)
		{
			//pIdx[(現カウントx軸 * 2) + ((数える分のx軸 * 2) * 現カウントz軸) + 縮退ポリゴン]
			pIdx[(nCntMeshX * 2) + (((m_nMeshX + 1) * 2) * nCntMeshZ) + nDeg]	
				// = (数える分のx軸) + 現カウントx軸 + ((数える分のx軸) * 現カウントz軸)
				= (WORD)((m_nMeshX + 1) + nCntMeshX + ((m_nMeshX + 1) * nCntMeshZ));

			//pIdx[上の+1]
			pIdx[(nCntMeshX * 2) + (((m_nMeshX + 1) * 2) * nCntMeshZ) + nDeg + 1]
				// = 現カウントx軸 + ((数える分のx軸) * 現カウントz軸)
				= (WORD)(nCntMeshX + ((m_nMeshX + 1) * nCntMeshZ));
		}
	}
	//インデックスのアンロック
	m_pIdxBuff->Unlock();
}

//=====================================
//色設定処理(頂点別)
//=====================================
void CMeshField::SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3)
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
void CMeshField::SetColor(D3DXCOLOR col)
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
void CMeshField::SetType(Object_Type type)
{
	CObject::SetType(type);
}

//=====================================
//サイズ設定処理
//=====================================
void CMeshField::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_fAngle = atan2f(fWidth, fHeight);
	m_fLength = sqrtf((fWidth * fWidth) + (fHeight * fHeight)) / 2;
}

//=====================================
//床生成処理
//=====================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos)
{
	CMeshField* pMeshField = new CMeshField;		//プレイヤーポインタ

	if (pMeshField != nullptr)
	{
		pMeshField->Init();
		pMeshField->SetPos(pos);
	}
	return pMeshField;
}