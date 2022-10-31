//=============================================================================
//
// Letter.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "Letter.h"
#include <string>

//�R���X�g���N�^
CLetter::CLetter()
{
	m_bVanish = false;
	m_nLife = 0;
	m_pPreviousLetter = nullptr;
	m_pNextLetter = nullptr;
}

CLetter::CLetter(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{
	m_pPreviousLetter = nullptr;
	m_pNextLetter = nullptr;
}

//�f�X�g���N�^
CLetter::~CLetter()
{

}

//����������
HRESULT CLetter::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_bVanish = false;
	m_nLife = 0;
	m_pPreviousLetter = nullptr;
	m_pNextLetter = nullptr;

	return S_OK;
}

//�I������
void CLetter::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CLetter::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	if (m_bVanish)
	{
		if (m_nLife > 0)
		{
			m_nLife--;
		}

		if (m_nLife <= 0)
		{
			Release();
		}
	}
}

//�I������
void CLetter::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}

bool CLetter::ConvertInNumber(const int nNum)
{
	if (nNum >= 0 && nNum <= 9)
	{
		SetTexture(CObject::TEXTURE_NUMBERS);
		SetTextureParameter(1, 5, 3, INT_MAX);
		SetAnimPattern(nNum);
	}
	else
	{
		return false;
	}

	return true;
}

bool CLetter::ConvertInSymbol(const char symbol)
{
	if (symbol != '?' && symbol != '!' && symbol != '%')
	{
		return false;
	}
	else
	{
		SetTexture(CObject::TEXTURE_NUMBERS);
		SetTextureParameter(1, 5, 3, INT_MAX);

		switch (symbol)
		{
		case '?':

			SetAnimPattern(10);

			break;

		case '!':

			SetAnimPattern(11);

			break;

		case '%':

			SetAnimPattern(12);

			break;

		default:

			return false;

			break;
		}
	}
	
	return true;
}

bool CLetter::Convert(const char symbol)
{
	char aLetter = 33;

	//�A�j���[�V�����p�^�[���̐ݒ�
	int Cell = 27;

	for (int nCnt = 0; nCnt < 93; nCnt++)
	{
		if (symbol == aLetter)
		{
			Cell = nCnt;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 0 || Cell > 93)
	{
		return false;
	}
	else
	{
		SetAnimPattern(Cell);
		return true;
	}
}

void CLetter::SetLife(const int nLife)
{
	m_bVanish = true;

	m_nLife = nLife;
}

void CLetter::SetPrevLetter(CLetter* pPrev)
{
	m_pPreviousLetter = pPrev;
}

void CLetter::SetNextLetter(CLetter* pNext)
{
	m_pNextLetter = pNext;
}

CLetter* CLetter::GetPrevLetter(void)
{
	return m_pPreviousLetter;
}

CLetter* CLetter::GetNextLetter(void)
{
	return m_pNextLetter;
}


//==================================================================================================================
//
//		�ÓI�֐�
//
//==================================================================================================================

//��������
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter)
{
	CLetter* pLetter = new CLetter(3);								//����

																	//����������
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}

	pLetter->SetPos(pos);									//�ʒu�̐ݒ�
	pLetter->SetSize(size);									//�T�C�Y�̐ݒ�
															//pLetter->SetStartingRot(D3DX_PI * 0.5f);				//��]�p�x�̐ݒ�
	pLetter->SetTexture(CObject::TEXTURE_CHARACTERS);			//�e�N�X�`���̐ݒ�
	pLetter->SetTextureParameter(1, 10, 10, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	char aLetter = 33;

	//�A�j���[�V�����p�^�[���̐ݒ�
	int Cell = 27;

	for (int nCnt = 0; nCnt < 93; nCnt++)
	{
		if (letter == aLetter)
		{
			Cell = nCnt;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 0 || Cell > 93)
	{
			pLetter->Release();
			return nullptr;
	}
	else
	{
		pLetter->SetAnimPattern(Cell);
	}

	return pLetter;
}

//��������
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const int nNum)
{
	CLetter* pLetter = new CLetter(3);						//����

																	//����������
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}

	pLetter->SetPos(pos);									//�ʒu�̐ݒ�
	pLetter->SetSize(size);									//�T�C�Y�̐ݒ�
															//pLetter->SetStartingRot(D3DX_PI * 0.5f);				//��]�p�x�̐ݒ�
	pLetter->SetTexture(CObject::TEXTURE_CHARACTERS);		//�e�N�X�`���̐ݒ�
	pLetter->SetTextureParameter(1, 10, 10, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	std::string number = std::to_string(nNum);
	char aLetter = 47;

	//�A�j���[�V�����p�^�[���̐ݒ�
	int Cell = 14;

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		if (number.c_str()[0] == aLetter)
		{
			Cell = nCnt + 14;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 14 || Cell > 56)
	{
		pLetter->Release();
		return nullptr;
	}
	else
	{
		pLetter->SetAnimPattern(Cell);
	}


	return pLetter;
}

