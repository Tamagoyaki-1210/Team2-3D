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
	// メッセージ種類
	enum MESSAGE
	{
		MESSAGE_COUNTDOWN = 0,
		MESSAGE_START,
		MESSAGE_GOAL,
		MESSAGE_WIN,
		MESSAGE_MAX
	};
	CMessage();
	~CMessage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetCountDown(int nNum);
	void StartMessage(void);
	void GoalMessage(int nMessageIdx);
	void WinMessage();

	void Destroy();

	static CMessage* Create();			//生成処理
	static bool GetStart(void) { return m_bStart; }

private:
	static const int CountDownLife = 60;
	static bool m_bStart;

	int m_nMessageIdx;
	int m_nMessageCounter;		// メッセージ表示時間
	int m_nNum;					// カウントダウン現在位置
	CObject_2D* m_pObj2D;
	MESSAGE m_type;
};

#endif // !_MESSAGE_H
