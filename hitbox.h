//=============================================================================
//
// hitbox.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HITBOX_H
#define HITBOX_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "object3D.h"
#include <vector>

//=============================================================================
//インクルードファイル
//=============================================================================
class CObject;

class CHitbox
{
public:

	enum HITBOX_SHAPE
	{
		SHAPE_SPHERE = 0,
		SHAPE_BOX,
		SHAPE_CYLINDER,

		SHAPE_MAX
	};

	enum HITBOX_TYPE
	{
		TYPE_PLAYER = 0,
		TYPE_OBSTACLE,
		TYPE_NEUTRAL,
		TYPE_VANISHING,

		TYPE_MAX
	};

	enum INTERACTION_EFFECT
	{
		EFFECT_DAMAGE = 0,
		EFFECT_LAUNCH,

		EFFECT_MAX
	};

	CHitbox();							//コンストラクタ
	virtual ~CHitbox();					//デストラクタ

	virtual HRESULT Init(void);
	virtual void    Uninit(void);
	virtual void    Update(void);

	void Release(void);

	D3DXVECTOR3  GetPos(void);
	D3DXVECTOR3  GetRelativePos(void);
	D3DXVECTOR3  GetLastPos(void);
	D3DXVECTOR3  GetSize(void);
	D3DXVECTOR3  GetRot(void);
	HITBOX_SHAPE GetShape(void);
	HITBOX_TYPE  GetType(void);
	CObject*	 GetParent(void);
	INTERACTION_EFFECT GetEffect(void);

	void SetPos(const D3DXVECTOR3 pos);
	void SetRelativePos(const D3DXVECTOR3 pos);
	void SetLastPos(const D3DXVECTOR3 pos);
	void SetSize(const D3DXVECTOR3 size);
	void SetShape(const HITBOX_SHAPE shape);
	void SetType(const HITBOX_TYPE type);
	void SetParent(CObject* pParent);
	void SetCollisionState(bool bCollision);
	void SetPlayerIdx(const int nPlayerIdx);
	void SetScore(const int nScore);
	void SetEffect(INTERACTION_EFFECT effect);
	void SetInvincibility(const bool bInv);

	bool GetCollisionState(void);
	const int GetPlayerIdx(void);
	const int GetScore(void);
	const bool GetInvincibility(void);

	static void ReleaseAll(void);
	static std::vector <CHitbox*>* GetAllHitbox(void);

private:

	D3DXVECTOR3  m_pos;
	D3DXVECTOR3  m_RelativePos;
	D3DXVECTOR3  m_LastPos;
	D3DXVECTOR3  m_size;
	D3DXVECTOR3  m_rot;
	HITBOX_SHAPE m_shape;
	HITBOX_TYPE  m_type;
	INTERACTION_EFFECT m_effect;
	bool		 m_bCollided;
	CObject*	 m_pParent;
	int			 m_nPlayerIdx;
	int			 m_nScore;
	bool		 m_bInvincible;

	static std::vector <CHitbox*> m_vHitbox;
};



#endif
#pragma once