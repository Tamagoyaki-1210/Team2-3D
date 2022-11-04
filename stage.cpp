//=============================================================================
//
// stage.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "stage.h"
#include "application.h"
#include "meshfield.h"
#include "object2D.h"
#include "object3D.h"
#include "billboard.h"
#include "model.h"
#include "player.h"
#include "UIString.h"
#include "Letter.h"
#include "debugProc.h"
#include "font.h"
#include "halfsphere.h"
#include "CylinderHitbox.h"
#include "BoxHitbox.h"
#include "coin.h"
#include "goal.h"
#include "camera.h"
#include "SpikeBall.h"
#include "score.h"

CMeshfield *CStage::m_pField = nullptr;
CHalfSphere* CStage::m_pSphere[PLAYER_MAX] = {};
CPlayer* CStage::m_pPlayer[PLAYER_MAX] = {};
bool CStage::m_bResult = false;

//=====================================
// デフォルトコンストラクタ
//=====================================
CStage::CStage()
{

}

//=====================================
// デストラクタ
//=====================================
CStage::~CStage()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CStage::Init(void)
{
	// メッシュフィールドの生成
	m_pField = CMeshfield::Create(D3DXVECTOR3(-200.0f, -150.0f, 1100.0f), Vec3Null, D3DXVECTOR2(30.0f, 70.0f), 20, 10, 3);
	m_pField->SetTexture(CObject::TEXTURE_BLOCK);
	m_pField->SetTextureTiling(0.33f);

	// スフィアメッシュ
	m_pSphere[0] = CHalfSphere::Create(D3DXVECTOR3(0.0f, -2000.0f, 1000.0f), D3DXVECTOR3(30000.0f, 0.0f, 30000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CHalfSphere::SPHERE_UP);
	m_pSphere[0]->LoadTexture("data\\TEXTURE\\sky001.jpg");

	m_pSphere[1] = CHalfSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(35000.0f, 0.0f, 35000.0f), D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI), CHalfSphere::SPHERE_DOWN);
	m_pSphere[1]->LoadTexture("data\\TEXTURE\\89_m.jpg");

	CGoal::Create();

	// プレイヤーの生成
	m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, -100.0f, -100.0f), 0);
	m_pPlayer[1] = CPlayer::Create(D3DXVECTOR3(-50.0f, -100.0f, -100.0f), 1);
	m_pPlayer[2] = CPlayer::Create(D3DXVECTOR3(-100.0f, -100.0f, -100.0f), 2);
	m_pPlayer[3] = CPlayer::Create(D3DXVECTOR3(-150.0f, -100.0f, -100.0f), 3);

	CObject_2D* pObj2D = CObject_2D::Create();
	pObj2D->SetPos(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	pObj2D->SetSize(D3DXVECTOR2(20.0f, 20.0f));
	pObj2D->SetTexture(CObject::TEXTURE_LETTERS);
	pObj2D->SetTextureParameter(5, 13, 2, 60);
	pObj2D->SetAnimPattern(15);
	pObj2D->SetAnimationBase(15);

	// オブジェクト3Dの生成
	//CObject_3D* pObj = CObject_3D::Create();
	//pObj->SetPos(D3DXVECTOR3(0.0f, -200.0f, 300.0f));
	//pObj->SetSize(D3DXVECTOR2(100.0f, 100.0f));
	//pObj->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	//pObj->SetStartingRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//pObj->SetTexture(CObject::TEXTURE_BLOCK);
	//pObj->SetTextureParameter(1, 1, 1, INT_MAX);

	// モデルの生成
	//CModel::Create(CModel::MODEL_JEWEL_TEAR, D3DXVECTOR3(0.0f, -100.0f, -150.0f));
	//CModel::Create(CModel::MODEL_JEWEL_TEAR, D3DXVECTOR3(0.0f, -100.0f, 150.0f));

	// ビルボードの生成
	//CBillboard* pBillboard = CBillboard::Create(D3DXVECTOR3(-150.0f, 0.0f, 300.0f), D3DXVECTOR2(50.0f, 50.0f), 3);
	//pBillboard->SetTexture(CObject::TEXTURE_BLOCK);

	// UIStringの生成
	CUIString::Create(D3DXVECTOR3(100.0f, 200.0f, 0.0f), D3DXVECTOR2(250.0f, 25.0f), D3DXCOLOR(0.2f, 1.0f, 0.5f, 1.0f), "Sentence A, 125 $%&");

	CLetter::Create(D3DXVECTOR3(200.0f, 100.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 'r', 5);

	CLetter::Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 4, 5);

	CBoxHitbox::Create(D3DXVECTOR3(-200.0f, -150.0f, 200.0f), Vec3Null, D3DXVECTOR3(50.0f, 300.0f, 50.0f), CHitbox::TYPE_OBSTACLE, nullptr, -30, CHitbox::EFFECT_LAUNCH);
	CCylinderHitbox::Create(D3DXVECTOR3(150.0f, -150.0f, 200.0f), Vec3Null, D3DXVECTOR3(150.0f, 300.0f, 150.0f), CHitbox::TYPE_NEUTRAL, nullptr);

	CCoin::Create(D3DXVECTOR3(-100.0f, -125.0f, 200.0f), CCoin::COIN_0);
	CCoin::Create(D3DXVECTOR3(0.0f, -125.0f, 200.0f), CCoin::COIN_1);
	CCoin::Create(D3DXVECTOR3(100.0f, -125.0f, 200.0f), CCoin::COIN_2);
	CCoin::Create(D3DXVECTOR3(200.0f, -125.0f, 200.0f), CCoin::COIN_3);

	CSpikeBall::Create(D3DXVECTOR3(-50.0f, -125.0f, 500.0f));

	//CModel::Create(CModel::MODEL_SPIKE_BALL, D3DXVECTOR3(-50.0f, -125.0f, 500.0f));

	//CModel* pModel = nullptr;
	//CModel::Create(CModel::MODEL_OBSTACLE_0, D3DXVECTOR3(-100.0f, -120.0f, 300.0f));
	//CModel::Create(CModel::MODEL_OBSTACLE_1, D3DXVECTOR3(0.0f, -120.0f, 300.0f));
	//CModel::Create(CModel::MODEL_OBSTACLE_2, D3DXVECTOR3(100.0f, -120.0f, 300.0f));
	//pModel = CModel::Create(CModel::MODEL_OBSTACLE_3, D3DXVECTOR3(200.0f, -120.0f, 300.0f));
	//pModel->SetModelColor(4, D3DXCOLOR(0.68f, 0.68f, 0.68f, 1.0f));

	//UI
	//m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 140.0f, 50.0f, 0.0f));

	if (CApplication::GetCamera() != nullptr)
	{
		CApplication::GetCamera()->SetPos(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, -200.0f, 100.0f));
	}

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CStage::Uninit(void)
{
	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (m_pPlayer[nCnt] != nullptr)
		{
			m_pPlayer[nCnt]->Release();
			m_pPlayer[nCnt] = nullptr;
		}
	}

	if (m_pSphere[0] != nullptr)
	{
		m_pSphere[0]->Release();
		m_pSphere[0] = nullptr;
	}

	if (m_pField != nullptr)
	{
		m_pField->Release();
		m_pField = nullptr;
	}
}

