//=============================================================================
//
// menu.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "menu.h"
#include "Application.h"
#include "font.h"
#include "mode.h"
#include "choice.h"
#include "inputKeyboard.h"
#include "inputPad.h"

int CMenu::m_nNumAll = 0;
int CMenu::m_nSelectNum = 0;
CChoice* CMenu::m_pChoice[MaxChoice] = {};

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

		m_pChoice[m_nNumAll] = CChoice::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "スタート");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CChoice::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "おわり");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();
		break;
	case CApplication::Mode_Game_Race:
		break;
	case CApplication::Mode_Result:
		m_pChoice[m_nNumAll] = CChoice::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "リトライ");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CChoice::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "タイトルにもどる");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();
		break;
	case CApplication::Mode_Game_Debug:
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
		}
	}
	m_nSelectNum = 0;
	m_nNumAll = 0;
}

//=====================================
// 更新処理
//=====================================
void CMenu::Update(void)
{
	if (CApplication::GetMode() == CApplication::Mode_Title || CApplication::GetMode() == CApplication::Mode_Result)
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
				CApplication::SetMode(CApplication::Mode_Game_Race);
			}
			else if (m_nSelectNum == 1)
			{
				ExitExe();
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