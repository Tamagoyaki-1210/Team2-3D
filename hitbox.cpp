//=============================================================================
//
// hitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "hitbox.h"
#include "object.h"


std::vector <CHitbox*> CHitbox::m_vHitbox;

//コンストラクタ
CHitbox::CHitbox()
{
	m_pos = Vec3Null;
	m_RelativePos = Vec3Null;
	m_LastPos = Vec3Null;
	m_size = Vec3Null;
	m_rot = Vec3Null;
	m_shape = (HITBOX_SHAPE)0;
	m_type = (HITBOX_TYPE)0;
	m_bCollided = false;
	m_pParent = nullptr;

	m_vHitbox.push_back(this);
}

//デストラクタ
CHitbox::~CHitbox()
{

}

//初期化処理
HRESULT CHitbox::Init(void)
{
	m_pos = Vec3Null;
	m_LastPos = Vec3Null;
	m_RelativePos = Vec3Null;
	m_size = Vec3Null;
	m_rot = Vec3Null;
	m_shape = (HITBOX_SHAPE)0;
	m_type = (HITBOX_TYPE)0;
	m_bCollided = false;
	m_pParent = nullptr;

	return S_OK;
}

//終了処理
void CHitbox::Uninit(void)
{

}

//更新処理
void CHitbox::Update(void)
{
	m_LastPos = m_pos;

	if (m_pParent != nullptr)
	{
		D3DXVECTOR3 newPos = m_pParent->GetPos() + m_RelativePos;
		m_pos = newPos;
	}
}

//ヒットボックス1個の破棄処理
void CHitbox::Release(void)
{
	for (int nCnt = 0; nCnt < (int)m_vHitbox.size(); nCnt++)
	{
		if (m_vHitbox.data()[nCnt] == this)
		{
			m_vHitbox.data()[nCnt]->Uninit();
			m_vHitbox.erase(m_vHitbox.begin() + nCnt);
			delete this;
		}
	}
}

D3DXVECTOR3 CHitbox::GetPos(void)
{
	return m_pos;
}

D3DXVECTOR3 CHitbox::GetRelativePos(void)
{
	return m_RelativePos;
}

D3DXVECTOR3 CHitbox::GetLastPos(void)
{
	return m_LastPos;
}

D3DXVECTOR3 CHitbox::GetSize(void)
{
	return m_size;
}

D3DXVECTOR3 CHitbox::GetRot(void)
{
	return m_rot;
}

CHitbox::HITBOX_SHAPE CHitbox::GetShape(void)
{
	return m_shape;
}

CHitbox::HITBOX_TYPE CHitbox::GetType(void)
{
	return m_type;
}

CObject* CHitbox::GetParent(void)
{
	return m_pParent;
}


void CHitbox::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos + m_RelativePos;
}

void CHitbox::SetRelativePos(const D3DXVECTOR3 pos)
{
	m_RelativePos = pos;
}

void CHitbox::SetLastPos(const D3DXVECTOR3 pos)
{
	m_LastPos = pos;
}

void CHitbox::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
}

void CHitbox::SetShape(const HITBOX_SHAPE shape)
{
	m_shape = shape;
}

void CHitbox::SetType(const HITBOX_TYPE type)
{
	m_type = type;
}

void CHitbox::SetParent(CObject* pParent)
{
	m_pParent = pParent;
}

void CHitbox::SetCollisionState(bool bCollision)
{
	m_bCollided = bCollision;
}


bool CHitbox::GetCollisionState(void)
{
	return m_bCollided;
}







//ヒットボックス全部の破棄処理
void CHitbox::ReleaseAll(void)
{
	CHitbox* pHitbox = nullptr;

	for (int nCnt = 0; nCnt < (int)m_vHitbox.size(); nCnt++)
	{
		pHitbox = m_vHitbox.data()[nCnt];
		delete pHitbox;
		pHitbox = nullptr;
	}

	m_vHitbox.clear();
}

std::vector <CHitbox*>* CHitbox::GetAllHitbox(void)
{
	return &m_vHitbox;
}