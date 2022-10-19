//============================================================================
//
// デバッグ用
// Author:谷本康輔
//
//============================================================================
#include "debugproc.h"
#include "application.h"
#include "renderer.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifdef _DEBUG
#include <tchar.h> // _T
#endif // _DEBUG

#define TEXT_WIDTH			(10)		//テキストの横幅
#define TEXT_HEIGHT			(24)		//テキストの高さ

LPD3DXFONT CDebugProc::m_pFont = nullptr;
char CDebugProc::m_aStr[MAX_STR] = {};
int CDebugProc::m_nLen[MAX_LEN] = {};
//=====================================
// デフォルトコンストラクタ
//=====================================
CDebugProc::CDebugProc()
{

}

//=====================================
// デストラクタ
//=====================================
CDebugProc::~CDebugProc()
{

}

//============================================================================
//デバッグ用初期化処理
//============================================================================
void CDebugProc::Init()
{
#ifdef _DEBUG
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

									// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);

	//for (int nLen = 0; nLen < MAX_LEN; nLen++)
	//{
	//	m_nLen[nLen] = 0;
	//}
#endif
}

//============================================================================
//デバッグ用終了処理
//============================================================================
void CDebugProc::Uninit()
{
#ifdef _DEBUG
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG
}

//============================================================================
//文字力処理
//============================================================================
void CDebugProc::Print(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vsprintf(m_aStr, format, args);
	va_end(args);

	//char aStr[100] = {};

	//for (int i = 0; pFormat[i] != '\0'; ++i) {
	//	printf("%c:", pFormat[i]);
	//	switch (pFormat[i]) {
	//	case 'd':
	//		aStr[0] = pFormat[i];
	//		break;
	//	case 'f':
	//		aStr[0] = pFormat[i];
	//		break;
	//	case 'c':
	//		aStr[0] = pFormat[i];
	//		break;
	//	case 's':
	//		aStr[0] = pFormat[i];
	//		break;
	//	default:
	//		break;
	//	}
	//}

	//strcat(m_aStr, aStr);

	//for (int nLen = 0; nLen < MAX_LEN; nLen++)
	//{
	//	for (int i = m_nLen[nLen]; pFormat[m_nLen[nLen] + i] != '\0'; ++i) {
	//		printf("%c:", pFormat[i]);
	//		switch (m_aStr[i]) {
	//		case 'd':
	//			sprintf(&m_aStr[m_nLen[nLen]], "%d", va_arg(args, int));
	//			break;
	//		case 'f':
	//			sprintf(&m_aStr[m_nLen[nLen]], "%f", va_arg(args, float));
	//			break;
	//		case 'c':
	//			sprintf(&m_aStr[m_nLen[nLen]], "%c", va_arg(args, char));
	//			break;
	//		case 's':
	//			sprintf(&m_aStr[m_nLen[nLen]], "%s", va_arg(args, char*));
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//	m_nLen[nLen] = strlen(m_aStr);
	//}
	//va_end(args);
}

//============================================================================
//デバッグ用初期化処理
//============================================================================
void CDebugProc::Draw()
{
#ifdef _DEBUG	
	//sprintf(&m_aStr[0], "<ゲーム時間経過フレーム>\n");
	//sprintf(&m_aStr[1], "[] : f経過\n");

		//テキスト位置
	RECT rc = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	if (m_pFont != nullptr)
	{
		// テキスト描画
		m_pFont->DrawText(NULL,	&m_aStr[0],	-1,	&rc, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		m_aStr[0] = '\0';
	}
#endif // _DEBUG
}