//��������
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter, const int nPriority)
{
	CLetter* pLetter = new CLetter(nPriority);						//����

	//����������
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}
	
	pLetter->SetPos(pos);									//�ʒu�̐ݒ�
	pLetter->SetSize(size);									//�T�C�Y�̐ݒ�
	//pLetter->SetStartingRot(D3DX_PI * 0.5f);				//��]�p�x�̐ݒ�
	pLetter->SetTexture(CObject::TEXTURE_CHARACTERS);		//�e�N�X�`���̐ݒ�
	pLetter->SetTextureParameter(1, 10, 10, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	char aLetter = 33;

	//�A�j���[�V�����p�^�[���̐ݒ�
	int Cell = 27;

	for (int nCnt = 0; nCnt < 93; nCnt++)
	{
		if (letter == aLetter)
		{
			Cell = nCnt;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 0 || Cell > 93)
	{
		pLetter->Release();
		return nullptr;
	}
	else
	{
		pLetter->SetAnimPattern(Cell);
	}

	return pLetter;				
} 

//��������
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const int nNum, const int nPriority)
{
	//CLetter* pLetter = new CLetter(nPriority);			//����

	//													//����������
	//if (FAILED(pLetter->Init()))
	//{
	//	return nullptr;
	//}

	//pLetter->SetPos(pos);									//�ʒu�̐ݒ�
	//pLetter->SetSize(size);									//�T�C�Y�̐ݒ�
	//pLetter->SetStartingRot(D3DX_PI * 0.5f);				//��]�p�x�̐ݒ�
	//pLetter->SetTexture(CObject::TEXTURE_LETTERS);			//�e�N�X�`���̐ݒ�
	//pLetter->SetTextureParameter(26, 13, 2, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	//if (!pLetter->ConvertInNumber(nNum))
	//{
	//	pLetter->Uninit();
	//	pLetter->Release();
	//	return nullptr;
	//}

	CLetter* pLetter = new CLetter(nPriority);						//����

																	//����������
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}

	pLetter->SetPos(pos);									//�ʒu�̐ݒ�
	pLetter->SetSize(size);									//�T�C�Y�̐ݒ�
															//pLetter->SetStartingRot(D3DX_PI * 0.5f);				//��]�p�x�̐ݒ�
	pLetter->SetTexture(CObject::TEXTURE_CHARACTERS);		//�e�N�X�`���̐ݒ�
	pLetter->SetTextureParameter(1, 10, 10, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	std::string number = std::to_string(nNum);
	char aLetter = 47;

	//�A�j���[�V�����p�^�[���̐ݒ�
	int Cell = 14;

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		if (number.c_str()[0] == aLetter)
		{
			Cell = nCnt + 14;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 14 || Cell > 56)
	{
		pLetter->Release();
		return nullptr;
	}
	else
	{
		pLetter->SetAnimPattern(Cell);
	}
	

	return pLetter;
}