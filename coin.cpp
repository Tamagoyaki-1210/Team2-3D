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
#include "meshfield.h"
#include "application.h"
#include "effect.h"
#include "camera.h"

const D3DXVECTOR3 CCoin::m_hitboxSize[COIN_MAX] =
{
	{15.0f, 20.0f, 15.0f},
	{15.0f, 20.0f, 15.0f},
	{15.0f, 20.0f, 15.0f},
	{15.0f, 20.0f, 15.0f},
	{15.0f, 20.0f, 15.0f}
};

//�R���X�g���N�^
CCoin::CCoin()
{
	m_move = Vec3Null;
	m_nLife = 0;
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

	m_move = Vec3Null;
	m_nLife = -1;

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
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN_GET);

			for (int nCnt = 0; nCnt < 50; nCnt++)
			{
				CEffect::Create(GetPos(), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * ((float)CObject::random(-100, 100) * 0.001f)), D3DXVECTOR3((float)CObject::random(-50, 50) * 0.05f, (float)CObject::random(-50, 50) * 0.05f, (float)CObject::random(-50, 50) * 0.05f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.25f), D3DXCOLOR(-0.005f, -0.005f, 0.001f, 0.0f), 1.0f, -0.03f, 30);
			
			}

			return;
		}
	}

	if (m_nLife > 0)
	{
		m_nLife--;

		if (m_nLife <= 0)
		{
			m_pHitbox->Release();		//�q�b�g�{�b�N�X������
			Release();					//�R�C��������
			return;
		}
	}

	if (D3DXVec3Length(&m_move) > 0.0f)
	{
		if (m_move.y >= -10.0f)
		{
			m_move.y += -0.7f;
		}

		D3DXVECTOR3 newPos = GetPos() + m_move;
		SetPos(newPos);
		m_pHitbox->SetPos(newPos);

		m_move.x += (0.0f - m_move.x) * 0.05f;
		m_move.z += (0.0f - m_move.z) * 0.05f;

		CMeshfield::FieldInteraction(this);
	}

	if (GetPos().z < CApplication::GetCamera()->GetPos().z - 100.0f)
	{
		Release();
	}
}

//�`�揈��
void CCoin::Draw(void)
{
	if (GetPos().z < CApplication::GetCamera()->GetPos().z + 650.0f)
	{
		if ((m_nLife % 30) <= 15)
		{
			CModel::Draw();
		}
	}
}

void CCoin::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

const D3DXVECTOR3 CCoin::GetMove(void)
{
	return m_move;
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

	pCoin->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, m_hitboxSize[type], CHitbox::TYPE_VANISHING, pCoin, 10);		//�q�b�g�{�b�N�X�𐶐�����

	return pCoin;				//���������C���X�^���X��Ԃ�

}

CCoin* CCoin::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const int nLife, const COIN_TYPE type)
{
	CCoin* pCoin = new CCoin;			//�R�C���𐶐�����

	if (FAILED(pCoin->Init()))
	{//����������
		return nullptr;
	}

	int nType = (int)CModel::MODEL_COIN_0 + (int)type;					//���f���ԍ����v�Z����

	pCoin->SetModel((CModel::ModelType)nType);							//���f���̐ݒ菈��
	pCoin->SetPos(pos);													//�ʒu�̐ݒ菈��
	pCoin->m_move = move;												//�ړ��ʂ̐ݒ菈��
	pCoin->StartRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.01f, 0.0f));		//��]���x�̐ݒ�
	pCoin->m_nLife = nLife;												//���C�t�̐ݒ�

	pCoin->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, m_hitboxSize[type], CHitbox::TYPE_VANISHING, pCoin, 10);		//�q�b�g�{�b�N�X�𐶐�����

	return pCoin;				//���������C���X�^���X��Ԃ�
}