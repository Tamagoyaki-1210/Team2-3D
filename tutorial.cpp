//=============================================================================
//
// tutorial.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "tutorial.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "application.h"
#include "meshfield.h"
#include "player.h"
#include "halfsphere.h"
#include "coin.h"
#include "goal.h"
#include "camera.h"
#include "SpikeBall.h"
#include "lavaFloor.h"
#include "score.h"
#include "message.h"
#include "silhouette.h"
#include "environment.h"
#include "trampoline.h"
#include "bouncePole.h"
#include "stoneSpawner.h"
#include "icePillarSpawner.h"

CMeshfield *CTutorial::m_pField = {};
CPlayer* CTutorial::m_pPlayer[PLAYER_MAX] = {};
CMessage* CTutorial::m_pMessage = nullptr;
bool CTutorial::m_bEndTutorial = false;

//=====================================
// デフォルトコンストラクタ
//=====================================
CTutorial::CTutorial()
{
	m_pUi = nullptr;
	m_bChange = false;
}

//=====================================
// デストラクタ
//=====================================
CTutorial::~CTutorial()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CTutorial::Init(void)
{
	LPDIRECT3DTEXTURE9 pTex = CObject_2D::GetTexturePointer(CObject::TEXTURE_SKY);

	// スフィアメッシュ
	CHalfSphere* pSphere1 = CHalfSphere::Create(D3DXVECTOR3(0.0f, -8000.0f, 1000.0f), D3DXVECTOR3(30000.0f, 0.0f, 30000.0f), D3DXVECTOR3(D3DX_PI * -0.15f, D3DX_PI, 0.0f), CHalfSphere::SPHERE_UP);
	pSphere1->BindTexture(pTex);

	pSphere1 = CHalfSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(35000.0f, 0.0f, 35000.0f), D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI), CHalfSphere::SPHERE_DOWN);
	pSphere1->BindTexture(pTex);

	if (m_pField != nullptr)
	{
		m_pField->SetPriority(1);
	}
	CGoal::Create(D3DXVECTOR3(0.0f, -100.0f, 900.0f));

	m_pField = CMeshfield::Create(D3DXVECTOR3(-135.0f, -150.0f, 1100.0f), Vec3Null, D3DXVECTOR2(30.0f, 70.0f), 40, 10, 3);
	m_pField->SetTexture(CObject::TEXTURE_BLOCK);
	m_pField->SetTextureTiling(0.33f);
	m_pField->SetPriority(1);

	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-135.0f, -150.0f, -1800.0f), Vec3Null, D3DXVECTOR2(30.0f, 70.0f), 20, 10, 3);
	pField->SetTexture(CObject::TEXTURE_BLOCK);
	pField->SetTextureTiling(0.33f);
	m_pField->SetPriority(1);

	// プレイヤーの生成
	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		m_pPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(-75.0f + (50 * nCnt), -150.0f, ((60 - 20) * -70.0f) - 200.0f), nCnt);
	}

	// メッセージの生成
	m_pMessage = CMessage::Create();

	// カウントダウンメッセージ表示
	m_pMessage->SetCountDown(3);

	if (CApplication::GetCamera() != nullptr)
	{
		CApplication::GetCamera()->SetPos(D3DXVECTOR3(0.0f, 0.0f, ((60 - 21) * -70.0f) - 500.0f), D3DXVECTOR3(0.0f, -200.0f, 100.0f));
	}

	m_pUi = CObject_2D::Create();
	m_pUi->SetPos(D3DXVECTOR3(640.0f, 90.0f, 0.0f));
	m_pUi->SetSize(D3DXVECTOR2(105.0f, 54.0f));
	m_pUi->SetTexture(CObject::TEXTURE_TUTORIAL_MOVE);
	m_pUi->SetTextureParameter(8, 2, 4, 20);
	m_pUi->SetPriority(5);

	CSilhouette::Create();

	m_bChange = false;

	SetObject();

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CTutorial::Uninit(void)
{
	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (m_pPlayer[nCnt] != nullptr)
		{
			m_pPlayer[nCnt]->Release();
			m_pPlayer[nCnt] = nullptr;
		}
	}

	if (m_pField != nullptr)
	{
		m_pField->Release();
		m_pField = nullptr;
	}

	if (m_pMessage != nullptr)
	{
		m_pMessage->Uninit();
		delete m_pMessage;
		m_pMessage = nullptr;
	}
	if (m_pUi != nullptr)
	{
		m_pUi->Release();
		m_pUi = nullptr;
	}

	m_bEndTutorial = false;
}

