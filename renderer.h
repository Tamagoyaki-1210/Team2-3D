//=============================================================================
//
// �����_���[
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <d3dx9.h>

//---------------------------
//�O���錾
//---------------------------
#ifdef _DEBUG
class CDebugProc;
#endif // _DEBUG

//�����_���[�N���X
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

	LPDIRECT3D9 m_pD3D;	// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Device�I�u�W�F�N�g
	LPD3DXFONT m_pFont;
#ifdef _DEBUG
	static CDebugProc *m_pDebugProc;
#endif // _DEBUG
};

#endif // !1
