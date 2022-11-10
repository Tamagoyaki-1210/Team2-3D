//=============================================================================
//
// model.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "playerModel.h"
#include "animator.h"
#include "modelPart.h"
#include "application.h"
#include "rendering.h"
#include "inputKeyboard.h"
#include "UIString.h"
#include "inputPad.h"
#include "playerSelect.h"
#include "AnimateUI.h"
#include "fade.h"

CModel::ModelType CPlayerModel::m_HeadTypeAll[HEAD_MAX]
{
	CModel::MODEL_HEAD,
	CModel::MODEL_HEAD_SANTA,
	CModel::MODEL_HEAD_PUMPKIN,
	CModel::MODEL_HEAD_TOPHAT,
	CModel::MODEL_HEAD_KATANA,
	CModel::MODEL_HEAD_DRAGON,
	CModel::MODEL_HEAD_OCTOPUS,
	CModel::MODEL_HEAD_SNOWMAN,
	CModel::MODEL_HEAD_TOYBOX,
	CModel::MODEL_HEAD_SUMMER
	
};

CModel::ModelType CPlayerModel::m_HeadType[PLAYER_MAX] =
{
	CModel::MODEL_HEAD,
	CModel::MODEL_HEAD,
	CModel::MODEL_HEAD,
	CModel::MODEL_HEAD
};

D3DXCOLOR CPlayerModel::m_playersCol[PLAYER_MAX] =
{
	ColorWhite,
	ColorWhite,
	ColorWhite,
	ColorWhite
};

//コンストラクタ
CPlayerModel::CPlayerModel()
{
	//メンバー変数をクリアする
	m_pAnimator = nullptr;					//アニメーターへのポインタ
	m_pos = Vec3Null;						//位置
	m_rot = Vec3Null;						//向き
	m_nPresentColor = ColorNull;			//現在のカーラーインデックス
	m_nIdx = 0;
	m_nPresentHead = 0;

	m_pIcon = nullptr;
	m_pUiString = nullptr;
	m_pOK = nullptr;
	m_pParent = nullptr;

	for (int nCnt = 0; nCnt < CPlayer::PARTS_MAX; nCnt++)
	{//モデルの部分へのポインタ
		m_pModel[nCnt] = nullptr;
	}
}

//デストラクタ
CPlayerModel::~CPlayerModel()
{

}

