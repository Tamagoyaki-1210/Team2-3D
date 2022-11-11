//=============================================================================
//
// fontString.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _FONTSTRING_H_
#define _FONTSTRING_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "font.h"

//---------------------------
//クラス宣言
//---------------------------
class CFontString
{
public:
	CFontString();
	~CFontString();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SizeScale(void);

	void SizeReset(void);
	void SetSellect(void);
	void SetColor(D3DXCOLOR col);

	static CFontString* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const std::string letter);
private:
	static const int MaxWordLenght = 24;

	int m_nNum;
	float m_fScale;
	bool m_bScale;
	bool m_bSellect;
	D3DXVECTOR2 m_sizeYuan;		
	CFont* m_pFont[MaxWordLenght];
};

#endif // !_FONTSTRING_H_
