//=============================================================================
//
// warning.cpp
// Author : tanimoto kosuke
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "warning.h"
#include "application.h"

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CWarning::CWarning()
{

}

CWarning::CWarning(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CWarning::~CWarning()
{

}

//=====================================
// ����������
//=====================================
HRESULT CWarning::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_nMaxBlink = 10;

	CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WARNINGS);
	return S_OK;
}

//=====================================
// �I������
//=====================================
void CWarning::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//=====================================
// �X�V����
//=====================================
void CWarning::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	if (m_nLife <= 0)
	{
		BlinkColor();
	}
	else
	{
		m_nLife--;
	}
}

//=====================================
// �`�揈��
//=====================================
void CWarning::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}

//=====================================
// �`�揈��
//=====================================
void CWarning::BlinkColor(void)
{
	if (m_bBlink)
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	else
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	m_bBlink = !m_bBlink;
	m_nLife = 20.0f;
	m_nMaxBlink--;

	if (m_nMaxBlink <= 0)
	{
		Release();
	}
}

//=====================================
// ��������
//=====================================
CWarning* CWarning::Create(const D3DXVECTOR3 pos)
{
	CWarning* pWarning = new CWarning(5);		//����(Priority = 5)

										//����������
	if (FAILED(pWarning->Init()))
	{
		return nullptr;
	}

	pWarning->SetPos(pos);									//�ʒu�̐ݒ�
	pWarning->SetSize(D3DXVECTOR2(50.0f, 50.0f));			//�T�C�Y�̐ݒ�
	pWarning->SetTexture(CObject::TEXTURE_EXCLAMATION);		//�e�N�X�`���̐ݒ�

	return pWarning;
}