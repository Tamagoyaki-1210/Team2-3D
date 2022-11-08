//=============================================================================
//
// warning.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _WARNING_H
#define _WARNING_H

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object2D.h"

//---------------------------
//クラス宣言
//---------------------------
class CWarning : public CObject_2D
{
public:
	enum WARNING
	{
		MESSAGE_FALLING_STONE = 0,
		MESSAGE_MAX
	};

	CWarning();
	CWarning(const int nPriority);
	~CWarning() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void BlinkColor(void);

	static CWarning* Create(const D3DXVECTOR3 pos);			//生成処理

private:
	int m_nLife;			// 寿命
	int m_nMaxBlink;	// 点滅回数
	bool m_bBlink;			// 点滅判定
};

#endif // !_FONT_H