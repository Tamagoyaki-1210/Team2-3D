//=============================================================================
//
// trampoline.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "trampoline.h"
#include "CylinderHitbox.h"

//�R���X�g���N�^
CTrampoline::CTrampoline()
{
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CTrampoline::~CTrampoline()
{

}

//����������
HRESULT CTrampoline::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CTrampoline::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CModel::Uninit();
}

//�X�V����
void CTrampoline::Update(void)
{
	CModel::Update();
}




//��������
CTrampoline* CTrampoline::Create(const D3DXVECTOR3 pos)
{
	CTrampoline* pModel = new CTrampoline;

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->SetModel(CModel::MODEL_HEAD);
	pModel->SetPos(pos);
	pModel->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(20.0f, 2.0f, 20.0f), CHitbox::TYPE_OBSTACLE, 0, nullptr, CHitbox::EFFECT_JUMP);

	return pModel;
}