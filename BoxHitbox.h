//=============================================================================
//
// BoxHitbox.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BOX_HITBOX_H
#define BOX_HITBOX_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "hitbox.h"

class CLine;

class CBoxHitbox : public CHitbox
{
public:
	CBoxHitbox();
	~CBoxHitbox() override;

	HRESULT Init(void) override;
	void    Uninit(void) override;
	void    Update(void) override;

	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent);
	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore);
	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore, INTERACTION_EFFECT effect);

private:

	bool BoxBoxHit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	CLine* m_pLine[12];
};


#endif