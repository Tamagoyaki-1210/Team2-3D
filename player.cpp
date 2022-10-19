//============================================================================
//
// モデルの処理
// Author:谷本康輔
//
//============================================================================
#include "player.h"		//作成したplayer.hをインクルードする
#include "input.h"		//作成したinput.hをインクルードする
#include "camera.h"		//作成したcamera.hをインクルードする
//#include "shadow.h"		//作成したshadow.hをインクルードする
#include "model.h"		//作成したmodel.hをインクルードする
#include "meshfield.h"	//作成したmeshfield.hをインクルードする
//#include "fade.h"		//作成したfade.hをインクルードする
#include "game.h"		//作成したgame.hをインクルードする
#include "application.h"
#include "texture.h"
#include "debugproc.h"

//****************************************************************************
//グローバル変数
//****************************************************************************
int g_nIndxShadowPlayer;				//影のインデックス
D3DXVECTOR3 g_rotDestPlayer;

//=====================================
// デフォルトコンストラクタ
//=====================================
CPlayer::CPlayer() : CObjectX(OBJECT_PRIORITY_CENTER)
{

}

//=====================================
// デストラクタ
//=====================================
CPlayer::~CPlayer()
{

}

//============================================================================
//プレイヤーの初期化処理
//============================================================================
void CPlayer::Init()
{
	CObjectX::Init("Data\\Model\\00_niwamaru_body.x");

	m_pModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 4.0f, -6.0f), "Data\\Model\\01_niwamaru_head.x");
	m_pModel[1] = CModel::Create(D3DXVECTOR3(2.0f, -2.0f, 0.0f), "Data\\Model\\02_niwamaru_legL.x");
	m_pModel[2] = CModel::Create(D3DXVECTOR3(-2.0f, -2.0f, 0.0f), "Data\\Model\\03_niwamaru_legR.x");

	m_nLife = PLAYER_LIFE;
	m_nPower = 0;
	m_fFlame = 0;
	m_fAttack = 0;
	m_bDamege = false;
	m_bLoop = false;
	m_bGround = false;
	m_motion = MOTION_NUTRAL;

	//m_pShadow = CShadow::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//for (int nCntPlayerParts = 0; nCntPlayerParts < MAX_PLAYER_PARTS; nCntPlayerParts++)
	//{
	//	g_aPlayer.aParts[nCntPlayerParts].Worldmtx = D3DXMATRIX();	//ワールドマトリックス
	//}

	////体(親)のパーツ
	//g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_aPlayer.aParts[0].nIdxModelParent = -1;

	////頭(子)のパーツ
	//g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_aPlayer.aParts[1].nIdxModelParent = 0;

	////左足(子)のパーツ
	//g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_aPlayer.aParts[2].nIdxModelParent = 0;

	////右足(子)のパーツ
	//g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_aPlayer.aParts[3].nIdxModelParent = 0;

	//g_nIndxShadowPlayer = SetShadow(g_aPlayer.pos, g_aPlayer.rot);
}

//============================================================================
//プレイヤーの初期化処理
//============================================================================
void CPlayer::Uninit()
{
	for (int nInd = 0; nInd < MAX_PLAYER_PARTS; nInd++)
	{
		m_pModel[nInd]->Uninit();
	}
	CObjectX::Uninit();
}

