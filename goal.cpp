//=============================================================================
//
// goal.cpp
// Author : Kajita Hiromu
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "application.h"
#include "goal.h"
#include "rendering.h"
#include "message.h"
#include "gamerace.h"

bool CGoal::m_bGoal = false;									//�S�[���������ǂ���

//�R���X�g���N�^
CGoal::CGoal()
{
}

//�f�X�g���N�^
CGoal::~CGoal()
{
}

//������
HRESULT CGoal::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bGoal = false;

	return S_OK;
}

//�I��
void CGoal::Uninit(void)
{
}

//�X�V
void CGoal::Update(void)
{
	m_bGoal = GetGoal();

	if (m_bGoal)
	{
		CGameRace::Get()->GoalMessage();
	}
}

//�`��
void CGoal::Draw(void)
{
}

//�ʒu
void CGoal::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�T�C�Y�̏��
const D3DXVECTOR2 CGoal::GetSize(void)
{
	return (D3DXVECTOR2)m_size;
}

//�ʒu�̏��
const D3DXVECTOR3 CGoal::GetPos(void)
{
	return m_pos;
}

void CGoal::SetGoal(bool bGoal)
{
	m_bGoal = bGoal;
}

bool CGoal::GetGoal()
{
	return m_bGoal;
}

//����
CGoal * CGoal::Create()
{
	//�C���X�^���X�𐶐�����
	CGoal* pGoal = new CGoal;		

	//�v���C���[�̏���������
	if (FAILED(pGoal->Init()))
	{
		return nullptr;
	}

	return pGoal;
}
