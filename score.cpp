//=============================================================================
//
// score.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "score.h"


std::vector <CScore*> CScore::m_vScore;

//�R���X�g���N�^
CScore::CScore()
{
	//�����o�[�ϐ����N���A����
	m_nScore = 0;
	m_nPlayerIdx = 0;
}

//�f�X�g���N�^
CScore::~CScore()
{

}

//����������
HRESULT CScore::Init(void)
{
	//����������
	m_nScore = 0;
	m_nPlayerIdx = -1;

	return S_OK;
}

//�I������
void CScore::Uninit(void)
{

}

//�X�R�A�𑫂�����
void CScore::AddScore(const int nScore)
{
	m_nScore += nScore;
}







//�X�R�A�𑫂�����
void CScore::AddScore(const int nPlayerIdx, const int nScore)
{
	m_vScore.data()[nPlayerIdx]->AddScore(nScore);
}


//�N���A����
void CScore::Clear(void)
{
	for (int nCnt = 0; nCnt < (int)m_vScore.size(); nCnt++)
	{
		m_vScore.data()[nCnt]->Uninit();
		delete m_vScore.data()[nCnt];
		m_vScore.data()[nCnt] = nullptr;
	}

	m_vScore.clear();
}

//��������
CScore* CScore::Create(const int nPlayerIdx)
{
	CScore* pScore = new CScore;

	if (FAILED(pScore->Init()))
	{
		return nullptr;
	}

	pScore->m_nScore = 0;
	pScore->m_nPlayerIdx = nPlayerIdx;
	
	return pScore;
}