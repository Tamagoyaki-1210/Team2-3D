//=============================================================================
//
// アプリケーション
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_ 

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <d3dx9.h>

//---------------------------
//前方宣言
//---------------------------
class CRenderer;
class CInput;
class CTexture;
class CMode;
class CFade;
//class CSound;
class CCamera;
class CLight;

//---------------------------
//クラス宣言
//---------------------------
class CApplication
{
public:
	CApplication();
	~CApplication();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	static CRenderer *GetRenderer() { return m_pRenderer; }	//レンダラー取得処理
	static CInput *GetInput() { return m_pInput; }			//入力取得処理
	static CTexture *GetTexture() { return m_pTexture; }	//画像取得処理
	static CMode *GetMode() { return m_pMode; }				//モード取得処理
	//static CSound *GetSound() { return m_pSound; }		//サウンド取得処理
	static CCamera *GetCamera() { return m_pCamera; }		//カメラ取得処理
	static CLight *GetLight() { return m_pLight; }			//カメラ取得処理
private:
	static CRenderer *m_pRenderer;
	static CInput *m_pInput;
	static CTexture *m_pTexture;
	static CMode *m_pMode;
	//static CSound *m_pSound;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
};

#endif // !_APPLICATION_H_
