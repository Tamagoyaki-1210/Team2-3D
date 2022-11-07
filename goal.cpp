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
#include "gamerace.h"
#include "stage.h"

bool CGoal::m_bGoal = false;									//�S�[���������ǂ���
int CGoal::m_nWinnerIdx = 0;

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

void CGoal::SetGoal(bool bGoal,int nWinnerIdx)
{
	m_bGoal = bGoal;
	m_nWinnerIdx = nWinnerIdx;
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
