//=============================================================================
//
// レンダラー
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <d3dx9.h>

//---------------------------
//前方宣言
//---------------------------
#ifdef _DEBUG
class CDebugProc;
#endif // _DEBUG

//レンダラークラス
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	LPDIRECT3DDEVICE9 GetDevice();
#ifdef _DEBUG
	static CDebugProc *GetDebugProc() { return m_pDebugProc; }
#endif // _DEBUG

private:
	void DrawFPS();

	LPDIRECT3D9 m_pD3D;	// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Deviceオブジェクト
	LPD3DXFONT m_pFont;
#ifdef _DEBUG
	static CDebugProc *m_pDebugProc;
#endif // _DEBUG
};

#endif // !1
