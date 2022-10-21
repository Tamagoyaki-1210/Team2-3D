//=============================================================================
//
// player.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"
#include "inputKeyboard.h"
#include "model.h"
#include "camera.h"
#include "application.h"
#include "debugProc.h"
#include "meshfield.h"
#include "modelPart.h"
#include "animator.h"

//�R���X�g���N�^
CPlayer::CPlayer()
{
	//�����o�[�ϐ����N���A����
	m_move = Vec3Null;
	m_DestRot = Vec3Null;
	m_pAnimator = nullptr;

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{

}

//����������
HRESULT CPlayer::Init(void)
{
	//�����o�[�ϐ��̏���������
	m_move = Vec3Null;				//���x�̏���������
	m_DestRot = Vec3Null;			//�ړI�̊p�x�̏���������
	m_pAnimator = nullptr;

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CPlayer::Uninit(void)
{
	//���f���p�[�c�̏I������
	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{
		if (m_pModel[nCnt] != nullptr)
		{
			m_pModel[nCnt]->Uninit();
			delete m_pModel[nCnt];
			m_pModel[nCnt] = nullptr;
		}
	}

	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Uninit();
		delete m_pAnimator;
		m_pAnimator = nullptr;
	}
}

//�X�V����
void CPlayer::Update(void)
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();					//�J�����̌����̎擾����
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));		
	float fA = acosf(cR.x);

	if (cR.z < 0.0f)
	{
		fA *= -1.0f;
	}

	//�ړ��ʂƖړI�̊p�x�̌v�Z
	if (CInputKeyboard::GetKeyboardPress(DIK_W))
	{//W�L�[�������ꂽ�ꍇ
		if (CInputKeyboard::GetKeyboardPress(DIK_A))
		{//A�L�[�������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(D3DX_PI * 0.25f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(D3DX_PI * 0.25f + cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.25f + fA;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D))
		{//D�L�[�������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(-D3DX_PI * 0.25f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(-D3DX_PI * 0.25f + cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.75f + fA;
		}
		else
		{//W�L�[�����������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.5f + fA;
		}
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_S))
	{//S�L�[�������ꂽ�ꍇ
		if (CInputKeyboard::GetKeyboardPress(DIK_A))
		{//A�L�[�������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(D3DX_PI * 0.75f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(D3DX_PI * 0.75f + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.25f + fA;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D))
		{//D�L�[�������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(-D3DX_PI * 0.75f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(-D3DX_PI * 0.75f + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.75f + fA;
		}
		else
		{//S�L�[�����������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(D3DX_PI + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(D3DX_PI + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.5f + fA;
		}
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_D))
	{//D�L�[���������ꂽ�ꍇ
		if (m_move.x <= 4.0f && m_move.x >= -4.0f)
		{
			m_move.x += 0.5f * cosf(-D3DX_PI * 0.5f + cameraRot.y);
		}
		if (m_move.z <= 4.0f && m_move.z >= -4.0f)
		{
			m_move.z += 0.5f * sinf(-D3DX_PI * 0.5f + cameraRot.y);
		}

		m_DestRot.y = D3DX_PI + fA;
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_A))
	{//A�L�[���������ꂽ�ꍇ
		if (m_move.x <= 4.0f && m_move.x >= -4.0f)
		{
			m_move.x += 0.5f * cosf(D3DX_PI * 0.5f + cameraRot.y);
		}
		if (m_move.z <= 4.0f && m_move.z >= -4.0f)
		{
			m_move.z += 0.5f * sinf(D3DX_PI * 0.5f + cameraRot.y);
		}

		m_DestRot.y = fA;
	}

	//m_pModel->SetPos(m_pModel->GetPos() + m_move);

	m_move.x += (0.0f - m_move.x) * 0.1f;				//�ړ��ʂ�X�R���|�l���g�̍X�V
	m_move.y += (0.0f - m_move.y) * 0.1f;				//�ړ��ʂ�Y�R���|�l���g�̍X�V
	m_move.z += (0.0f - m_move.z) * 0.1f;				//�ړ��ʂ�Z�R���|�l���g�̍X�V

	m_pos += m_move;									//�ʒu�̍X�V

	//�ړI�̊p�x�̐��K������
	if (m_DestRot.y - (m_pModel[BODY]->GetRot().y) > D3DX_PI)
	{
		m_DestRot.y -= 2 * D3DX_PI;
	}
	else if (m_DestRot.y - (m_pModel[BODY]->GetRot().y) < -D3DX_PI)
	{
		m_DestRot.y += 2 * D3DX_PI;
	}

	D3DXVECTOR3 rot = m_pModel[BODY]->GetRot() + ((m_DestRot - m_pModel[BODY]->GetRot()) * 0.1f);		//��]�p�x�̌v�Z

	m_pModel[BODY]->SetRot(rot);		//��]�p�x�̐ݒ菈��

	//��]�p�x�̐��K������
	{
		float fRot = m_pModel[BODY]->GetRot().y;

		if (fRot > D3DX_PI)
		{
			fRot = -D3DX_PI + (fRot - D3DX_PI);
		}
		else if (fRot < -D3DX_PI)
		{
			fRot = D3DX_PI - (D3DX_PI + fRot);
		}

		if (fRot < D3DX_PI * -2.0f)
		{
			fRot += D3DX_PI * 2.0f;
		}
		else if (fRot > D3DX_PI * 2.0f)
		{
			fRot += D3DX_PI * -2.0f;
		}

		//��]�̐ݒ菈��
		m_pModel[BODY]->SetRot(D3DXVECTOR3(m_pModel[BODY]->GetRot().x, fRot, m_pModel[BODY]->GetRot().z));
	}

	//�d�ʂ�ǉ�����
	if (m_move.y >= -10.0f)
	{
		m_move.y -= 0.5f;
	}

	//SetPos(pos);

	CMeshfield::FieldInteraction(this);				//�n�ʂƂ̓����蔻��

	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Update();
	}

	CDebugProc::Print("\nRot: %f\nRot Dest: %f\n\nPos: %f, %f, %f", m_pModel[BODY]->GetRot().y, m_DestRot.y, m_pos.x, m_pos.y, m_pos.z);
}

