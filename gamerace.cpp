//=============================================================================
//
// gamerace.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "gamerace.h"
#include "input.h"
#include "application.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "message.h"
#include "fade.h"
#include "stage.h"

CMessage* CGameRace::m_pMessage = nullptr;
CStage* CGameRace::m_pStage = nullptr;

//=====================================
// デフォルトコンストラクタ
//=====================================
CGameRace::CGameRace()
{

}

//=====================================
// デストラクタ
//=====================================
CGameRace::~CGameRace()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CGameRace::Init(void)
{
    CGame::Init();

	m_pStage = CStage::Create();

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

	CGoal::Create();

	// プレイヤーの生成
	m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(-50.0f, -100.0f, -100.0f),0);
	m_pPlayer[0]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	m_pPlayer[1] = CPlayer::Create(D3DXVECTOR3(0.0f, -100.0f, -100.0f), 1);
	m_pPlayer[1]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	m_pPlayer[2] = CPlayer::Create(D3DXVECTOR3(-100.0f, -100.0f, -100.0f), 2);
	m_pPlayer[2]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	m_pPlayer[3] = CPlayer::Create(D3DXVECTOR3(-150.0f, -100.0f, -100.0f), 3);
	m_pPlayer[3]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	// ビルボードの生成
	//CBillboard* pBillboard = CBillboard::Create(D3DXVECTOR3(-150.0f, 0.0f, 300.0f), D3DXVECTOR2(50.0f, 50.0f), 3);
	//pBillboard->SetTexture(CObject::TEXTURE_BLOCK);

	m_pSphere[0] = CHalfSphere::Create(D3DXVECTOR3(0.0f, -2000.0f, 1000.0f), D3DXVECTOR3(30000.0f, 0.0f, 30000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),CHalfSphere::SPHERE_UP);
    m_pSphere[0]->LoadTexture("data\\TEXTURE\\sky001.jpg");

	m_pSphere[1] = CHalfSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(35000.0f, 0.0f, 35000.0f), D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI), CHalfSphere::SPHERE_DOWN);
	m_pSphere[1]->LoadTexture("data\\TEXTURE\\89_m.jpg");

    // UIStringの生成
    CUIString::Create(D3DXVECTOR3(100.0f, 200.0f, 0.0f), D3DXVECTOR2(250.0f, 25.0f), D3DXCOLOR(0.2f, 1.0f, 0.5f, 1.0f), "Sentence A, 125 $%&");

    CLetter::Create(D3DXVECTOR3(200.0f, 100.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 'r', 5);

    CLetter::Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 4, 5);

	CBoxHitbox::Create(D3DXVECTOR3(-200.0f, -150.0f, 200.0f), Vec3Null, D3DXVECTOR3(50.0f, 300.0f, 50.0f), CHitbox::TYPE_NEUTRAL, nullptr, -30, CHitbox::EFFECT_LAUNCH);
	CCylinderHitbox::Create(D3DXVECTOR3(150.0f, -150.0f, 200.0f), Vec3Null, D3DXVECTOR3(150.0f, 300.0f, 150.0f), CHitbox::TYPE_NEUTRAL, nullptr);

	CBoxHitbox::Create(D3DXVECTOR3(0.0f, -150.0f, 400.0f), Vec3Null, D3DXVECTOR3(50.0f, 50.0f, 50.0f), CHitbox::TYPE_NEUTRAL, nullptr);
	CBoxHitbox::Create(D3DXVECTOR3(0.0f, -100.0f, 400.0f), Vec3Null, D3DXVECTOR3(45.0f, 10.0f, 45.0f), CHitbox::TYPE_OBSTACLE, nullptr, -30, CHitbox::EFFECT_LAUNCH);

    CCoin::Create(D3DXVECTOR3(-100.0f, -125.0f, 200.0f), CCoin::COIN_0);
    CCoin::Create(D3DXVECTOR3(0.0f, -125.0f, 200.0f), CCoin::COIN_1);
    CCoin::Create(D3DXVECTOR3(100.0f, -125.0f, 200.0f), CCoin::COIN_2);
    CCoin::Create(D3DXVECTOR3(200.0f, -125.0f, 200.0f), CCoin::COIN_3);

	CModel* pModel = nullptr;
	CModel::Create(CModel::MODEL_OBSTACLE_0, D3DXVECTOR3(-100.0f, -120.0f, 300.0f));
	CModel::Create(CModel::MODEL_OBSTACLE_1, D3DXVECTOR3(0.0f, -120.0f, 300.0f));
	CModel::Create(CModel::MODEL_OBSTACLE_2, D3DXVECTOR3(100.0f, -120.0f, 300.0f));
	pModel = CModel::Create(CModel::MODEL_OBSTACLE_3, D3DXVECTOR3(200.0f, -120.0f, 300.0f));
	//pModel->SetModelColor(4, D3DXCOLOR(0.68f, 0.68f, 0.68f, 1.0f));

	// メッセージの生成
	m_pMessage = CMessage::Create();

	// カウントダウンメッセージ表示
	m_pMessage->SetCountDown(3);

	//m_pMessage->GoalMessage();

    return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CGameRace::Uninit(void)
{
    CGame::Uninit();

	if (m_pStage != nullptr)
	{
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = nullptr;
	}

	if (m_pMessage != nullptr)
	{
		m_pMessage->Uninit();
		delete m_pMessage;
		m_pMessage = nullptr;
	}
}

//=====================================
// 更新処理
//=====================================
void CGameRace::Update(void)
{
    CGame::Update();

	if (m_pMessage != nullptr)
	{
		m_pMessage->Update();
	}

	if (m_pStage != nullptr)
	{
		m_pStage->Update();
	}

#ifdef _DEBUG

    CDebugProc::Print("\n[F2] : デバッグモードへ移動\n");

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_F2))
		{// F2キーを押したら
			CApplication::SetMode(CApplication::Mode_Game_Debug);
		}
		if (CInputKeyboard::GetKeyboardTrigger(DIK_BACK))
		{// Enterキーを押したら
			SetEndGame();
		}
		if (CInputKeyboard::GetKeyboardTrigger(DIK_G))
		{// Enterキーを押したら
			m_pMessage->GoalMessage(0);
		}
	}

#endif // _DEBUG
}

//=====================================
// 生成処理
//=====================================
CGameRace* CGameRace::Create(void)
{
    CGameRace* pGameRace = new CGameRace;

    if (FAILED(pGameRace->Init()))
    {
        return nullptr;
    }

    return pGameRace;
}