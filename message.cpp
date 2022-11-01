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
#include "game.h"

//�ÓI�����o�[�ϐ��錾
bool CMessage::m_bStart;

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
	m_nNum = 0;
	m_bCountDown = false;
	m_bEndGame = false;
	m_bStart = false;
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
	m_nMessageCounter = 0;
	m_nNum = 0;
	m_bCountDown = false;
	m_bEndGame = false;
}

//=====================================
// �X�V����
//=====================================
void CMessage::Update(void)
{
	// �J�E���g�_�E�������łȂ����
	if (m_bCountDown == false)
	{
		// ���b�Z�[�W�\�����Ԃ��J�E���g
		if (m_nMessageCounter > 0)
		{

			m_nMessageCounter--;
		}
		else
		{	// �Q�[���I������
			if (m_bEndGame == true)
			{
				CGame::SetEndGame();
			}
			m_nMessageCounter = 0;
			m_bStart = true;
			Uninit();
		}
	}
	else
	{
		CountDown();
	}
}

//=====================================
// �J�E���g�_�E�����b�Z�[�W�\������
//=====================================
void CMessage::SetCountDown(int nNum)
{
	if (m_bCountDown == false && m_pObj2D == nullptr)
	{
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(200.0f, 150.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_NUMBERS);
		m_pObj2D->SetTextureParameter(1, 5, 3, INT_MAX);
		m_nNum = nNum;
		m_pObj2D->SetAnimPattern(nNum);
		m_nMessageCounter = CountDownLife;
		m_bCountDown = true;
	}
}

//=====================================
// �J�E���g�_�E�����b�Z�[�W�\������
//=====================================
void CMessage::CountDown()
{
	m_nMessageCounter--;
	if (m_nMessageCounter <= 0)
	{
		m_nNum--;
		// ���݈ʒu��0���傫���ꍇ
		if (m_nNum > 0)
		{
			m_nMessageCounter = CountDownLife;
			m_pObj2D->SetAnimPattern(m_nNum);
		}
		else
		{
			Uninit();
			StartMessage();
		}
	}
}

//=====================================
// �X�^�[�g���b�Z�[�W�\������
//=====================================
void CMessage::StartMessage(void)
{
	if (m_pObj2D == nullptr)
	{
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_MESSAGE_START);
		m_pObj2D->SetTextureParameter(1, 1, 1, INT_MAX);
		m_nMessageCounter = 120;
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
		m_bEndGame = true;
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