//============================================================================
//プレイヤーの更新処理
//============================================================================
void CPlayer::Update()
{
	for (int nInd = 0; nInd < MAX_PLAYER_PARTS; nInd++)
	{
		m_pModel[nInd]->Update();
	}
	CObjectX::Update();


	D3DXVECTOR3 pos = CObjectX::GetPos();
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//落ちたら復帰する処理
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (pos.y <= -100)
	{
		m_nLife--;
		//pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
		pos.y = 20.0f;
	}
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//その他の処理
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	D3DXVECTOR3 rot = CObjectX::GetRot();

	//プレイヤーの前回位置を反映
	m_posOld = pos;

	//重力を更新(増幅させる)
	m_move.y -= 4.0f;

	Input();

	//移動量を更新(減衰させる)
	m_move -= m_move * 0.1f;

	pos = CObjectX::GetPos();

	Motion();
	Collision();

	pos = CObjectX::GetPos();

	//プレイヤーの位置更新
	pos += m_move * 0.1f;

	SetPos(pos);
	//m_pModel->SetPos(pos);
	//m_pModel->SetRot(rot);

	//m_pShadow->SetShadow(D3DXVECTOR3(pos.x, 2.0f, pos.z));

}
//============================================================================
//プレイヤーの描画処理
//============================================================================
void CPlayer::Draw()
{
	CApplication::GetTexture()->TextureType(CTexture::TYPE_PLAYER);
	CObjectX::Draw();
	for (int nInd = 0; nInd < MAX_PLAYER_PARTS; nInd++)
	{
		m_pModel[nInd]->Draw(GetWorldMtx());
	}
	CApplication::GetTexture()->TextureClear();

	//CDebugProc::Print("現在の角度y : %f\n目的の角度y : %f\n", CObjectX::GetRot().y, m_rotDest.y);

	////パーツの処理
	//for (int nCntPlayerParts = 0; nCntPlayerParts < MAX_PLAYER_PARTS; nCntPlayerParts++)
	//{
	//	//ワールドマトリックスの初期化
	//	D3DXMatrixIdentity(&g_aPlayer.aParts[nCntPlayerParts].Worldmtx);

	//	//向きを反映(YaW : y,Pitch : x,Roll : z)
	//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer.aParts[nCntPlayerParts].rot.y, g_aPlayer.aParts[nCntPlayerParts].rot.x, g_aPlayer.aParts[nCntPlayerParts].rot.z);
	//	D3DXMatrixMultiply(&g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &mtxRot);

	//	//位置を反映
	//	D3DXMatrixTranslation(&mtxTrans, g_aPlayer.aParts[nCntPlayerParts].pos.x, g_aPlayer.aParts[nCntPlayerParts].pos.y, g_aPlayer.aParts[nCntPlayerParts].pos.z);
	//	D3DXMatrixMultiply(&g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &mtxTrans);

	//	if (g_aPlayer.aParts[nCntPlayerParts].nIdxModelParent == -1)
	//	{//親モデルのインデックスが-1の場合
	//		mtxParent = g_aPlayer.Worldmtx;				//プレイヤーマトリクスを登録
	//	}
	//	else
	//	{
	//		mtxParent = g_aPlayer.aParts[g_aPlayer.aParts[nCntPlayerParts].nIdxModelParent].Worldmtx;		//親のマトリクスを登録
	//	}
	//	//親モデルのマトリックスとの掛け算
	//	D3DXMatrixMultiply(&g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &mtxParent);

	//	//ワールドマトリックスの設定
	//	pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer.aParts[nCntPlayerParts].Worldmtx);

	//	//現在のマテリアルのポインタを取得
	//	pMat = (D3DXMATERIAL*)g_aPlayer.aParts[nCntPlayerParts].pBuffMat->GetBufferPointer();

	//	//テクスチャの読み出し
	//	for (int nCntMat = 0; nCntMat < (int)g_aPlayer.aParts[nCntPlayerParts].nNumMat; nCntMat++)
	//	{
	//		//テクスチャの設定
	//		pDevice->SetTexture(0, g_aPlayer.aParts[nCntPlayerParts].g_pTexture[g_aPlayer.tex]);

	//		//マテリアルの設定
	//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	//		//モデルパーツの描画
	//		g_aPlayer.aParts[nCntPlayerParts].pMesh->DrawSubset(nCntMat);
	//	}
	//}
}

