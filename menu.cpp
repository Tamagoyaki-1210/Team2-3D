//=============================================================================
//
// menu.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "menu.h"
#include "Application.h"
#include "font.h"
#include <string>
#include <map>

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
	CChoice::Create();

	//CFont *pFont[2][20];
	//int nNumFont = 0;

	//// すたーと
	//std::string nStr[4] = { "す", "た", "ー", "と" };
	//for (int i = 0; i < 4; i++)
	//{
	//	pFont[nNumFont][i] = CFont::Create(D3DXVECTOR2(-500.0f, -50.0f), D3DXVECTOR2(30.0f, 30.0f), nStr[i], 5, i, 4);
	//}
	//nNumFont++;

	//// おわり
	//int nTex2[3] = { 4, 45, 41 };
	//for (int i = 0; i < 3; i++)
	//{
	//	pFont[nNumFont][i] = CFont::Create(D3DXVECTOR2(0.0f, 60.0f), D3DXVECTOR2(30.0f, 30.0f), nTex2[i], 5, i, 3);
	//}

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CMenu::Uninit(void)
{

}

//=====================================
// 更新処理
//=====================================
void CMenu::Update(void)
{

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