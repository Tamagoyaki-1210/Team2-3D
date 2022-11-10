//=============================================================================
//
// application.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "application.h"
#include "rendering.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "inputPad.h"
#include "directionalLight.h"
#include "camera.h"
#include "model.h"
#include "debugProc.h"
#include "animator.h"
#include "title.h"
#include "playerSelect.h"
#include "stageSelect.h"
#include "gamerace.h"
#include "fade.h"
#include "menu.h"
#include "hitbox.h"
#include "score.h"
#include "tutorial.h"

//静的メンバー変数の宣言
HWND CApplication::m_hWnd;
CRenderer* CApplication::m_pRenderer = nullptr;			//レンディングインスタンスへのポインタ
CInput* CApplication::m_pInput[2] = {};					//インプットインスタンスへのポインタ
CInputMouse* CApplication::m_pMouse = nullptr;			//マウスインスタンスへのポインタ
CInputPad* CApplication::m_pPad = nullptr;
CSound* CApplication::m_pSound = nullptr;
CFade* CApplication::m_pFade = nullptr;
CCamera* CApplication::m_pCamera = nullptr;
CMode* CApplication::m_pMode = nullptr;					// モードへのポインタ
CMenu* CApplication::m_pMenu = nullptr;					// メニューへのポインタ
CDebugProc* CApplication::m_pDebug = nullptr;
CApplication::Mode CApplication::m_mode = CApplication::Mode_Title;
CApplication::Mode CApplication::m_modeNext = CApplication::Mode_Title;
bool CApplication::m_bPause = false;
int CApplication::m_nStageSelect = 0;

//コンストラクタ
CApplication::CApplication()
{
	
}

//デストラクタ
CApplication::~CApplication()
{
	
}

//初期化処理
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd;

	//レンディングインスタンスの生成処理
	if (m_pRenderer == nullptr)
	{//ポインタはnullではなかったら
		m_pRenderer = new CRenderer;
	}

	//レンディングインスタンスの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}

	m_pDebug = CDebugProc::Create();

	//テクスチャ全部をロード処理
	CObject_2D::LoadTextures();

	//モデル全部をロード処理
	CModel::LoadAllModels();

	CAnimator::LoadAllAnimation();

	m_pSound = CSound::Create(hWnd);


	CLight::ReleaseAll();
	CDirectionalLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(2, -5, 2));
	CDirectionalLight::Create(D3DXCOLOR(0.75f, 0.75f, 0.75f, 0.75f), D3DXVECTOR3(-0.2f, 0.2f, 1.0f));

	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, -200.0f, 100.0f));

	// モードインスタンスの生成処理
	m_pMode = CTitle::Create();
	m_mode = Mode_Title;
	m_modeNext = Mode_Title;
	m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	// フェード生成
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create();
		m_pFade->SetFade();
	}

	//キーボードインスタンスの生成処理
	m_pInput[0] = new CInputKeyboard;

	//キーボードの初期化処理
	if (FAILED(m_pInput[0]->Init(hInstance, hWnd, GUID_SysKeyboard)))
	{
		return -1;
	}

	m_pMouse = new CInputMouse;

	if (m_pMouse != nullptr)
	{
		m_pMouse->Init(hInstance, hWnd, GUID_SysMouse);
	}

	m_pPad = new CInputPad;

	if (m_pPad != nullptr)
	{
		m_pPad->Init(hInstance, hWnd, GUID_SysMouse);
	}

	//キーボードの初期化処理
	/*if (FAILED(m_pMouse->Init(hInstance, hWnd, GUID_SysMouse)))
	{
		return -1;
	}*/

	// メニュー生成
	if (m_pMenu == nullptr)
	{
		m_pMenu = CMenu::Create();
	}


	//m_pSphear->Init();

	//FILE*pFile;				//ファイルポインタを宣言する

	//						//ファイルを開く
	//pFile = fopen("data\\charData.txt", "wb");

	//if (pFile != NULL)
	//{//ファイルが開けた場合
	// //ファイルにランキング情報を書き出す

	//	char cData = 33;		//for (int nCnt = 0; nCnt < 93; nCnt++)
	//	char dData[100] = {};

	//	for (int nCnt = 0; nCnt < 93; nCnt++)
	//	{
	//		dData[nCnt] = cData;

	//		fwrite(&cData, sizeof(char), 1, pFile);

	//		cData++;
	//	}

	//	//ファイルを閉じる
	//	fclose(pFile);

	//	int a = 0;
	//}
	//else
	//{//ファイルが開けなかった場合
	//	printf("XXXXX セーブファイルが開けませんでした XXXXX");
	//}

	m_bPause = false;	//ポーズを未使用にする

	m_nStageSelect = 0;

	return S_OK;
}