//=====================================
//入力処理
//=====================================
void CPlayer::Input()
{
	//キーボード取得
	CInput *pInput = CApplication::GetInput();

	//カメラ取得処理
	CCamera *pCamera = CApplication::GetCamera();

	D3DXVECTOR3 rotPlayer = GetRot();
	D3DXVECTOR3 rotCamera = pCamera->GetRot();

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//プレイヤー移動処理
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (pInput->GetKeyboardPress(DIK_W) == true)
	{//手前移動
		rotPlayer.y += (m_rotDest.y - rotPlayer.y) / 10;
		if (m_bLoop == false && m_bGround == true)
		{
			m_fFlame = 0;
			m_motion = MOTION_WARK;
			m_bLoop = true;
		}
		if (pInput->GetKeyboardPress(DIK_A) == true)
		{
			m_move.x += sinf(rotCamera.y - D3DX_PI / 4) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y - D3DX_PI / 4) * PLAYER_SPEAD;
			m_rotDest.y = rotCamera.y + D3DX_PI * 3 / 4;
		}
		else if (pInput->GetKeyboardPress(DIK_D) == true)
		{
			m_move.x += sinf(rotCamera.y + D3DX_PI / 4) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y + D3DX_PI / 4) * PLAYER_SPEAD;
			m_rotDest.y = rotCamera.y - D3DX_PI * 3 / 4;
		}
		else
		{
			m_move.x += sinf(rotCamera.y) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y) * PLAYER_SPEAD;

			if (rotPlayer.y >= rotCamera.y)
			{
				m_rotDest.y = rotCamera.y + D3DX_PI;
			}
			else if (rotPlayer.y < rotCamera.y)
			{
				m_rotDest.y = rotCamera.y - D3DX_PI;
			}
		}
	}
	else if (pInput->GetKeyboardPress(DIK_S) == true)
	{//奥移動
		rotPlayer.y += (m_rotDest.y - rotPlayer.y) / 10;
		if (m_bLoop == false && m_bGround == true)
		{
			m_fFlame = 0;
			m_motion = MOTION_WARK;
			m_bLoop = true;
		}

		if (pInput->GetKeyboardPress(DIK_A) == true)
		{
			m_move.x += sinf(rotCamera.y - D3DX_PI * 3 / 4) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y - D3DX_PI * 3 / 4) * PLAYER_SPEAD;
			m_rotDest.y = rotCamera.y + D3DX_PI / 4;
		}
		else if (pInput->GetKeyboardPress(DIK_D) == true)
		{
			m_move.x += sinf(rotCamera.y + D3DX_PI * 3 / 4) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y + D3DX_PI * 3 / 4) * PLAYER_SPEAD;
			m_rotDest.y = rotCamera.y - D3DX_PI / 4;
		}
		else
		{
			m_move.x += sinf(rotCamera.y - D3DX_PI) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y - D3DX_PI) * PLAYER_SPEAD;
			m_rotDest.y = rotCamera.y;
		}
	}
	else if (pInput->GetKeyboardPress(DIK_A) == true)
	{//左移動
		rotPlayer.y += (m_rotDest.y - rotPlayer.y) / 10;
		if (m_bLoop == false && m_bGround == true)
		{
			m_fFlame = 0;
			m_motion = MOTION_WARK;
			m_bLoop = true;
		}

		m_move.x += sinf(rotCamera.y - D3DX_PI / 2.0f) * PLAYER_SPEAD;
		m_move.z += cosf(rotCamera.y - D3DX_PI / 2.0f) * PLAYER_SPEAD;
		m_rotDest.y = rotCamera.y + D3DX_PI / 2;
	}
	else if (pInput->GetKeyboardPress(DIK_D) == true)
	{//右移動
		rotPlayer.y += (m_rotDest.y - rotPlayer.y) / 10;
		if (m_bLoop == false && m_bGround == true)
		{
			m_fFlame = 0;
			m_motion = MOTION_WARK;
			m_bLoop = true;
		}

		m_move.x += sinf(rotCamera.y + D3DX_PI / 2.0f) * PLAYER_SPEAD;
		m_move.z += cosf(rotCamera.y + D3DX_PI / 2.0f) * PLAYER_SPEAD;
		m_rotDest.y = rotCamera.y - D3DX_PI / 2;
	}

	if (m_bGround == true)
	{//接地時の処理
		if (pInput->GetKeyboardTrigger(DIK_SPACE) == true)
		{//ジャンプ
			m_motion = MOTION_JUMP;
			m_bLoop = true;
			m_fFlame = 0;
			m_move.y += 100.0f;
			m_bGround = false;		//着地判定を偽にする
		}
	}

	//if (m_nPower < 3)
	//{
	//	if (pInput->GetKeyboardTrigger(DIK_RETURN) == true)
	//	{//攻撃モーション
	//		m_motion = MOTION_ATTACK;
	//		m_bLoop = true;
	//		m_fFlame = 0;
	//	}
	//}
	//else if (m_fFlame >= 6.0f)
	//{
	//	if (pInput->GetKeyboardPress(DIK_RETURN) == true)
	//	{//攻撃モーション
	//		m_motion = MOTION_ATTACK;
	//		m_bLoop = true;
	//		m_fFlame = 0;
	//	}
	//}
	//else
	//{
	//	m_fFlame++;
	//}
	SetRot(rotPlayer);
	RotNormalize();
}

