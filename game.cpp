//=============================================================================
//
// game.h
// Author : tanimoto kosuke
//
//=============================================================================
#include "game.h"
#include "input.h"
#include "application.h"
#include "mode.h"
#include "meshfield.h"
#include "object2D.h"
#include "object3D.h"
#include "billboard.h"
#include "model.h"
#include "player.h"
#include "UIString.h"
//#include "menu.h"
//#include "fade.h"

bool CGame::m_bPause = true;		//ポーズ使用判定
bool CGame::m_bEndGame = false;		//ゲーム終了判定
CMeshField *CGame::m_pField = nullptr;
CPlayer* CGame::m_pPlayer = nullptr;

//=====================================
//デフォルトコンストラクタ
//=====================================
CGame::CGame()
{

}

//=====================================
//デストラクタ
//=====================================
CGame::~CGame()
{

}

//=====================================
//初期化処理
//=====================================
void CGame::Init()
{
	// メッシュフィールドの生成
	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-1000.0f, -150.0f, 1000.0f), Vec3Null, D3DXVECTOR2(50.0f, 50.0f), 30, 30, 3);
	pField->SetTexture(CObject::TEXTURE_BLOCK);
	pField->SetTextureTiling(0.33f);

	// オブジェクト3Dの生成
	CObject_3D* pObj = CObject_3D::Create();
	pObj->SetPos(D3DXVECTOR3(0.0f, -200.0f, 300.0f));
	pObj->SetSize(D3DXVECTOR2(100.0f, 100.0f));
	pObj->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	pObj->SetStartingRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pObj->SetTexture(CObject::TEXTURE_BLOCK);
	pObj->SetTextureParameter(1, 1, 1, INT_MAX);

	// モデルの生成
	//CModel::Create(CModel::MODEL_JEWEL_TEAR, D3DXVECTOR3(0.0f, -100.0f, -150.0f));
	//CModel::Create(CModel::MODEL_JEWEL_TEAR, D3DXVECTOR3(0.0f, -100.0f, 150.0f));

	//UI
	//m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 140.0f, 50.0f, 0.0f));
	//CMenu::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), CMenu::TYPE_NONE, CMenu::MODE_GAME);

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, -100.0f, -100.0f));

	// ビルボードの生成
	CBillboard* pBillboard = CBillboard::Create(D3DXVECTOR3(-150.0f, 0.0f, 300.0f), D3DXVECTOR2(50.0f, 50.0f), 3);
	pBillboard->SetTexture(CObject::TEXTURE_BLOCK);

	// UIStringの生成
	CUIString::Create(D3DXVECTOR3(100.0f, 200.0f, 0.0f), D3DXVECTOR2(250.0f, 25.0f), D3DXCOLOR(0.2f, 1.0f, 0.5f, 1.0f), "Sentence A, 125 $%&");


	m_bPause = false;	//ポーズ未使用
}

//=====================================
//終了処理
//=====================================
void CGame::Uninit()
{
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	CObject::ReleaseAll();
	m_bPause = true;
}

//=====================================
//更新処理
//=====================================
void CGame::Update()
{
	//CFade *pFade = CMode::GetFade();

	////フェードしていない場合
	//if (pFade->GetFade() == CFade::FADE_NONE)
	//{
	//	CInput *pInput = CApplication::GetInput();

	//	//Pでポーズ切り替え
	//	if (pInput->GetKeyboardTrigger(DIK_P))
	//	{
	//		if (!m_bPause)
	//		{
	//			CSound::PlaySound(SOUND_LABEL_SE_WHISTLE_STOP);
	//		}
	//		else
	//		{
	//			CSound::PlaySound(SOUND_LABEL_SE_WHISTLE_START);
	//		}
	//		m_bPause = !m_bPause;
	//	}

	//	//ゲーム終了時の処理
	//	if (m_bEndGame == true)
	//	{
	//		CMode *pMode = CApplication::GetMode();

	//		pMode->ChangeMode(CMode::MODE_RESULT);

	//		m_bEndGame = false;
	//	}
	//}

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Update();
	}
}

//=====================================
//描画処理
//=====================================
void CGame::Draw()
{
	
}