//�`�揈��
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxTrans, mtxRot;												//�v�Z�p�̃}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);											//���[���h�}�g���b�N�X�̏���������

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	m_pModel[BODY]->Draw(m_mtxWorld);											//�ŏ��̃��f���̕`�揈��

	for (int nCnt = 1; nCnt < PARTS_MAX; nCnt++)
	{//���̃��f���̕`�揈��
		if (m_pModel[nCnt] != nullptr)
		{
			m_pModel[nCnt]->Draw();
		}
	}
}

//�ʒu�̐ݒ菈��
void CPlayer::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CPlayer::GetSize(void)
{
	return Vec2Null;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}



//��������
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos)
{
	CPlayer* pModel = new CPlayer;			//�C���X�^���X�𐶐�����
	
	//�v���C���[�̏���������
	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_pModel[BODY] = CModelPart::Create(CModel::MODEL_CROBAT_BODY, D3DXVECTOR3(0.0f, 50.0f, 0.0f), Vec3Null);						//�̂̃��f���𐶐�����
	pModel->m_pModel[LEFT_WING] = CModelPart::Create(CModel::MODEL_CROBAT_LEFT_WING, D3DXVECTOR3(7.0f, 10.0f, -2.0f), Vec3Null);			//�����̃��f���𐶐�����
	pModel->m_pModel[LEFT_WING]->SetParent(pModel->m_pModel[BODY]);																			//�����̐e��ݒ肷��
	pModel->m_pModel[RIGHT_WING] = CModelPart::Create(CModel::MODEL_CROBAT_RIGHT_WING, D3DXVECTOR3(-7.0f, 10.0f, -2.0f), Vec3Null);			//�E���̃��f���𐶐�����
	pModel->m_pModel[RIGHT_WING]->SetParent(pModel->m_pModel[BODY]);																		//�E���̐e��ݒ肷��
	pModel->m_pModel[LEFT_WING_SMALL] = CModelPart::Create(CModel::MODEL_CROBAT_LEFT_WING_SMALL, D3DXVECTOR3(6.0f, 6.0f, 0.0f), Vec3Null);			//����(������)�̃��f���𐶐�����
	pModel->m_pModel[LEFT_WING_SMALL]->SetParent(pModel->m_pModel[BODY]);																			//����(������)�̐e��ݒ肷��
	pModel->m_pModel[RIGHT_WING_SMALL] = CModelPart::Create(CModel::MODEL_CROBAT_RIGHT_WING_SMALL, D3DXVECTOR3(-6.0f, 6.0f, 0.0f), Vec3Null);			//�E��(������)�̃��f���𐶐�����
	pModel->m_pModel[RIGHT_WING_SMALL]->SetParent(pModel->m_pModel[BODY]);																		//�E��(������)�̐e��ݒ肷��

	std::vector <CModelPart*> vParts;
	vParts.clear();
	vParts.push_back(pModel->m_pModel[BODY]);
	vParts.push_back(pModel->m_pModel[LEFT_WING]);
	vParts.push_back(pModel->m_pModel[RIGHT_WING]);
	vParts.push_back(pModel->m_pModel[LEFT_WING_SMALL]);
	vParts.push_back(pModel->m_pModel[RIGHT_WING_SMALL]);
	pModel->m_pAnimator = CAnimator::Create(&vParts, CAnimator::ANIM_TYPE_CROBAT);

	return pModel;
}