//=====================================
//モーション処理
//=====================================
void CPlayer::Motion()
{
	////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	////プレイヤーモーション処理
	////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	////通常状態
	//if (m_motion == MOTION_NUTRAL)
	//{
	//	m_fFlame++;

	//	if (m_fFlame <= 40)
	//	{
	//		//体(親)のパーツ
	//		g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.002f, 0.0f, 0.0f);
	//		//頭(子)のパーツ
	//		g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.002f, 0.0f, 0.0f);
	//		//左足(子)のパーツ
	//		g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.003f, 0.0f, 0.0f);
	//		//右足(子)のパーツ
	//		g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.003f, 0.0f, 0.0f);
	//	}
	//	else if (g_aPlayer.fFlame <= 80)
	//	{
	//		//体(親)のパーツ
	//		g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.002f, 0.0f, 0.0f);
	//		//頭(子)のパーツ
	//		g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.002f, 0.0f, 0.0f);
	//		//左足(子)のパーツ
	//		g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.003f, 0.0f, 0.0f);
	//		//右足(子)のパーツ
	//		g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.003f, 0.0f, 0.0f);
	//	}
	//	else
	//	{//モーションリセット
	//		g_aPlayer.fFlame = 0;
	//		//体(親)のパーツ
	//		g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//		g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//		//頭(子)のパーツ
	//		g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//		g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//		//左足(子)のパーツ
	//		g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//		g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//		//右足(子)のパーツ
	//		g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//		g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	}
	//}
	////通常状態以外の処理
	//else if (g_aPlayer.bLoop == true)
	//{
	//	//歩行状態
	//	if (g_aPlayer.motion == MOTION_WARK)
	//	{
	//		g_aPlayer.fFlame++;

	//		if (g_aPlayer.fFlame <= 5)
	//		{
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.01f, 0.0f, 0.0f);
	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.01f, 0.0f, 0.0f);
	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 10)
	//		{
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.01f, 0.0f, 0.0f);
	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.01f, 0.0f, 0.0f);
	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 15)
	//		{
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.01f, 0.0f, 0.0f);
	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.01f, 0.0f, 0.0f);
	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 20)
	//		{
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.01f, 0.0f, 0.0f);
	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.01f, 0.0f, 0.0f);
	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//		}
	//		else
	//		{//モーションリセット
	//			g_aPlayer.fFlame = 0;
	//			g_aPlayer.bLoop = false;
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		}
	//	}
	//	//ジャンプ状態
	//	if (g_aPlayer.motion == MOTION_JUMP)
	//	{
	//		if (g_aPlayer.fFlame == 0)
	//		{
	//			g_aPlayer.fFlame++;
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 2)
	//		{
	//			g_aPlayer.fFlame++;
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 4)
	//		{
	//			g_aPlayer.fFlame++;
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 6)
	//		{
	//			g_aPlayer.fFlame++;
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(-0.1f, 0.0f, 0.0f);
	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].pos += D3DXVECTOR3(0.0f, -0.6f, 0.0f);
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(-0.6f, 0.0f, 0.0f);
	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].pos += D3DXVECTOR3(0.0f, -0.6f, 0.0f);
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(-0.6f, 0.0f, 0.0f);
	//		}
	//	}
	//	//着地状態
	//	if (g_aPlayer.motion == MOTION_LANDING)
	//	{
	//		g_aPlayer.fFlame++;

	//		if (g_aPlayer.move.x >= 1.0f || g_aPlayer.move.z >= 1.0f)
	//		{
	//			//モーションリセット
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			g_aPlayer.fFlame = 0;
	//			g_aPlayer.bLoop = false;
	//			g_aPlayer.motion = MOTION_WARK;
	//		}
	//		else if (g_aPlayer.fFlame == 1)
	//		{//モーションリセット
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 5)
	//		{
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].pos += D3DXVECTOR3(0.0f, -0.4f, 0.0f);
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.08f, 0.0f, 0.0f);
	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].pos += D3DXVECTOR3(0.0f, 0.4f, 0.0f);
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.10f, 0.0f, 0.0f);
	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].pos += D3DXVECTOR3(0.0f, 0.4f, 0.0f);
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.10f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 15)
	//		{
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].pos -= D3DXVECTOR3(0.0f, -0.2f, 0.0f);
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.04f, 0.0f, 0.0f);
	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].pos -= D3DXVECTOR3(0.0f, 0.2f, 0.0f);
	//			g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.05f, 0.0f, 0.0f);
	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].pos -= D3DXVECTOR3(0.0f, 0.2f, 0.0f);
	//			g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.05f, 0.0f, 0.0f);
	//		}
	//		else
	//		{
	//			g_aPlayer.fFlame = 0;
	//			g_aPlayer.bLoop = false;
	//		}
	//	}
	//	//攻撃状態
	//	if (g_aPlayer.motion == MOTION_ATTACK)
	//	{
	//		if (g_aPlayer.fFlame == 0)
	//		{//攻撃判定作成(位置, 移動量, 持続時間, 種類)
	//			//SetAttack
	//			//(
	//			//	D3DXVECTOR3(g_aPlayer.pos.x - sinf(g_aPlayer.rot.y) * 12.0f, (g_aPlayer.pos.y + 10.0f), g_aPlayer.pos.z - cosf(g_aPlayer.rot.y) * 12.0f),
	//			//	D3DXVECTOR3(0.0f, -10.0f, 0.0f),
	//			//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//			//	PLAYER_ATTACK,
	//			//	ATTACK_TYPE_PLAYER
	//			//);
	//		}
	//		g_aPlayer.fFlame++;
	//		if (g_aPlayer.fFlame <= 4)
	//		{
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.4f, 0.0f, 0.0f);
	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 8)
	//		{
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.4f, 0.0f, 0.0f);
	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//		}
	//		else
	//		{//モーションリセット
	//			g_aPlayer.fFlame = 0;
	//			g_aPlayer.bLoop = false;
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//弾を終了させる
	//			pAttack->bUse = false;
	//		}
	//	}
	//	//被弾状態
	//	if (g_aPlayer.motion == MOTION_DAMEGE)
	//	{
	//		if (g_aPlayer.fFlame <= 0)
	//		{//モーションリセット
	//			g_aPlayer.fFlame = 0;
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		}
	//		g_aPlayer.fFlame++;

	//		if (g_aPlayer.fFlame <= 5)
	//		{
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.08f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 10)
	//		{
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.28f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 20)
	//		{
	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.14f, 0.0f, 0.0f);
	//		}
	//		else
	//		{//モーションリセット
	//			g_aPlayer.bLoop = false;
	//			g_aPlayer.fFlame = 0;

	//			//体(親)のパーツ
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//頭(子)のパーツ
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//左足(子)のパーツ
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//右足(子)のパーツ
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		}
	//	}
	//}
	//else
	//{//通常状態以外のモーションが終了した場合
	//	g_aPlayer.fFlame = 0;
	//	//体(親)のパーツ
	//	g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//	g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	//頭(子)のパーツ
	//	g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//	g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	//左足(子)のパーツ
	//	g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//	g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	//右足(子)のパーツ
	//	g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//	g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aPlayer.motion = MOTION_NUTRAL;		//通常状態に戻す
	//}
