//=============================================================================
//
// player.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "player.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "model.h"
#include "camera.h"
#include "application.h"
#include "debugProc.h"
#include "meshfield.h"
#include "modelPart.h"
#include "animator.h"
#include "CylinderHitbox.h"
#include "score.h"
#include "UIString.h"
#include "stage.h"
#include "rendering.h"
#include "silhouette.h"

//コンストラクタ
CPlayer::CPlayer()
{
	//メンバー変数をクリアする
	m_move = Vec3Null;					//速度の初期化処理		
	m_DestRot = Vec3Null;				//目的の角度の初期化処理
	m_pAnimator = nullptr;				//アニメーターへのポインタ
	m_pHitbox = nullptr;				//ヒットボックスへのポインタ
	m_pScore = nullptr;					//スコアへのポインタ
	m_State = (STATE)0;					//アニメーション状態
	m_pScoreUI = nullptr;				//スコアのUIへのポインタ
	m_bJump = false;					//ジャンプしているかどうか

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{//モデルの部分へのポインタ
		m_pModel[nCnt] = nullptr;
	}
}

//デストラクタ
CPlayer::~CPlayer()
{

}

//初期化処理
HRESULT CPlayer::Init(void)
{
	//メンバー変数の初期化処理
	m_move = Vec3Null;				//速度の初期化処理
	m_DestRot = Vec3Null;			//目的の角度の初期化処理
	m_pAnimator = nullptr;			//アニメーターへのポインタ
	m_pHitbox = nullptr;			//ヒットボックスへのポインタ
	m_pScore = nullptr;				//スコアへのポインタ
	m_State = STATE_NEUTRAL;		//アニメーション状態
	m_pScoreUI = nullptr;			//スコアのUIへのポインタ
	m_bJump = false;				//ジャンプしているかどうか

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{//モデルの部分へのポインタ
		m_pModel[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CPlayer::Uninit(void)
{
	//モデルパーツの終了処理
	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{
		if (m_pModel[nCnt] != nullptr)
		{
			m_pModel[nCnt]->Uninit();
			delete m_pModel[nCnt];
			m_pModel[nCnt] = nullptr;
		}
	}

	//アニメーターの破棄処理
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Uninit();
		delete m_pAnimator;
		m_pAnimator = nullptr;
	}
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
	//スコアの破棄処理
	if (m_pScore != nullptr)
	{
		m_pScore->Clear();
		m_pScore = nullptr;
	}
	//スコアのUIの破棄処理
	if (m_pScoreUI != nullptr)
	{
		m_pScoreUI->Uninit();
		m_pScoreUI = nullptr;
	}
}

//更新処理
void CPlayer::Update(void)
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();					//カメラの向きの取得処理

	//プレイヤーの目的角度の正規化処理
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));		
	float fA = acosf(cR.x);

	if (cR.z < 0.0f)
	{
		fA *= -1.0f;
	}

	PlayerController(m_nIdxPlayer);

	//m_pModel->SetPos(m_pModel->GetPos() + m_move);

	m_move.x += (0.0f - m_move.x) * 0.1f;				//移動量のXコンポネントの更新
	m_move.y += (0.0f - m_move.y) * 0.1f;				//移動量のYコンポネントの更新
	m_move.z += (0.0f - m_move.z) * 0.1f;				//移動量のZコンポネントの更新

	m_pos += m_move;									//位置の更新

	//目的の角度の正規化処理
	if (m_DestRot.y - (m_pModel[BODY]->GetRot().y) > D3DX_PI)
	{
		m_DestRot.y -= 2 * D3DX_PI;
	}
	else if (m_DestRot.y - (m_pModel[BODY]->GetRot().y) < -D3DX_PI)
	{
		m_DestRot.y += 2 * D3DX_PI;
	}

	D3DXVECTOR3 rot = m_pModel[BODY]->GetRot() + ((m_DestRot - m_pModel[BODY]->GetRot()) * 0.1f);		//回転角度の計算

	m_pModel[BODY]->SetRot(rot);		//回転角度の設定処理

	//回転角度の正規化処理
	{
		float fRot = m_pModel[BODY]->GetRot().y;

		if (fRot > D3DX_PI)
		{
			fRot = -D3DX_PI + (fRot - D3DX_PI);
		}
		else if (fRot < -D3DX_PI)
		{
			fRot = D3DX_PI - (D3DX_PI + fRot);
		}

		if (fRot < D3DX_PI * -2.0f)
		{
			fRot += D3DX_PI * 2.0f;
		}
		else if (fRot > D3DX_PI * 2.0f)
		{
			fRot += D3DX_PI * -2.0f;
		}

		//回転の設定処理
		m_pModel[BODY]->SetRot(D3DXVECTOR3(m_pModel[BODY]->GetRot().x, fRot, m_pModel[BODY]->GetRot().z));
	}

	//重量を追加する
	if (m_move.y >= -10.0f)
	{
		m_move.y -= 0.65f;
	}

	//SetPos(pos);
	
	//地面との当たり判定
	if (CMeshfield::FieldInteraction(this))
	{
		m_bJump = false;		//着地している状態にする
	}

	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Update();
	}

	CCamera* pCamera = CApplication::GetCamera();

	if (pCamera != nullptr)
	{
		D3DXVECTOR3 wallPos = pCamera->GetPos();
		wallPos.z += 150.0f;

		if (m_pos.z <= wallPos.z)
		{
			m_pos.z = wallPos.z;
		}

		if (wallPos.z >= 900.0f || CStage::GetPlayer(0)->m_pos.z >= 900.0f)
		{
			CStage::GetPlayer(0)->m_pos = D3DXVECTOR3(-147.0f,-149.0f,1009.0f);
		}

		if(wallPos.z >= 900.0f || CStage::GetPlayer(1)->m_pos.z >= 900.0f)
		{
			CStage::GetPlayer(1)->m_pos = D3DXVECTOR3(-85.0f, -149.0f, 1009.0f);
		}
	}

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(m_pos);
		m_pHitbox->Update();
	}

	if (m_pScoreUI != nullptr && m_pScore != nullptr)
	{
		int nScore = m_pScore->GetScore();
		std::string str = std::to_string(nScore);
		std::string begin = {};
		
		if (str.size() < 4)
		{
			for (int nCnt = 0; nCnt < 4 - (int)str.size(); nCnt++)
			{
				begin += '0';
			}

			begin += str;
		}
		else
		{
			begin = str;
		}

		const char* pStr = begin.c_str();
		m_pScoreUI->ChangeString(pStr);
	}

	CDebugProc::Print("\nRot: %f\nRot Dest: %f\n\nPos: %f, %f, %f", m_pModel[BODY]->GetRot().y, m_DestRot.y, m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("\nPlayer %d score: %d", m_nIdxPlayer, m_pScore->GetScore());
}

