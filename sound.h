//=============================================================================
// 
// サウンド
// Author : Tanimoto Kosuke
// 
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "xaudio2.h"	// 音楽処理に必要

// *****************************************************************************
// サウンドファイル
// *****************************************************************************
enum Sound_Label
{
	SOUND_LABEL_BGM_TITLE = 0,		// BGMタイトル
	SOUND_LABEL_BGM_STAGE1,
	SOUND_LABEL_SE_JUMP,
	SOUND_LABEL_MAX,
};

class CSound
{
public:
	//*****************************************************************************
	// パラメータ構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit();
	static HRESULT PlaySound(Sound_Label label);
	static void StopSound(Sound_Label label);
	static void StopSound(void);

private:
	static IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// オーディオデータサイズ

	// 各音素材のパラメータ
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};

#endif
