//============================================================================
//
//
//ビルボードの処理[billboard.cpp] (ファイルヘッダコメント)
//Author:谷本康輔
//
//============================================================================
#include "billboard.h"	//作成したbillboard.hをインクルードする
#include "renderer.h"
#include "application.h"
#include "texture.h"
//#include "shadow.h"		//作成したshadow.hをインクルードする

//デフォルトコンストラクタ
//=====================================
CBillBoard::CBillBoard(int list) : CObject(list), m_pVtxBuff(nullptr)
{

}

//=====================================
//デストラクタ
//=====================================
CBillBoard::~CBillBoard()
{

}

//****************************************************************************
//グローバル変数
//****************************************************************************
//bool g_ZBillBoardDebug = false;						//Zバッファのデバッグ

//============================================================================
//ビルボードの初期化処理
//============================================================================
void CBillBoard::Init()
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

	SetUV();

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

	m_bUse = true;
}

//============================================================================
//ビルボードの終了処理
//============================================================================
void CBillBoard::Uninit()
{
	if (m_bUse == true)
	{
		m_bUse = false;
		//頂点バッファの破棄
		if (m_pVtxBuff != nullptr)
		{
			m_pVtxBuff->Release();
			m_pVtxBuff = nullptr;
		}
		//オブジェクトの破棄
		Release();
	}
}

//============================================================================
//ビルボードの更新処理
//============================================================================
void CBillBoard::Update()
{
	//for (int nCntBillBoard = 0; nCntBillBoard < MAX_BILLBOARD; nCntBillBoard++)
	//{
	//	if (g_aBillBoard[nCntBillBoard].bUse == true)
	//	{
	//		SetpositionShadow(g_aBillBoard[nCntBillBoard].IndxShadow, D3DXVECTOR3(g_aBillBoard[nCntBillBoard].pos.x, 0.0f, g_aBillBoard[nCntBillBoard].pos.z),
	//			SHADOW_WIDTH + (g_aBillBoard[nCntBillBoard].pos.y / 2), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1 - (g_aBillBoard[nCntBillBoard].pos.y / 100)));
	//	}
	//}

	//if (GetKeyboardTrigger(DIK_F7) == true)
	//{//Zバッファテスト
	//	g_ZBillBoardDebug = !g_ZBillBoardDebug;
	//}
	SetUV();
	//m_rot.x++;
	//m_rot.z++;
}

//============================================================================
//ビルボードの描画処理
//============================================================================
void CBillBoard::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス

		//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_worldmtx);

	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	D3DXMatrixInverse(&m_worldmtx, NULL, &mtxView);
	m_worldmtx._41 = 0.0f;
	m_worldmtx._42 = 0.0f;
	m_worldmtx._43 = 0.0f;

	////カメラの逆行列を設定
	//m_worldmtx._11 = mtxView._11;
	//m_worldmtx._12 = mtxView._21;
	//m_worldmtx._13 = mtxView._31;

	////弾
	//m_worldmtx._21 = mtxView._12;
	//m_worldmtx._22 = mtxView._22;
	//m_worldmtx._23 = mtxView._32;

	//m_worldmtx._31 = mtxView._13;
	//m_worldmtx._32 = mtxView._23;
	//m_worldmtx._33 = mtxView._33;

	////向きを反映(YaW : y,Pitch : x,Roll : z)
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBillBoard[nCntBillBoard].rot.y, g_aBillBoard[nCntBillBoard].rot.x, g_aBillBoard[nCntBillBoard].rot.z);
	//D3DXMatrixMultiply(&g_aBillBoard[nCntBillBoard].Worldmtx, &g_aBillBoard[nCntBillBoard].Worldmtx, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxTrans);

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	////Zバッファの値が手前のZバッファの値より小さい場合
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//if (g_ZBillBoardDebug == false)
	//{
	//	//Zバッファを描画する
	//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//}
	//else
	//{
	//	//Zバッファを描画する
	//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//}

	////アルファテストを有効
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_worldmtx);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	CApplication::GetTexture()->TextureType(CTexture::TYPE_PLAYER);

	//ビルボードの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	////Zバッファを描画する
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	////Zバッファの値が手前のZバッファの値より小さい場合
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	////アルファテストを無効に戻す
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//テクスチャの解除
	CApplication::GetTexture()->TextureClear();

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//=====================================
//UV設定処理
//=====================================
void CBillBoard::SetUV()
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[0].pos.z = m_pos.z;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[1].pos.z = m_pos.z;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[2].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[2].pos.z = m_pos.z;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[3].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[3].pos.z = m_pos.z;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=====================================
//色設定処理(頂点別)
//=====================================
void CBillBoard::SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3)
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
void CBillBoard::SetColor(D3DXCOLOR col)
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
//種別設定処理
//=====================================
void CBillBoard::SetType(Object_Type type)
{
	CObject::SetType(type);
}

//=====================================
//サイズ設定処理
//=====================================
void CBillBoard::SetSize(float fWidth, float fHeight)
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
CBillBoard *CBillBoard::Create(D3DXVECTOR3 pos)
{
	CBillBoard *pBillBoard = new CBillBoard;	//オブジェクト2Dポインタ

	if (pBillBoard != nullptr)
	{
		pBillBoard->Init();
		pBillBoard->SetPos(pos);
	}
	return pBillBoard;
}