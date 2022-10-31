//=============================================================================
//
// choice.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "choice.h"
#include "Application.h"

static const int ScaleSpeed = 4;		// ScaleSpeed / 10.0f

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CChoice::CChoice()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CChoice::~CChoice()
{

}

//=====================================
// ����������
//=====================================
HRESULT CChoice::Init(void)
{
	m_nNum = 0;
	m_fScale = 0.0f;
	m_bScale = false;
	m_bSellect = false;
	
	return S_OK;
}

//=====================================
// �I������
//=====================================
void CChoice::Uninit(void)
{

}

//=====================================
// �X�V����
//=====================================
void CChoice::Update(void)
{
	SizeScale();
}

//=====================================
// �T�C�Y�ύX����
//=====================================
void CChoice::SizeScale(void)
{
	// ���݂��̑I�������I������Ă���ꍇ
	if (m_bSellect == true)
	{
		if (m_bScale == false)
		{
			m_fScale += ScaleSpeed / 10.0f;
			if (m_fScale > 5.0f)
			{
				m_bScale = true;
			}
		}
		else
		{
			m_fScale -= ScaleSpeed / 10.0f;
			if (m_fScale < -5.0f)
			{
				m_bScale = false;
			}
		}

		for (int nCnt = 0; nCnt < m_nNum; nCnt++)
		{
			m_pFont[nCnt]->SetSize(D3DXVECTOR2(m_sizeYuan.x + m_fScale, m_sizeYuan.y + m_fScale));
		}
	}
}

//=====================================
// �T�C�Y���Z�b�g����
//=====================================
void CChoice::SizeReset(void)
{
	m_bSellect = false;
	m_fScale = 0.0f;
	m_bScale = false;
	for (int nCnt = 0; nCnt < m_nNum; nCnt++)
	{
		m_pFont[nCnt]->SetSize(D3DXVECTOR2(m_sizeYuan.x + m_fScale, m_sizeYuan.y + m_fScale));
	}
}

//=====================================
// �T�C�Y�ύX����
//=====================================
void CChoice::SetSellect(void)
{
	m_bSellect = true;
}

//=====================================
// ��������
//=====================================
CChoice* CChoice::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const std::string letter)
{
	CChoice* pChoice = new CChoice;
	
	if (FAILED(pChoice->Init()))
	{
		return nullptr;
	}

	// string�^�̕��������擾
	int nTex = strlen(letter.c_str());

	int nCnt = 0;
	for (int nLatter = 0; nLatter < nTex; nLatter += 2)
	{
		// ���݈ʒu����1�����i�ޏ���
		std::string sLatter = letter.substr(nLatter , 2);

		// �����𒆉��ɔz�u���Astring�^����*char�^��1���������o��
		pChoice->m_pFont[nCnt++] = CFont::Create(D3DXVECTOR3(pos.x + (nLatter * size.x) - (nTex * size.x / 2), pos.y, pos.z), size, sLatter.c_str());
		
		// �ŏ��̃T�C�Y��o�^����
		pChoice->m_sizeYuan = size;

		// �ԍ�������U��
		pChoice->m_nNum++;
	}

	return pChoice;
}