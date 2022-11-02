//=============================================================================
//
// hitbox.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef CYLINDER_HITBOX_H
#define CYLINDER_HITBOX_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "hitbox.h"

class CLine;

class CCylinderHitbox : public CHitbox
{
public:
	CCylinderHitbox();
	~CCylinderHitbox() override;

	HRESULT Init(void) override;
	void    Uninit(void) override;
	void    Update(void) override;

	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent);
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nPlayerIdx);
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent);
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent, CHitbox::INTERACTION_EFFECT effect);

private:

	bool CylinderCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	bool CylinderBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);
	bool PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);

	CLine* m_pLine[18];

};


#endif