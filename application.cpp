//=============================================================================
//
// application.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "application.h"
#include "rendering.h"
#include "object.h"
#include "object2D.h"
#include "input.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "sound.h"
#include "directionalLight.h"
#include "camera.h"
#include "model.h"
#include "debugProc.h"
#include "object2D.h"
//#include "Letter.h"
#include "animator.h"
#include "title.h"
#include "gamedebug.h"
#include "gamerace.h"
#include "result.h"

//静的メンバー変数の宣言
HWND CApplication::m_hWnd;
CRenderer* CApplication::m_pRenderer = nullptr;			//レンディングインスタンスへのポインタ
CInput* CApplication::m_pInput[2] = {};					//インプットインスタンスへのポインタ
CInputMouse* CApplication::m_pMouse = nullptr;			//マウスインスタンスへのポインタ
CSound* CApplication::m_pSound = nullptr;
CFade* CApplication::m_pFade = nullptr;
CCamera* CApplication::m_pCamera = nullptr;
bool CApplication::m_bFade = false;
CMode *CApplication::m_pMode = nullptr;					// モードへのポインタ
CDebugProc* CApplication::m_pDebug = nullptr;
CApplication::Mode CApplication::m_mode = CApplication::Mode_Title;

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

	// モードインスタンスの生成処理
	m_pMode = CGameRace::Create();

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

	//キーボードの初期化処理
	/*if (FAILED(m_pMouse->Init(hInstance, hWnd, GUID_SysMouse)))
	{
		return -1;
	}*/

	m_pSound = CSound::Create(hWnd);

	/*if (m_pSound != nullptr)
	{
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
	}*/

	//m_pFade = CFade::Create();
	m_bFade = false;

	CLight::ReleaseAll();
	CDirectionalLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(2, -5, 2));

	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, -200.0f, 300.0f));

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

	return S_OK;
}

//終了処理
void CApplication::Uninit(void)
{
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

	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
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
	CDebugProc::Print("\nアローキーで視点の移動\nマウスで注視点の移動\nWASDキーでモデルの移動\n");

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

	if (m_pMode != nullptr)
	{
		m_pMode->Update();
	}

	if (m_pMouse != nullptr)
	{
		m_pMouse->Update();
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	/*if (CInputKeyboard::GetKeyboardTrigger(DIK_C))
	{
		CObject_2D* pObj2D = CObject_2D::Create();
		pObj2D->SetPos(D3DXVECTOR3((float)CObject::random(50, SCREEN_WIDTH - 50), (float)CObject::random(50, SCREEN_HEIGHT - 50), 0.0f));
		pObj2D->SetSize(D3DXVECTOR2(50.0f, 50.0f));
		pObj2D->SetTexture(CObject::TEXTURE_LETTERS);
		pObj2D->SetTextureParameter(1, 13, 2, INT_MAX);
		pObj2D->SetAnimPattern(CObject::random(0, 25));
		pObj2D->SetPriority(5);
	}
	if (CInputKeyboard::GetKeyboardTrigger(DIK_X))
	{
		CObject::DebugDestroy();
	}

	if (m_pStr != nullptr)
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_Z))
		{
			m_pStr->Release();
			m_pStr = nullptr;
		}
	}*/
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
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	CObject::ReleaseAll();

	if (m_pSound != nullptr)
	{
		m_pSound->Stop();
	}

	switch (mode)
	{
	case CApplication::Mode_Title:
		m_pMode = CTitle::Create();
		break;
	case CApplication::Mode_Game_Race:
		m_pMode = CGameRace::Create();
		break;
	case CApplication::Mode_Result:
		m_pMode = CResult::Create();
		break;
	case CApplication::Mode_Game_Debug:
		m_pMode = CGameDebug::Create();
		break;
	default:
		break;
	}
	m_mode = mode;
}