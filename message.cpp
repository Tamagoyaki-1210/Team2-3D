//=============================================================================
//
// message.cpp
// Author : tanimoto kosuke
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "message.h"

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CMessage::CMessage()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CMessage::~CMessage()
{

}

//=====================================
// ����������
//=====================================
HRESULT CMessage::Init(void)
{
	m_nMessageCounter = 0;
	return S_OK;
}

//=====================================
// �I������
//=====================================
void CMessage::Uninit(void)
{
	if (m_pObj2D != nullptr)
	{
		m_pObj2D->Release();
		m_pObj2D = nullptr;
	}
}

//=====================================
// �X�V����
//=====================================
void CMessage::Update(void)
{
	// ���b�Z�[�W�\�����Ԃ��J�E���g
	if (m_nMessageCounter > 0)
	{
		m_nMessageCounter--;
	}
	else
	{
		m_nMessageCounter = 0;
		Uninit();
	}
}

//=====================================
// �S�[�����b�Z�[�W�\������
//=====================================
void CMessage::GoalMessage(void)
{
	if (m_pObj2D == nullptr)
	{
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_MESSAGE_GOAL);
		m_pObj2D->SetTextureParameter(1, 1, 1, INT_MAX);
		m_nMessageCounter = 120;
	}
}

//=====================================
// ��������
//=====================================
CMessage* CMessage::Create()
{
	CMessage* pMessage = new CMessage;

	//����������
	if (FAILED(pMessage->Init()))
	{
		return nullptr;
	}

	return pMessage;
}