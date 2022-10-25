//=============================================================================
//
// title.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//---------------------------
//クラス宣言
//---------------------------
class CTitle : public CMode
{
public:
	CTitle();
	~CTitle() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static CTitle* Create(void);			//生成処理
private:
};

#endif // !_TITLE_H_