//終了処理
void CApplication::Uninit(void)
{
	CScore::Clear();

	//レンディングインスタンスの破棄
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// モード
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	//インプットデバイスの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Uninit();
			delete m_pInput[nCnt];
			m_pInput[nCnt] = nullptr;
		}
	}

	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	if (m_pPad != nullptr)
	{
		m_pPad->Uninit();
		delete m_pPad;
		m_pPad = nullptr;
	}

	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	if (m_pMenu != nullptr)
	{
		m_pMenu->Uninit();
		delete m_pMenu;
		m_pMenu = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pDebug != nullptr)
	{
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	//オブジェクト全体の終了処理
	CObject::ReleaseAll();

	//ヒットボックスの破棄処理
	CHitbox::ReleaseAll();

	CLight::ReleaseAll();

	//テクスチャ全部の破棄
	CObject_2D::DestroyLoadedTextures();

	CAnimator::DestroyLoadedAnimation();

	//モデル全部破棄の破棄処理
	CModel::DestroyAllModels();
}

//更新処理
void CApplication::Update(void)
{
	//CDebugProc::Print("\nアローキーで視点の移動\nマウスで注視点の移動\nWASDキーでモデルの移動\n");

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Update();
		}
	}

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	if (m_pFade != nullptr)
	{
		//フェードが読み込まれていない場合
		if (m_pFade->GetFade() != CFade::FADE_NONE)
		{
			m_pFade->Update();
			ChangeMode();
		}
	}

	if (m_pMode != nullptr)
	{
		m_pMode->Update();
	}

	if (m_pMenu != nullptr)
	{
		m_pMenu->Update();
	}

	if (m_pMouse != nullptr)
	{
		m_pMouse->Update();
	}

	if (m_pPad != nullptr)
	{
		m_pPad->Update();
	}

	// ポーズ中でない場合のみ更新
	if (m_bPause == false)
	{
		if (m_pCamera != nullptr)
		{
			m_pCamera->Update();
		}
	}
}

//描画処理
void CApplication::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

CRenderer* CApplication::GetRenderer(void)
{
	return m_pRenderer;
}

CInputMouse* CApplication::GetMouse(void)
{
	return m_pMouse;
}

CInputPad * CApplication::GetPad(void)
{
	return m_pPad;
}

HWND CApplication::GetWindow(void)
{
	return m_hWnd;
}

//サウンドの取得処理
CSound* CApplication::GetSound(void)
{
	return m_pSound;
}

CCamera* CApplication::GetCamera(void)
{
	return m_pCamera;
}

CFade* CApplication::GetFade(void)
{
	return m_pFade;
}

//=====================================
// モード取得処理
//=====================================
CApplication::Mode CApplication::GetMode(void)
{
	return m_mode;
}

//=====================================
// モード設定処理
//=====================================
void CApplication::SetMode(Mode mode)
{
	// フェード切り替え状態ではない場合
	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		m_modeNext = mode;
		m_pFade->SetFade();
	}
}

//=====================================
// モード切り替え処理
//=====================================
void CApplication::ChangeMode()
{
	if (m_pFade->GetFade() != CFade::FADE_CHANGE)
	{// フェード切り替え状態じゃない場合
		return;
	}

	// 現在モードの終了
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	m_pMenu->Uninit();

	CObject::ReleaseAll();
	CHitbox::ReleaseAll();

	m_bPause = false;		// ポーズを未使用にする

	// 次のモードがステージ選択でなければ
	if (m_modeNext != Mode_StageSelect)
	{
		if (m_pSound != nullptr)
		{
			m_pSound->Stop();
		}
	}

	// モードを生成する
	switch (m_modeNext)
	{
	case CApplication::Mode_Title:
		m_pMode = CTitle::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		break;
	case CApplication::Mode_PlayerSelect:
		m_pMode = CPlayerSelect ::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_SELECT);
		break;
	case CApplication::Mode_StageSelect:
		m_pMode = CStageSelect::Create();
		break;
	case CApplication::Mode_Game_Race:
		m_pMode = CGameRace::Create();
		if (m_nStageSelect == 0)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME01);
		}
		else if (m_nStageSelect == 1)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME02);
		}
		else if (m_nStageSelect == 2)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME03);
		}
		break;
	case CApplication::Mode_Tutorial:
		m_pMode = CTutorial::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME01);
		break;
	default:
		break;
	}
	m_mode = m_modeNext;

	m_pMenu->Init();
}

//=====================================
// ポーズ取得処理
//=====================================
bool CApplication::GetPause()
{
	return m_bPause;
}

//=====================================
// ポーズ設定処理
//=====================================
void CApplication::SetPause(const bool bPause)
{
	m_bPause = bPause;
}