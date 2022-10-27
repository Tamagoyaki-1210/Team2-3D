//=============================================================================
//
// choice.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _CHOICE_H_
#define _CHOICE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "font.h"

//---------------------------
//クラス宣言
//---------------------------
class CChoice
{
public:
	enum Choice
	{
		Choice_Start = 0,	//すたーと
		Choice_Finish,		//おわり
		Choice_Max
	};
	CChoice();
	~CChoice();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CChoice* Create(void);			//生成処理
private:
	static const int MaxWordLenght = 24;

	CFont* m_pFont[MaxWordLenght];
	Choice* m_choice;
};

#endif // !_CHOICE_H_
