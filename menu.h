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
#include "fontString.h"

//---------------------------
// 前方宣言
//---------------------------
class CFontString;

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

	static void PauseChange(bool bPause);

	static CMenu* Create(void);
private:
	static const int MaxChoice = 10;			// 選択肢数

	static int m_nNumAll;						// 選択肢の全体数
	static int m_nSelectNum;					// 現在選択されている番号
	static CFontString* m_pChoice[MaxChoice];	// 選択肢文字列
	static CFontString* m_pPause;				// ポーズ文字列
	static CObject_2D* m_pObj2D;				// 半透明ポリゴン
};

#endif // !_MENU_H_
