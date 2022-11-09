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

//=============================================================================
//前方宣言
//=============================================================================
class CPlayerModel;
class CAnimateUI;

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

	static CTitle* Create(void);
private:

	static const int MAX_TITLE_MODEL = 7;

	CPlayerModel* m_pModel[MAX_TITLE_MODEL];
	CAnimateUI*   m_pTitle;

};

#endif // !_TITLE_H_
