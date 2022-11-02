//=============================================================================
//
// message.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _MESSAGE_H
#define _MESSAGE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object2D.h"

//---------------------------
//クラス宣言
//---------------------------
class CMessage
{
public:
	CMessage();
	~CMessage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetCountDown(int nNum);
	void CountDown();
	void StartMessage(void);
	void GoalMessage(int nMessageIdx);

	static CMessage* Create();			//生成処理
	static bool GetStart(void) { return m_bStart; }

private:
	static const int CountDownLife = 60;
	static bool m_bStart;

	int m_nMessageCounter;		// メッセージ表示時間
	int m_nNum;					// カウントダウン現在位置
	bool m_bCountDown;
	bool m_bEndGame;
	CObject_2D* m_pObj2D;
};

#endif // !_MESSAGE_H
