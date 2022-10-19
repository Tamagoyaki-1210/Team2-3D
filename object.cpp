//=============================================================================
//
// �I�u�W�F�N�g
// Author : tanimoto kosuke
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "game.h"
#include "Application.h"
#include "mode.h"

CObject *CObject::m_pTop[MAX_OBJECT_PRIORITY] = {};
CObject *CObject::m_pCurrent[MAX_OBJECT_PRIORITY] = {};
//=====================================
//�f�t�H���g�R���X�g���N�^
//=====================================
CObject::CObject(int priority) : m_bDeath(false)
{
	//���݂̃I�u�W�F�N�g���g�p���̏ꍇ
	if (m_pCurrent[priority] != nullptr)
	{
		m_pCurrent[priority]->m_pNext = this;
		m_pPrev = m_pCurrent[priority];
		m_pCurrent[priority] = this;
	}
	else
	{
		m_pTop[priority] = this;
		m_pCurrent[priority] = this;
		m_pPrev = nullptr;
	}
	m_pNext = nullptr;
	//m_nPriority = priority;
}

//=====================================
//�f�X�g���N�^
//=====================================
CObject::~CObject()
{
	
}

//=====================================
//�������
//=====================================
void CObject::Release()
{
	//// �O��|�C���^���g�p���̏ꍇ
	//if (m_pPrev != nullptr)
	//{
	//	// ����|�C���^���g�p���̏ꍇ
	//	if (m_pNext != nullptr)
	//	{
	//		m_pPrev->m_pNext = m_pNext;
	//		m_pNext->m_pPrev = m_pPrev;
	//	}
	//	else
	//	{
	//		m_pPrev->m_pNext = nullptr;
	//		m_pCurrent[m_nPriority] = m_pPrev;
	//	}
	//}
	//else
	//{
	//	// ����|�C���^���g�p���̏ꍇ
	//	if (m_pNext != nullptr)
	//	{
	//		m_pNext->m_pPrev = nullptr;
	//		m_pTop[m_nPriority] = m_pNext;
	//	}
	//	else
	//	{
	//		m_pTop[m_nPriority] = nullptr;
	//		m_pCurrent[m_nPriority] = nullptr;
	//	}
	//}
	//delete this;
	m_bDeath = true;
}

//=====================================
//�S�Ẳ������
//=====================================
void CObject::ReleaseAll(void)
{
	for (int i = 0; i < MAX_OBJECT_PRIORITY; i++)
	{
		// �擪�|�C���^���g�p���̏ꍇ
		if (m_pTop[i] != nullptr)
		{
			//���݈ʒu�|�C���^�ɐ擪�|�C���^����
			CObject *pObject = m_pTop[i];
			//���݈ʒu�|�C���^�����g�p�ɂȂ�܂�
			while (pObject != nullptr)
			{
				//CObject *pObjectNext = pObject->m_pNext;
				pObject->Uninit();
				pObject = pObject->m_pNext;
			}
		}
	}
	for (int i = 0; i < MAX_OBJECT_PRIORITY; i++)
	{
		// �擪�|�C���^���g�p���̏ꍇ
		if (m_pTop[i] != nullptr)
		{
			//���݈ʒu�|�C���^�ɐ擪�|�C���^����
			CObject *pObject = m_pTop[i];
			//���݈ʒu�|�C���^���g�p���̏ꍇ
			while (pObject != nullptr)
			{
				CObject *pObjectNext = pObject->m_pNext;

				// �O��|�C���^���g�p���̏ꍇ
				if (pObject->m_pPrev != nullptr)
				{
					// ����|�C���^���g�p���̏ꍇ
					if (pObject->m_pNext != nullptr)
					{
						pObject->m_pPrev->m_pNext = pObject->m_pNext;
						pObject->m_pNext->m_pPrev = pObject->m_pPrev;
					}
					else
					{
						pObject->m_pPrev->m_pNext = nullptr;
						m_pCurrent[i] = pObject->m_pPrev;
					}
				}
				else
				{
					// ����|�C���^���g�p���̏ꍇ
					if (pObject->m_pNext != nullptr)
					{
						pObject->m_pNext->m_pPrev = nullptr;
						m_pTop[i] = pObject->m_pNext;
					}
					else
					{
						m_pTop[i] = nullptr;
						m_pCurrent[i] = nullptr;
					}
				}
				delete pObject;
				pObject = pObjectNext;
			}
		}
	}
}

