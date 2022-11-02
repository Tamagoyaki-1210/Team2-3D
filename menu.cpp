//=============================================================================
//
// menu.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "menu.h"
#include "Application.h"
#include "mode.h"
#include "fontString.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "game.h"
#include "fade.h"

int CMenu::m_nNumAll = 0;
int CMenu::m_nSelectNum = 0;
CFontString* CMenu::m_pChoice[MaxChoice] = {};
CFontString* CMenu::m_pPause = nullptr;
CObject_2D* CMenu::m_pObj2D = nullptr;

//-----------------------------------------
//プロトタイプ宣言
//-----------------------------------------
void ExitExe(void);

//=====================================
// デフォルトコンストラクタ
//=====================================
CMenu::CMenu()
{

}

//=====================================
// デストラクタ
//=====================================
CMenu::~CMenu()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CMenu::Init(void)
{
	switch (CApplication::GetMode())
	{
	case CApplication::Mode_Title :

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "スタート");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "おわり");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();
		break;
	case CApplication::Mode_Game_Race:
		break;
	case CApplication::Mode_Result:
		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "リトライ");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "タイトルにもどる");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();
		break;
	default:
		break;
	}

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CMenu::Uninit(void)
{
	for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
	{
		if (m_pChoice[nCnt] != nullptr)
		{
			m_pChoice[nCnt]->Uninit();
			m_pChoice[nCnt] = nullptr;
		}
	}

	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		m_pPause = nullptr;
	}

	if (m_pObj2D != nullptr)
	{
		m_pObj2D->Release();
		m_pObj2D = nullptr;
	}

	m_nSelectNum = 0;
	m_nNumAll = 0;
}

//=====================================
// 更新処理
//=====================================
void CMenu::Update(void)
{
	if (CApplication::GetMode() == CApplication::Mode_Game_Race)
	{
		// ポーズ中でない場合のみ更新
		if (CApplication::GetPause() == true)
		{
			for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
			{
				if (m_pChoice[nCnt] != nullptr)
				{
					m_pChoice[nCnt]->Update();
				}
			}
			Input();
		}
	}
	else
	{
		for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
		{
			if (m_pChoice[nCnt] != nullptr)
			{
				m_pChoice[nCnt]->Update();
			}
		}
		Input();
	}
}

//=====================================
// 入力処理
//=====================================
void CMenu::Input(void)
{
	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_W) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).y < -0.3f)
		{// Wキーが押された場合
			m_pChoice[m_nSelectNum]->SizeReset();
			m_nSelectNum--;

			// 現在位置が0より下の場合
			if (m_nSelectNum < 0)
			{
				m_nSelectNum = m_nNumAll - 1;
			}
			m_pChoice[m_nSelectNum]->SetSellect();
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_S) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).y > 0.3f)
		{// Sキーが押された場合
			m_pChoice[m_nSelectNum]->SizeReset();
			m_nSelectNum++;

			// 現在位置が最大数より大きい場合
			if (m_nSelectNum >= m_nNumAll)
			{
				m_nSelectNum = 0;
			}
			m_pChoice[m_nSelectNum]->SetSellect();
		}
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
		{
			switch (CApplication::GetMode())
			{
			case CApplication::Mode_Title:

				if (m_nSelectNum == 0)
				{
					CApplication::SetMode(CApplication::Mode_PlayerSelect);
				}
				else if (m_nSelectNum == 1)
				{
					ExitExe();
				}
				break;
			case CApplication::Mode_Game_Race:
				if (m_nSelectNum == 0)
				{
					CApplication::SetPause(false);
					PauseChange(false);
				}
				else if (m_nSelectNum == 1)
				{
					CApplication::SetMode(CApplication::Mode_Game_Race);
				}
				else if (m_nSelectNum == 2)
				{
					CApplication::SetMode(CApplication::Mode_Title);
				}
				break;
			case CApplication::Mode_Result:
				if (m_nSelectNum == 0)
				{
					CApplication::SetMode(CApplication::Mode_Game_Race);
				}
				else if (m_nSelectNum == 1)
				{
					CApplication::SetMode(CApplication::Mode_Title);
				}
				break;
			default:
				break;
			}
		}
	}
}

//=====================================
// ポーズ選択肢処理
//=====================================
void CMenu::PauseChange(bool bPause)
{
	if (bPause == true)
	{
		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "つづける");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "やりなおす");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "タイトルにもどる");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();

		m_pPause = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), "ポーズ");

		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		m_pObj2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.1f));
		m_pObj2D->SetTexture(CObject::TEXTURE_NULL);
		m_pObj2D->SetPriority(4);
	}
	else
	{
		for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
		{
			if (m_pChoice[nCnt] != nullptr)
			{
				m_pChoice[nCnt]->Uninit();
				m_pChoice[nCnt] = nullptr;
			}
		}

		if (m_pPause != nullptr)
		{
			m_pPause->Uninit();
			m_pPause = nullptr;
		}

		if (m_pObj2D != nullptr)
		{
			m_pObj2D->Release();
			m_pObj2D = nullptr;
		}

		m_nSelectNum = 0;
		m_nNumAll = 0;
	}
}

//=====================================
// 生成処理
//=====================================
CMenu* CMenu::Create(void)
{
	CMenu* pMenu = new CMenu;

	if (FAILED(pMenu->Init()))
	{
		return nullptr;
	}

	return pMenu;
}