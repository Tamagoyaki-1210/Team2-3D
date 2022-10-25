//=============================================================================
//
// application.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef APPLICATION_H
#define APPLICATION_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//前方宣言
class CRenderer;
class CInput;
class CInputMouse;
class CSound;
class CFade;
class CCamera;
class CDebugProc;
class CMode;

//アプリケーションのクラス
class CApplication
{
public:
	enum Mode
	{
		Mode_Title = 0,	//タイトル
		Mode_Game,		//ゲーム
		Mode_Result,	//リザルト
		Mode_Max
	};

	CApplication();										//コンストラクタ
	~CApplication();									//デストラクタ
														
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理
	static CRenderer* GetRenderer(void);				//レンディングインスタンスの取得処理
	static CInputMouse* GetMouse(void);					//マウスインスタンスの取得処理
	static HWND GetWindow(void);						//ウインドウの取得処理
	static CSound* GetSound(void);						//サウンドの取得処理
	static CCamera* GetCamera(void);					//カメラの取得処理

	static Mode GetMode(void);
	static void SetMode(Mode mode);

private:
	static HWND m_hWnd;									//クライエント画面
	static CRenderer* m_pRenderer;						//レンディングインスタンスへのポインタ
	static CInput* m_pInput[2];							//インプットデバイスへのポインタ
	static CInputMouse* m_pMouse;						//マウスインスタンス
	static CSound* m_pSound;							//サウンドのインスタンスへのポインタ
	static CFade* m_pFade;								//フェードのインスタンスへのポインタ
	static CCamera* m_pCamera;							//カメラのインスタンスへのポインタ
	static CMode* m_pMode;								//モードのインスタンスへのポインタ

	static CDebugProc* m_pDebug;						//

	static Mode m_mode;		//現在モード

	static bool m_bFade;								//フェード中であるかどうか
};

#endif // !APPLICATION_H