//CObjectX::SetPos(pos);
//CObjectX::SetRot(rot);
}

//=====================================
//プレイヤー当たり判定処理
//=====================================
void CPlayer::Collision()
{
	//フィールドポインタ生成
	CMeshField *pField = CGame::GetField();

	//プレイヤーのサイズを求める処理
	D3DXVECTOR3 size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	//プレイヤーのサイズの半径を求める処理
	D3DXVECTOR3 r_size = size / 2;

	D3DXVECTOR3 pos = CObjectX::GetPos();
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//床の判定処理
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//メッシュフィールド当たり判定の処理
	//bool bIsGroundField = pField->FieldCollision(pos, m_posOld);

	////敵キャラ当たり判定の処理
	//bool bIsGroundEnemy = EnemyCollision(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &r_size);

	////モデル当たり判定の処理
	//bool bIsGroundModel = ModelCollision(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &r_size);

	//床接地時
	if (pField->FieldCollision(pos, m_posOld) == true)
	{

		//接地しているなら
		//if (pField->GetVecNor() == pos.y)
		//{
		float f = pField->GetVecNor();
			//プレイヤーの位置.yを押し上げる処理
			SetPos(D3DXVECTOR3(pos.x, f, pos.z));
				//m_move.y = 0.0f;

				if (m_bGround == false)
				{
					m_bGround = true;	//着地判定を真にする
					m_bLoop = true;
					m_fFlame = 0;
					m_motion = MOTION_LANDING;
				}
			
		//}
	}
	////影の大きさを高さで設定
	//SetpositionShadow(g_nIndxShadowPlayer, D3DXVECTOR3(g_aPlayer.pos.x, -2.0f, g_aPlayer.pos.z),
	//	SHADOW_WIDTH + (g_aPlayer.pos.y / 2), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1 - (g_aPlayer.pos.y / 100)));
}