//描画処理
void CPlayer::Draw(void)
{
	//デバイスの取得処理
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//ステンシルバッファを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//ステンシルバッファと比較する参照値設定
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	//ステンシルバッファの値に対してのマスク設定
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//ステンシルテストの比較方法の設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

	//ステンシルテストの結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);


	D3DXMATRIX mtxTrans, mtxRot;												//計算用のマトリックス
	D3DXMatrixIdentity(&m_mtxWorld);											//ワールドマトリックスの初期化処理

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	m_pModel[BODY]->Draw(m_mtxWorld);											//最初のモデルの描画処理

	for (int nCnt = 1; nCnt < PARTS_MAX; nCnt++)
	{//他のモデルの描画処理
		if (m_pModel[nCnt] != nullptr)
		{
			m_pModel[nCnt]->Draw();
		}
	}

	//ステンシルバッファを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//位置の設定処理
void CPlayer::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//サイズの取得処理
const D3DXVECTOR2 CPlayer::GetSize(void)
{
	return Vec2Null;
}

//位置の取得処理
const D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}



//生成処理
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos,int nCntPlayer)
{
	CPlayer* pModel = new CPlayer;		//インスタンスを生成する
	
	//プレイヤーの初期化処理
	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_pModel[BODY] = CModelPart::Create(CModel::MODEL_BODY, D3DXVECTOR3(0.0f, 14.0f, 0.0f), Vec3Null);				//体のモデルを生成する

	pModel->m_pModel[HEAD] = CModelPart::Create(CModel::MODEL_HEAD, D3DXVECTOR3(0.0f, 13.0f, 0.0f), Vec3Null);				//頭のモデルを生成する
	pModel->m_pModel[HEAD]->SetParent(pModel->m_pModel[BODY]);																//頭の親を設定する

	pModel->m_pModel[LEFT_ARM] = CModelPart::Create(CModel::MODEL_LEFT_ARM, D3DXVECTOR3(5.0f, 12.0f, 0.0f), Vec3Null);		//左腕のモデルを生成する
	pModel->m_pModel[LEFT_ARM]->SetParent(pModel->m_pModel[BODY]);															//左腕の親を設定する

	pModel->m_pModel[LEFT_HAND] = CModelPart::Create(CModel::MODEL_LEFT_HAND, D3DXVECTOR3(9.0f, 0.0f, 0.0f), Vec3Null);		//左手のモデルを生成する
	pModel->m_pModel[LEFT_HAND]->SetParent(pModel->m_pModel[LEFT_ARM]);														//左手の親を設定する

	pModel->m_pModel[RIGHT_ARM] = CModelPart::Create(CModel::MODEL_RIGHT_ARM, D3DXVECTOR3(-5.0f, 12.0f, 0.0f), Vec3Null);	//右腕のモデルを生成する
	pModel->m_pModel[RIGHT_ARM]->SetParent(pModel->m_pModel[BODY]);															//右腕の親を設定する
	
	pModel->m_pModel[RIGHT_HAND] = CModelPart::Create(CModel::MODEL_RIGHT_HAND, D3DXVECTOR3(-9.0f, 0.0f, 0.0f), Vec3Null);	//右手のモデルを生成する
	pModel->m_pModel[RIGHT_HAND]->SetParent(pModel->m_pModel[RIGHT_ARM]);													//右手の親を設定する
	
	pModel->m_pModel[LEFT_LEG] = CModelPart::Create(CModel::MODEL_LEFT_LEG, D3DXVECTOR3(3.0f, 1.0f, 0.0f), Vec3Null);		//左太腿のモデルを生成する
	pModel->m_pModel[LEFT_LEG]->SetParent(pModel->m_pModel[BODY]);															//左太腿の親を設定する
	
	pModel->m_pModel[LEFT_FOOT] = CModelPart::Create(CModel::MODEL_LEFT_FOOT, D3DXVECTOR3(0.1f, -10.0f, 0.0f), Vec3Null);	//左足のモデルを生成する
	pModel->m_pModel[LEFT_FOOT]->SetParent(pModel->m_pModel[LEFT_LEG]);														//左足の親を設定する
	
	pModel->m_pModel[RIGHT_LEG] = CModelPart::Create(CModel::MODEL_RIGHT_LEG, D3DXVECTOR3(-3.0f, 1.0f, 0.0f), Vec3Null);	//右太腿のモデルを生成する
	pModel->m_pModel[RIGHT_LEG]->SetParent(pModel->m_pModel[BODY]);															//右太腿の親を設定する

	pModel->m_pModel[RIGHT_FOOT] = CModelPart::Create(CModel::MODEL_RIGHT_FOOT, D3DXVECTOR3(-0.1f, -10.0f, 0.0f), Vec3Null);//右足のモデルを生成する
	pModel->m_pModel[RIGHT_FOOT]->SetParent(pModel->m_pModel[RIGHT_LEG]);													//右足の親を設定する

	std::vector <CModelPart*> vParts;
	vParts.clear();
	vParts.push_back(pModel->m_pModel[BODY]);
	vParts.push_back(pModel->m_pModel[HEAD]);
	vParts.push_back(pModel->m_pModel[LEFT_ARM]);
	vParts.push_back(pModel->m_pModel[LEFT_HAND]);
	vParts.push_back(pModel->m_pModel[RIGHT_ARM]);
	vParts.push_back(pModel->m_pModel[RIGHT_HAND]);
	vParts.push_back(pModel->m_pModel[LEFT_LEG]);
	vParts.push_back(pModel->m_pModel[LEFT_FOOT]);
	vParts.push_back(pModel->m_pModel[RIGHT_LEG]);
	vParts.push_back(pModel->m_pModel[RIGHT_FOOT]);

	pModel->m_pAnimator = CAnimator::Create(&vParts, CAnimator::ANIM_TYPE_PLAYER);

	pModel->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(10.0f, 35.0f, 10.0f), CHitbox::TYPE_PLAYER, pModel, nCntPlayer);

	pModel->SetPlayerIdx(nCntPlayer);

	pModel->m_pScore = CScore::Create(nCntPlayer);

	D3DXCOLOR UIcol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	if (nCntPlayer == 1)
	{
		pModel->m_pModel[BODY]->SetModelColor(1, D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f));
		pModel->m_pModel[LEFT_ARM]->SetModelColor(1, D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f));
		pModel->m_pModel[RIGHT_ARM]->SetModelColor(1, D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f));
		UIcol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}

	pModel->m_pScoreUI = CUIString::Create(D3DXVECTOR3(50.0f + 200.0f * nCntPlayer, 50.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), UIcol, "0000", 5);

	CSilhouette::Create();

	return pModel;
}

