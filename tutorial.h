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
class CStage;

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
	static bool GetEndTutorial() { return m_bEndTutorial; }

	static CStage* GetStage(void) { return m_pStage; }

	static CTutorial* Create(void);			//生成処理
private:
	static CStage* m_pStage;
	static bool m_bEndTutorial;
};

#endif // !_GAME_H_
