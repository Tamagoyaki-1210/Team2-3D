//=============================================================================
//
// coin.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "coin.h"
#include "BoxHitbox.h"

const D3DXVECTOR3 CCoin::m_hitboxSize[COIN_MAX] =
{
	{10.0f, 20.0f, 10.0f},
	{10.0f, 20.0f, 10.0f},
	{10.0f, 20.0f, 10.0f},
	{10.0f, 20.0f, 10.0f}
};

//�R���X�g���N�^
CCoin::CCoin()
{
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CCoin::~CCoin()
{

}

//����������
HRESULT CCoin::Init(void)
{
	//����������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CCoin::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CCoin::Update(void)
{
	//��{�N���X�̍X�V����
	CModel::Update();

	if (m_pHitbox != nullptr)
	{//�����蔻�肪null�ł͂Ȃ�������
		if (m_pHitbox->GetCollisionState())
		{//�����Ɠ��������ꍇ
			m_pHitbox->Release();		//�q�b�g�{�b�N�X������
			Release();					//�R�C��������
		}
	}
}




//��������
CCoin* CCoin::Create(const D3DXVECTOR3 pos, const COIN_TYPE type)
{
	CCoin* pCoin = new CCoin;			//�R�C���𐶐�����

	if (FAILED(pCoin->Init()))
	{//����������
		return nullptr;
	}

	int nType = (int)CModel::MODEL_COIN_0 + (int)type;					//���f���ԍ����v�Z����

	pCoin->SetModel((CModel::ModelType)nType);							//���f���̐ݒ菈��
	pCoin->SetPos(pos);													//�ʒu�̐ݒ菈��
	pCoin->StartRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.01f, 0.0f));		//��]���x�̐ݒ�

	pCoin->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, m_hitboxSize[type], CHitbox::TYPE_NEUTRAL, pCoin, 10);		//�q�b�g�{�b�N�X�𐶐�����

	return pCoin;				//���������C���X�^���X��Ԃ�

}