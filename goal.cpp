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
	//����������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}
	m_bGoal = false;

	return S_OK;
}

//�I��
void CGoal::Uninit(void)
{
	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V
void CGoal::Update(void)
{
	//��{�N���X�̍X�V����
	CModel::Update();
}

//�`��
void CGoal::Draw(void)
{
	CModel::Draw();
}

void CGoal::SetGoal(bool bGoal,int nWinnerIdx)
{
	m_bGoal = bGoal;
	m_nWinnerIdx = nWinnerIdx;
}

//����
CGoal * CGoal::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X�𐶐�����
	CGoal* pGoal = new CGoal;		

	//�v���C���[�̏���������
	if (FAILED(pGoal->Init()))
	{
		return nullptr;
	}

	pGoal->SetModel(MODEL_GOAL);	//���f���̐ݒ菈��
	pGoal->SetPos(pos);				//�ʒu�̐ݒ菈��
	pGoal->SetShadowDraw(false);

	return pGoal;
}