//初期化処理
HRESULT CPlayerModel::Init(void)
{
	m_pAnimator = nullptr;					//アニメーターへのポインタ
	m_pos = Vec3Null;						//位置
	m_rot = Vec3Null;						//向き
	m_nPresentColor = ColorWhite;			//現在のカーラーインデックス
	m_nIdx = 0;
	m_nPresentHead = 0;
	m_bDecision = false;

	m_pIcon = nullptr;
	m_pUiString = nullptr;
	m_pOK = nullptr;
	m_pParent = nullptr;

	for (int nCnt = 0; nCnt < CPlayer::PARTS_MAX; nCnt++)
	{//モデルの部分へのポインタ
		m_pModel[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CPlayerModel::Uninit(void)
{
	m_playersCol[m_nIdx] = m_presentColor;

	//モデルパーツの終了処理
	for (int nCnt = 0; nCnt < CPlayer::PARTS_MAX; nCnt++)
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
	if (m_pIcon != nullptr)
	{
		m_pIcon->Release();
		m_pIcon = nullptr;
	}
	if (m_pUiString != nullptr)
	{
		m_pUiString->Release();
		m_pUiString = nullptr;
	}
	if (m_pOK != nullptr)
	{
		m_pOK->Release();
		m_pOK = nullptr;
	}
	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}
}

//更新処理
void CPlayerModel::Update(void)
{
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Update();
	}

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		if (m_bSelect)
		{
			if (!m_bDecision)
			{
				if (CInputKeyboard::GetKeyboardTrigger(DIK_D) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_RIGHT, m_nIdx))
				{
					m_nPresentColor++;

					if (m_nPresentColor >= CPlayer::PLAYER_COLOR_MAX)
					{
						m_nPresentColor = 0;
					}

					m_presentColor = CPlayer::GetPlayerColors()[m_nPresentColor];

					if (m_pModel[CPlayer::BODY] != nullptr)
					{
						m_pModel[CPlayer::BODY]->SetModelColor(2, m_presentColor);
					}
					if (m_pIcon != nullptr)
					{
						m_pIcon->SetColor(m_presentColor);
					}
					if (m_pUiString != nullptr)
					{
						m_pUiString->ChangeColor(m_presentColor);
					}
				}
				else if (CInputKeyboard::GetKeyboardTrigger(DIK_A) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_LEFT, m_nIdx))
				{
					m_nPresentColor--;

					if (m_nPresentColor < 0)
					{
						m_nPresentColor = CPlayer::PLAYER_COLOR_MAX - 1;
					}

					m_presentColor = CPlayer::GetPlayerColors()[m_nPresentColor];

					if (m_pModel[CPlayer::BODY] != nullptr)
					{
						m_pModel[CPlayer::BODY]->SetModelColor(2, m_presentColor);
					}
					if (m_pIcon != nullptr)
					{
						m_pIcon->SetColor(m_presentColor);
					}
					if (m_pUiString != nullptr)
					{
						m_pUiString->ChangeColor(m_presentColor);
					}
				}

				if (CInputKeyboard::GetKeyboardTrigger(DIK_S) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, m_nIdx))
				{
					m_nPresentHead--;

					if (m_nPresentHead < 0)
					{
						m_nPresentHead = HEAD_MAX - 1;
					}

					if (m_pModel[CPlayer::HEAD] != nullptr)
					{
						m_pModel[CPlayer::HEAD]->SetModel(m_HeadTypeAll[m_nPresentHead]);
					}

					m_HeadType[m_nIdx] = m_HeadTypeAll[m_nPresentHead];
				}
				else if (CInputKeyboard::GetKeyboardTrigger(DIK_W) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, m_nIdx))
				{
					m_nPresentHead++;

					if (m_nPresentHead >= HEAD_MAX)
					{
						m_nPresentHead = 0;
					}

					if (m_pModel[CPlayer::HEAD] != nullptr)
					{
						m_pModel[CPlayer::HEAD]->SetModel(m_HeadTypeAll[m_nPresentHead]);
					}

					m_HeadType[m_nIdx] = m_HeadTypeAll[m_nPresentHead];
				}

				if (CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, m_nIdx))
				{//準備完了
					m_bDecision = true;
					
					if (m_pParent != nullptr)
					{
						m_pParent->AddPlayerCounnt(1);
					}

					if (m_pOK == nullptr)
					{
						CAnimateUI::UIAnimation animInfo;
						animInfo.deltaSize = D3DXVECTOR2(0.5f, 0.5f);
						animInfo.nChangeTime = 30;
						m_pOK = CAnimateUI::Create(CObject::TEXTURE_OK_UI, D3DXVECTOR3(((float)SCREEN_WIDTH / 5.0f) * (m_nIdx + 1), (float)SCREEN_HEIGHT * 0.425f, 0.0f), D3DXVECTOR2(65.0f, 40.0f),
							D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.75f), animInfo);
						m_pOK->AnimateColor(true);
					}
				}
			}
			else
			{
				if (CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_A, m_nIdx))
				{//準備中断
					m_bDecision = false;
					m_pParent->AddPlayerCounnt(-1);

					if (m_pOK != nullptr)
					{
						m_pOK->Release();
						m_pOK = nullptr;
					}
				}
			}
		}
	}
}