//=====================================
//入力処理
//=====================================
void CPlayer::RotNormalize()
{
	D3DXVECTOR3 rotPlayer = GetRot();
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//角度の正規化処理
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (rotPlayer.y > D3DX_PI)
	{//現在の角度が(PI)より大きい場合
		rotPlayer.y -= D3DX_PI * 2;
	}
	else if (rotPlayer.y < -D3DX_PI)
	{//現在の角度が(-PI)より小さい場合
		rotPlayer.y += D3DX_PI * 2;
	}

	if (m_rotDest.y - rotPlayer.y > D3DX_PI)
	{//現在の目的値が(PI)より大きい場合
		m_rotDest.y -= 2 * D3DX_PI;
	}
	else if (m_rotDest.y - rotPlayer.y < -D3DX_PI)
	{//現在の目的地が(-PI)より小さい場合
		m_rotDest.y += 2 * D3DX_PI;
	}
	SetRot(rotPlayer);
}

//=====================================
//プレイヤー生成処理
//=====================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, float ParentY)
{
	CPlayer *pPlayer = new CPlayer;		//プレイヤーポインタ

	if (pPlayer != nullptr)
	{
		pPlayer->Init();
		pPlayer->SetPos(pos);
		pPlayer->SetType(TYPE_PLAYER);
		pPlayer->SetPalentY(ParentY);
	}
	return pPlayer;
}