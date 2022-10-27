//=============================================================================
//
// font.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _FONT_H
#define _FONT_H

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object2D.h"
#include <string>
#include <map>

//---------------------------
//�N���X�錾
//---------------------------
class CFont : public CObject_2D
{
public:
	CFont();
	CFont(const int nPriority);
	~CFont() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	static CFont* CFont::Create(const D3DXVECTOR2 addPos, const D3DXVECTOR2 size, const std::string str, const int nPriority, int nCnt, int nMax);

private:
	static std::map<std::string, int> m_hiraganaData;
};

#endif // !_FONT_H