//描画処理
void CPlayerModel::Draw(void)
{
	D3DXMATRIX mtxTrans, mtxRot;												//計算用のマトリックス
	D3DXMatrixIdentity(&m_mtxWorld);											//ワールドマトリックスの初期化処理

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_pModel[CPlayer::BODY]->Draw(m_mtxWorld);											//最初のモデルの描画処理

	for (int nCnt = 1; nCnt < CPlayer::PARTS_MAX; nCnt++)
	{//他のモデルの描画処理
		if (m_pModel[nCnt] != nullptr)
		{
			m_pModel[nCnt]->Draw();
		}
	}

	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//位置の設定処理
void CPlayerModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//向きの設定処理
void CPlayerModel::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

void CPlayerModel::SetStage(CPlayerSelect* pStage)
{
	m_pParent = pStage;
}

//サイズの取得処理
const D3DXVECTOR2 CPlayerModel::GetSize(void)
{
	return Vec2Null;
}

//位置の取得処理
const D3DXVECTOR3 CPlayerModel::GetPos(void)
{
	return m_pos;
}

//カーラーの取得処理
const D3DXCOLOR*  CPlayerModel::GetPlayerColors(void)
{
	return m_playersCol;
}






CModel::ModelType CPlayerModel::GetHeadType(int nIdx)
{
	return m_HeadType[nIdx];
}


//生成処理
CPlayerModel* CPlayerModel::Create(const D3DXVECTOR3 pos, int nIdx, bool bUi)
{
	if (nIdx >= PLAYER_MAX)
	{
		return nullptr;
	}

	CPlayerModel* pModel = new CPlayerModel;

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_rot = Vec3Null;
	pModel->m_nIdx = nIdx;
	pModel->m_nPresentColor = nIdx;
	pModel->m_presentColor = CPlayer::GetPlayerColors()[nIdx];
	pModel->m_bSelect = bUi;

	pModel->m_pos = pos;
	pModel->m_pModel[CPlayer::BODY] = CModelPart::Create(CModel::MODEL_BODY, D3DXVECTOR3(0.0f, 17.0f, 0.0f), Vec3Null);				//体のモデルを生成する

	pModel->m_pModel[CPlayer::HEAD] = CModelPart::Create(CModel::MODEL_HEAD, D3DXVECTOR3(0.0f, 7.0f, 0.0f), Vec3Null);				//頭のモデルを生成する
	pModel->m_pModel[CPlayer::HEAD]->SetParent(pModel->m_pModel[CPlayer::BODY]);																//頭の親を設定する

	pModel->m_pModel[CPlayer::LEFT_ARM] = CModelPart::Create(CModel::MODEL_LEFT_ARM, D3DXVECTOR3(8.0f, 3.0f, 0.0f), Vec3Null);		//左腕のモデルを生成する
	pModel->m_pModel[CPlayer::LEFT_ARM]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//左腕の親を設定する

	pModel->m_pModel[CPlayer::LEFT_HAND] = CModelPart::Create(CModel::MODEL_LEFT_HAND, D3DXVECTOR3(9.0f, 0.0f, 0.0f), Vec3Null);		//左手のモデルを生成する
	pModel->m_pModel[CPlayer::LEFT_HAND]->SetParent(pModel->m_pModel[CPlayer::LEFT_ARM]);														//左手の親を設定する

	pModel->m_pModel[CPlayer::RIGHT_ARM] = CModelPart::Create(CModel::MODEL_RIGHT_ARM, D3DXVECTOR3(-8.0f, 3.0f, 0.0f), Vec3Null);	//右腕のモデルを生成する
	pModel->m_pModel[CPlayer::RIGHT_ARM]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//右腕の親を設定する

	pModel->m_pModel[CPlayer::RIGHT_HAND] = CModelPart::Create(CModel::MODEL_RIGHT_HAND, D3DXVECTOR3(-9.0f, 0.0f, 0.0f), Vec3Null);	//右手のモデルを生成する
	pModel->m_pModel[CPlayer::RIGHT_HAND]->SetParent(pModel->m_pModel[CPlayer::RIGHT_ARM]);													//右手の親を設定する

	pModel->m_pModel[CPlayer::LEFT_LEG] = CModelPart::Create(CModel::MODEL_LEFT_LEG, D3DXVECTOR3(3.0f, -9.0f, 0.0f), Vec3Null);		//左太腿のモデルを生成する
	pModel->m_pModel[CPlayer::LEFT_LEG]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//左太腿の親を設定する

	pModel->m_pModel[CPlayer::LEFT_FOOT] = CModelPart::Create(CModel::MODEL_LEFT_FOOT, D3DXVECTOR3(0.1f, -5.0f, 0.0f), Vec3Null);	//左足のモデルを生成する
	pModel->m_pModel[CPlayer::LEFT_FOOT]->SetParent(pModel->m_pModel[CPlayer::LEFT_LEG]);														//左足の親を設定する

	pModel->m_pModel[CPlayer::RIGHT_LEG] = CModelPart::Create(CModel::MODEL_RIGHT_LEG, D3DXVECTOR3(-3.0f, -9.0f, 0.0f), Vec3Null);	//右太腿のモデルを生成する
	pModel->m_pModel[CPlayer::RIGHT_LEG]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//右太腿の親を設定する

	pModel->m_pModel[CPlayer::RIGHT_FOOT] = CModelPart::Create(CModel::MODEL_RIGHT_FOOT, D3DXVECTOR3(-0.1f, -5.0f, 0.0f), Vec3Null);//右足のモデルを生成する
	pModel->m_pModel[CPlayer::RIGHT_FOOT]->SetParent(pModel->m_pModel[CPlayer::RIGHT_LEG]);													//右足の親を設定する

	std::vector <CModelPart*> vParts;
	vParts.clear();
	vParts.push_back(pModel->m_pModel[CPlayer::BODY]);
	vParts.push_back(pModel->m_pModel[CPlayer::HEAD]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_ARM]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_HAND]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_ARM]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_HAND]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_LEG]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_FOOT]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_LEG]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_FOOT]);

	pModel->m_pAnimator = CAnimator::Create(&vParts, CAnimator::ANIM_TYPE_PLAYER);

	pModel->m_pAnimator->SetPresentAnim(5);

	pModel->m_pModel[CPlayer::BODY]->SetModelColor(2, pModel->m_presentColor);

	if (bUi)
	{
		pModel->m_pIcon = CObject_2D::Create();
		pModel->m_pIcon->SetPos(D3DXVECTOR3(((float)SCREEN_WIDTH / 5.0f) * (nIdx + 1), (float)SCREEN_HEIGHT * 0.725f, 0.0f));
		pModel->m_pIcon->SetSize(D3DXVECTOR2(100.0f, 15.0f));
		pModel->m_pIcon->SetTexture(CObject::TEXTURE_NULL);
		pModel->m_pIcon->SetColor(pModel->m_presentColor);

		pModel->m_pAnimator->SetPresentAnim(0);

		std::string str;
		str.clear();
		str = std::to_string(nIdx + 1);
		str += "P";
		const char* pStr = str.c_str();
		pModel->m_pUiString = CUIString::Create(D3DXVECTOR3((((float)SCREEN_WIDTH / 5.0f) * (nIdx + 1)) - 50.0f, (float)SCREEN_HEIGHT * 0.275f, 0.0f), D3DXVECTOR2(100.0f, 60.0f), pModel->m_presentColor, pStr);
	
	}
	else
	{
		int nColor = random(0, (int)CPlayer::PLAYER_COLOR_MAX - 1);

		pModel->m_pModel[CPlayer::HEAD]->SetModel(m_HeadTypeAll[random(0, (int)HEAD_MAX - 1)]);
		pModel->m_pModel[CPlayer::BODY]->SetModelColor(2, CPlayer::GetPlayerColors()[nColor]);
	}

	m_HeadType[nIdx] = m_HeadTypeAll[0];

	return pModel;
}