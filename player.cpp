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
#include "model.h"
#include "camera.h"
#include "application.h"
#include "debugProc.h"
#include "meshfield.h"
#include "modelPart.h"
#include "animator.h"

//コンストラクタ
CPlayer::CPlayer()
{
	//メンバー変数をクリアする
	m_move = Vec3Null;
	m_DestRot = Vec3Null;
	m_pAnimator = nullptr;

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{
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
	m_pAnimator = nullptr;

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{
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

	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Uninit();
		delete m_pAnimator;
		m_pAnimator = nullptr;
	}
}

//更新処理
void CPlayer::Update(void)
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();					//カメラの向きの取得処理
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));		
	float fA = acosf(cR.x);

	if (cR.z < 0.0f)
	{
		fA *= -1.0f;
	}

	//移動量と目的の角度の計算
	if (CInputKeyboard::GetKeyboardPress(DIK_W))
	{//Wキーが押された場合
		if (CInputKeyboard::GetKeyboardPress(DIK_A))
		{//Aキーも押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(D3DX_PI * 0.25f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(D3DX_PI * 0.25f + cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.25f + fA;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D))
		{//Dキーも押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(-D3DX_PI * 0.25f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(-D3DX_PI * 0.25f + cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.75f + fA;
		}
		else
		{//Wキーだけが押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.5f + fA;
		}
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_S))
	{//Sキーが押された場合
		if (CInputKeyboard::GetKeyboardPress(DIK_A))
		{//Aキーも押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(D3DX_PI * 0.75f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(D3DX_PI * 0.75f + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.25f + fA;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D))
		{//Dキーも押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(-D3DX_PI * 0.75f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(-D3DX_PI * 0.75f + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.75f + fA;
		}
		else
		{//Sキーだけが押された場合
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(D3DX_PI + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(D3DX_PI + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.5f + fA;
		}
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_D))
	{//Dキーだけ押された場合
		if (m_move.x <= 4.0f && m_move.x >= -4.0f)
		{
			m_move.x += 0.5f * cosf(-D3DX_PI * 0.5f + cameraRot.y);
		}
		if (m_move.z <= 4.0f && m_move.z >= -4.0f)
		{
			m_move.z += 0.5f * sinf(-D3DX_PI * 0.5f + cameraRot.y);
		}

		m_DestRot.y = D3DX_PI + fA;
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_A))
	{//Aキーだけ押された場合
		if (m_move.x <= 4.0f && m_move.x >= -4.0f)
		{
			m_move.x += 0.5f * cosf(D3DX_PI * 0.5f + cameraRot.y);
		}
		if (m_move.z <= 4.0f && m_move.z >= -4.0f)
		{
			m_move.z += 0.5f * sinf(D3DX_PI * 0.5f + cameraRot.y);
		}

		m_DestRot.y = fA;
	}

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
		m_move.y -= 0.5f;
	}

	//SetPos(pos);

	CMeshfield::FieldInteraction(this);				//地面との当たり判定

	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Update();
	}

	CDebugProc::Print("\nRot: %f\nRot Dest: %f\n\nPos: %f, %f, %f", m_pModel[BODY]->GetRot().y, m_DestRot.y, m_pos.x, m_pos.y, m_pos.z);
}

//描画処理
void CPlayer::Draw(void)
{
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
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos)
{
	CPlayer* pModel = new CPlayer;			//インスタンスを生成する
	
	//プレイヤーの初期化処理
	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_pModel[BODY] = CModelPart::Create(CModel::MODEL_CROBAT_BODY, D3DXVECTOR3(0.0f, 50.0f, 0.0f), Vec3Null);						//体のモデルを生成する
	pModel->m_pModel[LEFT_WING] = CModelPart::Create(CModel::MODEL_CROBAT_LEFT_WING, D3DXVECTOR3(7.0f, 10.0f, -2.0f), Vec3Null);			//左翼のモデルを生成する
	pModel->m_pModel[LEFT_WING]->SetParent(pModel->m_pModel[BODY]);																			//左翼の親を設定する
	pModel->m_pModel[RIGHT_WING] = CModelPart::Create(CModel::MODEL_CROBAT_RIGHT_WING, D3DXVECTOR3(-7.0f, 10.0f, -2.0f), Vec3Null);			//右翼のモデルを生成する
	pModel->m_pModel[RIGHT_WING]->SetParent(pModel->m_pModel[BODY]);																		//右翼の親を設定する
	pModel->m_pModel[LEFT_WING_SMALL] = CModelPart::Create(CModel::MODEL_CROBAT_LEFT_WING_SMALL, D3DXVECTOR3(6.0f, 6.0f, 0.0f), Vec3Null);			//左翼(小さい)のモデルを生成する
	pModel->m_pModel[LEFT_WING_SMALL]->SetParent(pModel->m_pModel[BODY]);																			//左翼(小さい)の親を設定する
	pModel->m_pModel[RIGHT_WING_SMALL] = CModelPart::Create(CModel::MODEL_CROBAT_RIGHT_WING_SMALL, D3DXVECTOR3(-6.0f, 6.0f, 0.0f), Vec3Null);			//右翼(小さい)のモデルを生成する
	pModel->m_pModel[RIGHT_WING_SMALL]->SetParent(pModel->m_pModel[BODY]);																		//右翼(小さい)の親を設定する

	std::vector <CModelPart*> vParts;
	vParts.clear();
	vParts.push_back(pModel->m_pModel[BODY]);
	vParts.push_back(pModel->m_pModel[LEFT_WING]);
	vParts.push_back(pModel->m_pModel[RIGHT_WING]);
	vParts.push_back(pModel->m_pModel[LEFT_WING_SMALL]);
	vParts.push_back(pModel->m_pModel[RIGHT_WING_SMALL]);
	pModel->m_pAnimator = CAnimator::Create(&vParts, CAnimator::ANIM_TYPE_CROBAT);

	return pModel;
}