//=====================================
// 更新処理
//=====================================
void CTutorial::Update(void)
{
	//ゲーム中の処理
	if (m_bEndTutorial == false)
	{
		//Pでポーズ切り替え
		if (CInputKeyboard::GetKeyboardTrigger(DIK_P) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 0))
		{
			CApplication::SetMode(CApplication::Mode_Title);
		}
	}

	D3DXVECTOR3 cameraPos = CApplication::GetCamera()->GetPos();

	if (cameraPos.z >= -2900.0f && !m_bChange)
	{
		m_bChange = true;

		m_pUi->SetSize(D3DXVECTOR2(200.0f, 66.7f));
		m_pUi->SetTexture(CObject::TEXTURE_TUTORIAL_BUTTON);
		m_pUi->SetTextureParameter(2, 1, 2, 20);
	}

	if (cameraPos.z >= -2450.0f && m_bChange)
	{
		m_bChange = false;

		m_pUi->SetSize(D3DXVECTOR2(0.0f, 66.7f));
		m_pUi->SetTexture(CObject::TEXTURE_TUTORIAL_BUTTON);
		m_pUi->SetTextureParameter(2, 1, 2, 20);
	}


	if (cameraPos.z >= 600.0f)
	{
		CApplication::SetMode(CApplication::Mode_Title);
	}


	if (m_pMessage != nullptr)
	{
		m_pMessage->Update();
	}
}

//=====================================
// 更新処理
//=====================================
void CTutorial::SetEndTutorial(void)
{
	m_bEndTutorial = true;
}

//=====================================
// 生成処理
//=====================================
CTutorial* CTutorial::Create(void)
{
	CTutorial* pTutorial = new CTutorial;

	if (FAILED(pTutorial->Init()))
	{
		return nullptr;
	}

	return pTutorial;
}



//=====================================
// プライベート関数
//=====================================


//オブジェクトの配置処理
void CTutorial::SetObject(void)
{
	CCoin* pCoin = nullptr;
	CLavaFloor* pLava = nullptr;
	CMeshfield* pField = nullptr;

	for (int nCnt = 0; nCnt < 36; nCnt++)
	{
		pCoin = CCoin::Create(D3DXVECTOR3(-100.0f + 25.0f * (nCnt % 9) ,-75.0f ,-2150.0f + 75.0f * (nCnt / 9)), (CCoin::COIN_TYPE)CObject::random((int)CCoin::COIN_0, (int)CCoin::COIN_3));
		pCoin->SetShadowHeight(-99.0f);
	}

	CSpikeBall::Create(D3DXVECTOR3(-75.0f, -135.0f, -1500.0f));
	CSpikeBall::Create(D3DXVECTOR3(-25.0f, -135.0f, -1500.0f));
	CSpikeBall::Create(D3DXVECTOR3( 25.0f, -135.0f, -1500.0f));
	CSpikeBall::Create(D3DXVECTOR3( 75.0f, -135.0f, -1500.0f));

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pLava = CLavaFloor::Create(D3DXVECTOR3(-110.0f + 50.0f * (nCnt), -149.0f, -1250.0f));
		pLava->SetShadowDraw(false);
		pLava = CLavaFloor::Create(D3DXVECTOR3( 110.0f - 50.0f * (nCnt), -149.0f, -1250.0f));
		pLava->SetShadowDraw(false);
	}


	pField = CMeshfield::Create(D3DXVECTOR3(-135.0f, -149.9f, -300.0f), Vec3Null, D3DXVECTOR2(30.0f, 70.0f), 12, 10, 0.01f);
	pField->SetTexture(CObject::TEXTURE_ICE);
	pField->ChangeHeight(0, 100, 0.1f);
	pField->SetPriority(0);

	CBouncePole::Create(D3DXVECTOR3(-85.0f, -150.0f, -900.0f));
	CBouncePole::Create(D3DXVECTOR3(-85.0f, -150.0f, -500.0f));

	CTrampoline::Create(D3DXVECTOR3(-75.0f, -150.0f, -700.0f));
	CTrampoline::Create(D3DXVECTOR3(-25.0f, -150.0f, -700.0f));
	CTrampoline::Create(D3DXVECTOR3( 25.0f, -150.0f, -700.0f));
	CTrampoline::Create(D3DXVECTOR3( 75.0f, -150.0f, -700.0f));

	CStoneSpawner::Create(D3DXVECTOR3(0.0f, 150.0f, 150.0f), -149.9f, 135.0f, 200.0f, 30);

	//pCoin = CCoin::Create(D3DXVECTOR3(), (CCoin::COIN_TYPE)CObject::random((int)CCoin::COIN_0, (int)CCoin::COIN_3));
}