//=====================================
//�S�Ă̍X�V����
//=====================================
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_OBJECT_PRIORITY; i++)
	{
		// �擪�|�C���^���g�p���̏ꍇ
		if (m_pTop[i] != nullptr)
		{
			//���݈ʒu�|�C���^�ɐ擪�|�C���^����
			CObject *pObject = m_pTop[i];

			//���݂̃��[�h
			CMode::MODE mode = CApplication::GetMode()->GetMode();

			//���݈ʒu�|�C���^���g�p���̏ꍇ
			while (pObject != nullptr)
			{
				//���S�t���O�������Ă��Ȃ��ꍇ
				if (!pObject->m_bDeath)
				{
					//�Q�[�����ł���A�`�揇��UI��艺�̏ꍇ
					if (mode == CMode::MODE_GAME && i < UI_PRIORITY_UI)
					{
						if (CGame::GetPause() == false)
						{
							pObject->Update();
						}
					}
					else
					{
						pObject->Update();
					}
				}
				pObject = pObject->m_pNext;
			}
		}
	}
	for (int i = 0; i < MAX_OBJECT_PRIORITY; i++)
	{
		// �擪�|�C���^���g�p���̏ꍇ
		if (m_pTop[i] != nullptr)
		{
			//���݈ʒu�|�C���^�ɐ擪�|�C���^����
			CObject *pObject = m_pTop[i];
			//���݈ʒu�|�C���^���g�p���̏ꍇ
			while (pObject != nullptr)
			{
				CObject *pObjectNext = pObject->m_pNext;
				//���S�t���O�������Ă���ꍇ
				if (pObject->m_bDeath)
				{
					// �O��|�C���^���g�p���̏ꍇ
					if (pObject->m_pPrev != nullptr)
					{
						// ����|�C���^���g�p���̏ꍇ
						if (pObject->m_pNext != nullptr)
						{
							pObject->m_pPrev->m_pNext = pObject->m_pNext;
							pObject->m_pNext->m_pPrev = pObject->m_pPrev;
						}
						else
						{
							pObject->m_pPrev->m_pNext = nullptr;
							m_pCurrent[i] = pObject->m_pPrev;
						}
					}
					else
					{
						// ����|�C���^���g�p���̏ꍇ
						if (pObject->m_pNext != nullptr)
						{
							pObject->m_pNext->m_pPrev = nullptr;
							m_pTop[i] = pObject->m_pNext;
						}
						else
						{
							m_pTop[i] = nullptr;
							m_pCurrent[i] = nullptr;
						}
					}
					delete pObject;
				}
				pObject = pObjectNext;
			}
		}
	}
}

//=====================================
//�S�Ă̕`�揈��
//=====================================
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_OBJECT_PRIORITY; i++)
	{
		// �擪�|�C���^���g�p���̏ꍇ
		if (m_pTop[i] != nullptr)
		{
			//���݈ʒu�|�C���^�ɐ擪�|�C���^����
			CObject *pObject = m_pTop[i];

			//���݈ʒu�|�C���^���g�p���̏ꍇ
			while (pObject != nullptr)
			{
				CObject *pObjectNext = pObject->m_pNext;
				pObject->Draw();
				pObject = pObjectNext;
			}
		}
	}
}

//=====================================
//�I�u�W�F�N�g�ݒ菈��
//=====================================
void CObject::SetType(Object_Type type)
{
	m_type = type;
}

//=====================================
//��ʎ擾����
//=====================================
const CObject::Object_Type& CObject::GetType() const
{
	return m_type;
}