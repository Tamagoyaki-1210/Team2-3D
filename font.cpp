//=============================================================================
//
// font.cpp
// Author : tanimoto kosuke
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "font.h"

//�Ђ炪�ȃZ�b�g
std::map<std::string, int> CFont::m_hiraganaData = 
{
	{ "��", 0 },{ "��", 1 },{ "��", 2 },{ "��", 3 },{ "��", 4 },
	{ "��", 5 },{ "��", 6 },{ "��", 7 },{ "��", 8 },{ "��", 9 },
	{ "��", 10 },{ "��", 11 },{ "��", 12 },{ "��", 13 },{ "��", 14 },
	{ "��", 15 },{ "��", 16 },{ "��", 17 },{ "��", 18 },{ "��", 19 },
	{ "��", 20 },{ "��", 21 },{ "��", 22 },{ "��", 23 },{ "��", 24 },
	{ "��", 25 },{ "��", 26 },{ "��", 27 },{ "��", 28 },{ "��", 29 },
	{ "��", 30 },{ "��", 31 },{ "��", 32 },{ "��", 33 },{ "��", 34 },
	{ "��", 35 },{ "��", 36 },{ "��", 37 },{ "�A", 38 },{ "�B", 39 },
	{ "��", 40 },{ "��", 41 },{ "��", 42 },{ "��", 43 },{ "��", 44 },
	{ "��", 45 },{ "��", 46 },{ "��", 47 },{ "�[", 48 },{ "�E", 49 },
	{ "��", 50 },{ "��", 51 },{ "��", 52 },{ "��", 53 },{ "��", 54 },
};
//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CFont::CFont()
{

}

CFont::CFont(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CFont::~CFont()
{

}

//=====================================
// ����������
//=====================================
HRESULT CFont::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	return S_OK;
}


//=====================================
// �I������
//=====================================
void CFont::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//=====================================
// �X�V����
//=====================================
void CFont::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();
}


//=====================================
// �`�揈��
//=====================================
void CFont::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}

//=====================================
// ��������
//=====================================
CFont* CFont::Create(const D3DXVECTOR2 addPos, const D3DXVECTOR2 size, const std::string str, const int nPriority, int nCnt, int nMax)
{
	CFont* pFont = new CFont(nPriority);

	if (FAILED(pFont->Init()))
	{
		return nullptr;
	}
	int nTex = m_hiraganaData[str];

	pFont->SetSize(size);									//�T�C�Y�̐ݒ�
	float fSize = pFont->GetSize().x * 2;
	pFont->SetPos(D3DXVECTOR3((SCREEN_WIDTH / 2 - (nMax * fSize) * 0.5) + (nCnt * fSize) + addPos.x, 300.0f + addPos.y, 0.0f) );

	pFont->SetTexture(CObject::TEXTURE_HIRAGANA);			//�e�N�X�`���̐ݒ�
	pFont->SetTextureParameter(100, 10, 10, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�
	pFont->SetAnimPattern(nTex);
	return pFont;
}