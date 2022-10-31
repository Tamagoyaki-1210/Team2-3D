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
	CChoice();
	~CChoice();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SizeScale(void);

	void SizeReset(void);
	void SetSellect(void);

	static CChoice* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const std::string letter);
private:
	static const int MaxWordLenght = 24;

	int m_nNum;
	float m_fScale;
	bool m_bScale;
	bool m_bSellect;
	D3DXVECTOR2 m_sizeYuan;		
	CFont* m_pFont[MaxWordLenght];
};

#endif // !_CHOICE_H_
