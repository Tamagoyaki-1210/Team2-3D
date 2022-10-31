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

	void GoalMessage(void);

	static CMessage* Create();			//生成処理

private:
	int m_nMessageCounter;			// メッセージ表示時間
	CObject_2D* m_pObj2D;
};

#endif // !_MESSAGE_H