void CPlayer::PlayerController(int nCntPlayer)
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();					//カメラの向きの取得処理
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));
	float fA = acosf(cR.x);

	//移動量と目的の角度の計算
	if (CInputKeyboard::GetKeyboardPress(DIK_W) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  < -0.3f)
	{//Wキーが押された場合
		if (CInputKeyboard::GetKeyboardPress(DIK_A) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  < -0.3f)
		{//Aキーも押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(D3DX_PI * 0.25f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(D3DX_PI * 0.25f + cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.25f + fA;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  > 0.3f)
		{//Dキーも押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(-D3DX_PI * 0.25f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(-D3DX_PI * 0.25f + cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.75f + fA;
		}
		else
		{//Wキーだけが押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.5f + fA;
		}
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_S) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  > 0.3f)
	{//Sキーが押された場合
		if (CInputKeyboard::GetKeyboardPress(DIK_A) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  < -0.3f)
		{//Aキーも押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(D3DX_PI * 0.75f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(D3DX_PI * 0.75f + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.25f + fA;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  > 0.5f)
		{//Dキーも押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(-D3DX_PI * 0.75f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(-D3DX_PI * 0.75f + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.75f + fA;
		}
		else
		{//Sキーだけが押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(D3DX_PI + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(D3DX_PI + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.5f + fA;
		}
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_D) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  > 0.3f)
	{//Dキーだけ押された場合
		if (m_move.x <= 4.0f && m_move.x >= -4.0f)
		{
			m_move.x += 0.2f * cosf(-D3DX_PI * 0.5f + cameraRot.y);
		}
		if (m_move.z <= 4.0f && m_move.z >= -4.0f)
		{
			m_move.z += 0.2f * sinf(-D3DX_PI * 0.5f + cameraRot.y);
		}

		m_DestRot.y = D3DX_PI + fA;
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_A) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  < -0.3f)
	{//Aキーだけ押された場合
		if (m_move.x <= 4.0f && m_move.x >= -4.0f)
		{
			m_move.x += 0.2f * cosf(D3DX_PI * 0.5f + cameraRot.y);
		}
		if (m_move.z <= 4.0f && m_move.z >= -4.0f)
		{
			m_move.z += 0.2f * sinf(D3DX_PI * 0.5f + cameraRot.y);
		}
		m_DestRot.y = fA;
	}
	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) && !m_bJump)
	{//ジャンプ
		m_move.y = 18.0f;
		m_bJump = true;
	}

	if (CInputKeyboard::GetKeyboardPress(DIK_W) || CInputKeyboard::GetKeyboardPress(DIK_S) || CInputKeyboard::GetKeyboardPress(DIK_A) || CInputKeyboard::GetKeyboardPress(DIK_D)
		|| CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  < -0.3f || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  > 0.3f
		|| CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  < -0.3f || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  > 0.3f)
	{
		m_State = STATE_RUNNING;
	}
	else
	{
		m_State = STATE_NEUTRAL;
	}

	switch (m_State)
	{
	case STATE_NEUTRAL:
		m_pAnimator->SetPresentAnim(0);
		break;

	case STATE_RUNNING:
		m_pAnimator->SetPresentAnim(1);
		break;
	default:
		break;
	}
}

void CPlayer::SetPlayerIdx(int nCntPlayer)
{
	m_nIdxPlayer = nCntPlayer;
}
