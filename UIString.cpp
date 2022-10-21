//=============================================================================
//
// UIString.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "UIString.h"
#include "Letter.h"

//�R���X�g���N�^
CUIString::CUIString()
{
	m_pTop = nullptr;
}

CUIString::CUIString(const int nPriority) : CObject(nPriority)
{
	m_pTop = nullptr;
}

//�f�X�g���N�^
CUIString::~CUIString()
{
	
}

//����������
HRESULT CUIString::Init(void)
{
	m_pTop = nullptr;

	return S_OK;
}

//�I������
void CUIString::Uninit(void)
{
	ReleaseLetters();
}

//�X�V����
void CUIString::Update(void)
{
	
}

//�`�揈��
void CUIString::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CUIString::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CUIString::GetSize(void)
{
	return m_size;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CUIString::GetPos(void)
{
	return m_pos;
}

//�j������
void CUIString::ReleaseLetters(void)
{
	if (m_pTop != nullptr)
	{
		CLetter* pCurrent = m_pTop;
		CLetter* pNext = m_pTop->GetNextLetter();

		while (pCurrent != nullptr)
		{
			pNext = pCurrent->GetNextLetter();
			pCurrent->Release();
			pCurrent = pNext;
		}
	}
}






//��������
CUIString* CUIString::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const char* pString)
{
	CUIString* pStr = new CUIString;

	if (FAILED(pStr->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR2 letterSize = Vec2Null;
	int nLenght = strlen(pString);
	letterSize.x = size.x / nLenght;
	letterSize.y = size.y;

	pStr->m_pTop = CLetter::Create(D3DXVECTOR3(pos.x + letterSize.x * 0.5f, pos.y, 0.0f), letterSize, pString[0], 3);
	CLetter* pLetter = nullptr;

	if (pStr->m_pTop != nullptr)
	{
		CLetter* pCurrent = pStr->m_pTop;

		for (int nCnt = 1; nCnt < nLenght; nCnt++)
		{
			if (pString[nCnt] != ' ')
			{
				pLetter = CLetter::Create(D3DXVECTOR3(pos.x + letterSize.x * 0.5f + letterSize.x * nCnt, pos.y, 0.0f), letterSize, pString[nCnt], 3);

				if (pLetter != nullptr)
				{
					pCurrent->SetNextLetter(pLetter);
					pLetter->SetPrevLetter(pCurrent);
					pCurrent = pLetter;
					pLetter = nullptr;
				}
			}
		}
	}

	if (pStr->m_pTop != nullptr)
	{
		pLetter = pStr->m_pTop;

		while (pLetter != nullptr)
		{
			pLetter->SetColor(col);
			//pLetter->SetPriority(5);
			pLetter = pLetter->GetNextLetter();
		}
	}

	return pStr;
}

CUIString* CUIString::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const char* pString, const int nPriority)
{
	CUIString* pStr = new CUIString(nPriority);

	if (FAILED(pStr->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR2 letterSize = Vec2Null;
	int nLenght = strlen(pString);
	letterSize.x = size.x / nLenght;
	letterSize.y = size.y;

	pStr->m_pTop = CLetter::Create(D3DXVECTOR3(pos.x + letterSize.x * 0.5f, pos.y, 0.0f), letterSize, pString[0], nPriority);
	CLetter* pLetter = nullptr;

	if (pStr->m_pTop != nullptr)
	{
		CLetter* pCurrent = pStr->m_pTop;

		for (int nCnt = 1; nCnt < nLenght; nCnt++)
		{
			if (pString[nCnt] != ' ')
			{
				pLetter = CLetter::Create(D3DXVECTOR3(pos.x + letterSize.x * 0.5f + letterSize.x * nCnt, pos.y, 0.0f), letterSize, pString[nCnt], nPriority);

				if (pLetter != nullptr)
				{
					pCurrent->SetNextLetter(pLetter);
					pLetter->SetPrevLetter(pCurrent);
					pCurrent = pLetter;
					pLetter = nullptr;
				}
			}
		}
	}

	if (pStr->m_pTop != nullptr)
	{
		pLetter = pStr->m_pTop;

		while (pLetter != nullptr)
		{
			pLetter->SetColor(col);
			//pLetter->SetPriority(5);
			pLetter = pLetter->GetNextLetter();
		}
	}

	return pStr;
}