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
	// スフィアメッシュ
	CHalfSphere* pSphere1 = CHalfSphere::Create(D3DXVECTOR3(0.0f, -8000.0f, 1000.0f), D3DXVECTOR3(30000.0f, 0.0f, 30000.0f), D3DXVECTOR3(D3DX_PI * -0.15f, D3DX_PI, 0.0f), CHalfSphere::SPHERE_UP);
	pSphere1->LoadTexture("data\\TEXTURE\\sky002.jpg");

	CHalfSphere* pSphere2 = CHalfSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(35000.0f, 0.0f, 35000.0f), D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI), CHalfSphere::SPHERE_DOWN);
	pSphere2->LoadTexture("data\\TEXTURE\\sky002.jpg");

	if (m_pField != nullptr)
	{
		m_pField->SetPriority(1);
	}
	CGoal::Create(D3DXVECTOR3(0.0f, -100.0f, 900.0f));

	m_pField = CMeshfield::Create(D3DXVECTOR3(-135.0f, -150.0f, 1100.0f), Vec3Null, D3DXVECTOR2(30.0f, 70.0f), 40, 10, 3);
	m_pField->SetTexture(CObject::TEXTURE_BLOCK);
	m_pField->SetTextureTiling(0.33f);

	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-135.0f, -150.0f, -1800.0f), Vec3Null, D3DXVECTOR2(30.0f, 70.0f), 20, 10, 3);
	pField->SetTexture(CObject::TEXTURE_BLOCK);
	pField->SetTextureTiling(0.33f);

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

	CSilhouette::Create();

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