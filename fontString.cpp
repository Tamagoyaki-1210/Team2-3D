//=============================================================================
//
// fontString.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "fontString.h"
#include "Application.h"

static const int ScaleSpeed = 4;		// ScaleSpeed / 10.0f

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CFontString::CFontString()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CFontString::~CFontString()
{

}

//=====================================
// ����������
//=====================================
HRESULT CFontString::Init(void)
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
void CFontString::Uninit(void)
{
	for (int nCnt = 0; nCnt < MaxWordLenght; nCnt++)
	{
		if (m_pFont[nCnt] != nullptr)
		{
			m_pFont[nCnt]->Release();
			m_pFont[nCnt] = nullptr;
		}
	}
}

//=====================================
// �X�V����
//=====================================
void CFontString::Update(void)
{
	SizeScale();
}

//=====================================
// �T�C�Y�ύX����
//=====================================
void CFontString::SizeScale(void)
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
void CFontString::SizeReset(void)
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
void CFontString::SetSellect(void)
{
	m_bSellect = true;
}

//=====================================
// ��������
//=====================================
CFontString* CFontString::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const std::string letter)
{
	CFontString* pFontString = new CFontString;
	
	if (FAILED(pFontString->Init()))
	{
		return nullptr;
	}

	for (int nCnt = 0; nCnt < MaxWordLenght; nCnt++)
	{
		pFontString->m_pFont[nCnt]  = nullptr;
	}

	// string�^�̕��������擾
	int nTex = strlen(letter.c_str());

	int nCnt = 0;
	float maxSizeX = size.x * 2;
	for (int nLatter = 0; nLatter < nTex; nLatter += 2)
	{
		// ���݈ʒu����1�����i�ޏ���
		std::string sLatter = letter.substr(nLatter , 2);

		// �����𒆉��ɔz�u���Astring�^����*char�^��1���������o��
		if (nTex / 2 % 2 == 1)
		{
			pFontString->m_pFont[nCnt++] = CFont::Create(D3DXVECTOR3(pos.x - (maxSizeX * (nTex / 4)) + ((maxSizeX * nCnt)), pos.y, pos.z), size, sLatter.c_str());
		}
		else
		{
			pFontString->m_pFont[nCnt++] = CFont::Create(D3DXVECTOR3(pos.x - (maxSizeX * ((nTex / 4) - 1)) + (maxSizeX * nCnt) - (maxSizeX / 2), pos.y, pos.z), size, sLatter.c_str());
		}

		// �ŏ��̃T�C�Y��o�^����
		pFontString->m_sizeYuan = size;

		// �ԍ�������U��
		pFontString->m_nNum++;
	}

	return pFontString;
}