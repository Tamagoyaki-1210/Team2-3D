//=============================================================================
//
// palyerSelect.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _PLAYERSELECT_H_
#define _PLAYERSELECT_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"
#include "fontString.h"

//---------------------------
// 前方宣言
//---------------------------
class CFontString;
class CPlayerModel;
class CDirectionalLight;

//---------------------------
//クラス宣言
//---------------------------
class CPlayerSelect : public CMode
{
public:

	CPlayerSelect();
	~CPlayerSelect() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Input(void);

	static CPlayerSelect* Create(void);
	static int m_nPlayerCount;

private:
	static CFontString* m_pStr;			// 文字列
};

#endif // !_TITLE_H_
