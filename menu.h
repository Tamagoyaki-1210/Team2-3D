//=============================================================================
//
// menu.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _MENU_H_
#define _MENU_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "choice.h"

//---------------------------
// 前方宣言
//---------------------------
class CChoice;

//---------------------------
//クラス宣言
//---------------------------
class CMenu
{
public:
	CMenu();
	~CMenu();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Input(void);

	static CMenu* Create(void);
private:
	static const int MaxChoice = 10;			// 選択肢数

	static int m_nNumAll;						// 選択肢の全体数
	static int m_nSelectNum;					// 現在選択されている番号
	static CChoice* m_pChoice[MaxChoice];
};

#endif // !_MENU_H_
