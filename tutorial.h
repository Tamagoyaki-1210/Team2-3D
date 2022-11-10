//=============================================================================
//
// tutorial.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "mode.h"

//---------------------------
//前方宣言
//---------------------------
class CMeshfield;
class CPlayer;
class CObject_2D;

//---------------------------
//クラス宣言
//---------------------------
class CTutorial : public CMode
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static void SetEndTutorial();			// ゲーム終了を設定する
	static bool GetEndTutorial() { return m_bEndTutorial; };

	static CMeshfield* GetField(void) { return m_pField; };			// メッシュフィールドの取得処理
	static CPlayer* GetPlayer(int nCnt) { return m_pPlayer[nCnt]; };	// プレイヤーの取得処理

	static CTutorial* Create(void);			//生成処理
private:

	void SetObject(void);

	static CMeshfield* m_pField;
	static CPlayer* m_pPlayer[PLAYER_MAX];					//プレイヤーのインスタンスへのポインタ

	static bool m_bEndTutorial;

	CObject_2D* m_pUi;
	bool m_bChange;
};

#endif // !_GAME_H_
