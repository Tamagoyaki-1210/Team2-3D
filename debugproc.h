//============================================================================
//
//
// デバッグ用
// Author:谷本康輔
//
//============================================================================
#ifndef _DEBUGPROC_H_						//このマクロ定義がされてなかったら
#define _DEBUGPROC_H_						//2連インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//****************************************************************************
//マクロ定義
//****************************************************************************
#define MAX_STR		(1024)		//ビルボードの最大設置数
#define MAX_LEN		(20)		//最大行数

class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void Init();
	void Uninit();

	static void Print(const char *format, ...);
	static void Draw();

	//static CDebugProc *Create(D3DXVECTOR3 pos);
private:
	static LPD3DXFONT m_pFont;
	static char m_aStr[MAX_STR];
	static int m_nLen[MAX_LEN];
};
#endif //!_DEBUGPROC_H_