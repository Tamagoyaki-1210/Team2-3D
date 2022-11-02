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
#include "application.h"

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
	m_nMessageIdx = 0;
	m_nMessageCounter = 0;
	m_nNum = 0;
	m_bStart = false;
	m_type = MESSAGE_COUNTDOWN;
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
	m_nMessageIdx = 0;
	m_nMessageCounter = 0;
	m_nNum = 0;
	m_bStart = false;
}

//=====================================
// �X�V����
//=====================================
void CMessage::Update(void)
{
	// �|�[�Y���łȂ��ꍇ�̂ݍX�V
	if (CApplication::GetPause() == false)
	{
		// �J�E���g��0����̏ꍇ
		if (m_nMessageCounter > 0)
		{
			m_nMessageCounter--;

			// �J�E���g��0�ȉ��ɂȂ����ꍇ
			if (m_nMessageCounter <= 0)
			{
				if (m_type == MESSAGE_COUNTDOWN)
				{// �J�E���g�_�E�������̏ꍇ
					m_nNum--;
					// ���݈ʒu��0���傫���ꍇ
					if (m_nNum > 0)
					{
						m_nMessageCounter = CountDownLife;
						m_pObj2D->SetAnimPattern(m_nNum);
					}
					else
					{
						Destroy();
						StartMessage();
					}
				}
				else if (m_type == MESSAGE_GOAL)
				{
					Destroy();
					WinMessage();
				}
				else if (m_type == MESSAGE_WIN)
				{
					Uninit();
					// �Q�[���I������
					CGame::SetEndGame();
				}
				else
				{
					Destroy();
				}
			}
		}
	}
}

//=====================================
// �J�E���g�_�E�����b�Z�[�W�\������
//=====================================
void CMessage::SetCountDown(int nNum)
{
	if (m_pObj2D == nullptr)
	{
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(200.0f, 150.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_NUMBERS);
		m_pObj2D->SetTextureParameter(1, 5, 3, INT_MAX);
		m_pObj2D->SetPriority(3);
		m_nNum = nNum;
		m_pObj2D->SetAnimPattern(nNum);
		m_nMessageCounter = CountDownLife;
		m_type = MESSAGE_COUNTDOWN;
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
		m_pObj2D->SetPriority(4);
		m_nMessageCounter = 120;
		m_type = MESSAGE_START;
		m_bStart = true;
	}
}

//=====================================
// �S�[�����b�Z�[�W�\������
//=====================================
void CMessage::GoalMessage(int nMessageIdx)
{
	if (m_pObj2D == nullptr)
	{
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_MESSAGE_GOAL);
		m_pObj2D->SetTextureParameter(1, 1, 1, INT_MAX);
		m_pObj2D->SetPriority(4);
		m_nMessageCounter = 120;
		m_type = MESSAGE_GOAL;
		m_bStart = false;
		// ���s�ԍ���������
		m_nMessageIdx = nMessageIdx;
	}
}


//=====================================
// �S�[�����b�Z�[�W�\������
//=====================================
void CMessage::WinMessage()
{
	if (m_pObj2D == nullptr)
	{
		// ���_�ł͂Ȃ��ꍇ
		if (m_nMessageIdx != 0)
		{
			// WIN����
			m_pObj2D = CObject_2D::Create();
			m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f));
			m_pObj2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
			m_pObj2D->SetTexture(CObject::TEXTURE_WINNER);
			m_pObj2D->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pObj2D->SetPriority(4);
		}

		// ���s���b�Z�[�W����
		CObject_2D *pObject2D = CObject_2D::Create();
		pObject2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		pObject2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		pObject2D->SetTextureParameter(1, 1, 1, INT_MAX);
		pObject2D->SetPriority(4);

		// �ԍ��Ńv���C���[��ύX����
		switch (m_nMessageIdx)
		{
		case 0:
			pObject2D->SetTexture(CObject::TEXTURE_DRAW);
			break;
		case 1:
			pObject2D->SetTexture(CObject::TEXTURE_1P_WIN);
			break;
		case 2:
			pObject2D->SetTexture(CObject::TEXTURE_2P_WIN);
			break;
		case 3:
			pObject2D->SetTexture(CObject::TEXTURE_3P_WIN);
			break;
		case 4:
			pObject2D->SetTexture(CObject::TEXTURE_4P_WIN);
			break;
		default:
			pObject2D->SetTexture(CObject::TEXTURE_NULL);
			break;
		}

		m_type = MESSAGE_WIN;
		m_nMessageCounter = 120;
	}
}

//=====================================
// �I������
//=====================================
void CMessage::Destroy(void)
{
	if (m_pObj2D != nullptr)
	{
		m_pObj2D->Release();
		m_pObj2D = nullptr;
		m_nMessageCounter = 120;
		m_bEndGame = true;
	}
	m_nMessageCounter = 0;
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