//=====================================
// 更新処理
//=====================================
void CStage::Update(void)
{
	GameResult();
}

//=====================================
// 生成処理
//=====================================
CStage* CStage::Create(void)
{
	CStage* pStage = new CStage;

	if (FAILED(pStage->Init()))
	{
		return nullptr;
	}

	return pStage;
}

void CStage::GameResult()
{
	bool bGoal[PLAYER_MAX] = {};
	bool bRot[PLAYER_MAX] = {};

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		bGoal[nCnt] = m_pPlayer[nCnt]->GetGoal();
		bRot[nCnt] = m_pPlayer[nCnt]->GetRotCmp();
	}
	
	if (bGoal[0] && bGoal[1] && bGoal[2] && bGoal[3]
		&& bRot[0] && bRot[1] && bRot[2] && bRot[3])
	{
		m_bResult = true;
		ScoreComparison();
	}
}

int CStage::ScoreComparison()
{
	int nCnt = 0;

	if (m_bResult)
	{
		D3DXVECTOR2 PlayerScore[PLAYER_MAX] = {};
		D3DXVECTOR2 nChange;

		for (int nCount = 0; nCount < PLAYER_MAX; nCount++)
		{
			PlayerScore[nCount].x = (float)CScore::GetScore(nCount);
			PlayerScore[nCount].y = (float)nCount;
		}

		for (int nCount = 0; nCount < PLAYER_MAX - 1; nCount++)
		{
			for (int nCount2 = nCount + 1; nCount2 < PLAYER_MAX; nCount2++)
			{
				if (PlayerScore[nCount].x < PlayerScore[nCount2].x)
				{
					nChange = PlayerScore[nCount2];
					PlayerScore[nCount2] = PlayerScore[nCount];
					PlayerScore[nCount] = nChange;
				}
			}
		}

		if ((int)PlayerScore[3].x == (int)PlayerScore[0].x)
		{
			m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[1].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[2].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[3].y]->SetWinner(true);

			m_pPlayer[(int)PlayerScore[0].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[1].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[2].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[3].y]->MoveWinner();
			nCnt = 4;
		}
		else if ((int)PlayerScore[2].x == (int)PlayerScore[0].x)
		{
			m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[1].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[2].y]->SetWinner(true);

			m_pPlayer[(int)PlayerScore[0].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[1].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[2].y]->MoveWinner();
			nCnt = 3;
		}
		else if ((int)PlayerScore[1].x == (int)PlayerScore[0].x)
		{
			m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[1].y]->SetWinner(true);

			m_pPlayer[(int)PlayerScore[0].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[1].y]->MoveWinner();
			nCnt = 2;
		}
		else
		{
			m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);

			m_pPlayer[(int)PlayerScore[0].y]->MoveWinner();
			nCnt = 1;
		}
	}

	return nCnt;
}