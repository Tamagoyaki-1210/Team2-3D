//============================================================================
//
//�J�����̏���[camera.cpp] (�t�@�C���w�b�_�R�����g)
//Author:�J�{�N��
//============================================================================
#include "camera.h"		//�쐬����camera.h���C���N���[�h����
#include "input.h"		//�쐬����input.h���C���N���[�h����
#include "application.h"
#include "player.h"
#include "debugproc.h"

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CCamera::CCamera()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CCamera::~CCamera()
{

}

//============================================================================
//�J�����̏���������
//============================================================================
void CCamera::Init()
{
	//�n�_�E�����_�E�������ݒ肷��
	m_posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_���璍���_�̋���
	m_fDistance = sqrtf(powf(m_posR.x - m_posV.x, 2) + powf(m_posR.z - m_posV.z, 2));
	m_bFollowUse = false;
}

//============================================================================
//�J�����̏I������
//============================================================================
void CCamera::Uninit()
{

}

//============================================================================
//�J�����̍X�V����
//============================================================================
void CCamera::Update()
{
	Input();

	//++++++++++++++++++++++++++++++++++++
	// �p�x�̐��K��
	//++++++++++++++++++++++++++++++++++++
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}
	//++++++++++++++++++++++++++++++++++++
	// �J�����Ǐ]
	//++++++++++++++++++++++++++++++++++++
	if (m_bFollowUse)
	{
		CObject *pCenter = (CObject*)CObjectX::GetTop(OBJECT_PRIORITY_CENTER);	//�I�u�W�F�N�g�̐擪�|�C���^
		if (pCenter != nullptr)
		{
			//���݈ʒu�|�C���^�ɐ擪�|�C���^����
			CObject *pObject = pCenter;

			//���݈ʒu�|�C���^���g�p���̏ꍇ
			while (pObject != nullptr)
			{
				CObject::Object_Type objtype = pObject->GetType();

				if (objtype == CObject::TYPE_PLAYER)
				{
					D3DXVECTOR3 pos = pCenter->GetPos();
					D3DXVECTOR3 rot = pCenter->GetRot();

					m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					m_posRDest.x = pos.x + sinf(rot.x);
					//m_posRDest.y = pos.y + cosf(rot.y + D3DX_PI);
					m_posRDest.z = pos.z + cosf(rot.z);

					m_posVDest.x = pos.x + sinf(rot.x) ;
					//m_posVDest.y = pos.y - cosf(rot.x) * -m_fDistance;
					m_posVDest.z = pos.z + cosf(rot.z);

					m_posR.x += (m_posRDest.x - m_posR.x);
					//m_posR.y += (m_posRDest.y - m_posR.y) / 2;
					m_posR.z += (m_posRDest.z - m_posR.z);

					m_posV.x += (m_posVDest.x - m_posV.x);
					//m_posV.y += (m_posVDest.y - m_posV.y) / 2;
					m_posV.z += (m_posVDest.z - m_posV.z) - 400.0f;

					//m_rotDest.y = rot.y + D3DX_PI;
				}
				//���݈ʒu�|�C���^�Ɏ���|�C���^��������(�|�C���^��i�߂鏈��)
				pObject = pObject->GetNext();
			}
		}
	}
	//CDebugProc::Print("���݂̊p�xx : %f\n���݂̊p�xy : %f\n���݂̊p�xz : %f\n", m_rot.x, m_rot.y, m_rot.z);
}

//=====================================
//���͏���
//=====================================
void CCamera::Input()
{
	//�L�[�{�[�h�擾
	CInput *pCInput = CApplication::GetInput();

	//�J�����Ǐ]����؂�ւ�
	if (pCInput->GetKeyboardTrigger(DIK_F2))
	{
		m_bFollowUse = !m_bFollowUse;
	}

	//���_ & �����_�̓����ړ�
	if (pCInput->GetKeyboardPress(DIK_LEFT) == true)
	{//�J�������ړ�
		m_posV.x -= sinf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posR.x -= sinf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posV.z -= cosf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posR.z -= cosf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
	}
	else if (pCInput->GetKeyboardPress(DIK_RIGHT))
	{//�J�����E�ړ�
		m_posV.x += sinf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posR.x += sinf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posV.z += cosf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posR.z += cosf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
	}
	if (pCInput->GetKeyboardPress(DIK_UP) == true)
	{//�J�����O���ړ�
		m_posV.x += sinf(m_rot.y) * CAMERA_SPEAD;
		m_posR.x += sinf(m_rot.y) * CAMERA_SPEAD;
		m_posV.z += cosf(m_rot.y) * CAMERA_SPEAD;
		m_posR.z += cosf(m_rot.y) * CAMERA_SPEAD;
	}
	else if (pCInput->GetKeyboardPress(DIK_DOWN) == true)
	{//�J��������ړ�
		m_posV.x -= sinf(m_rot.y) * CAMERA_SPEAD;
		m_posR.x -= sinf(m_rot.y) * CAMERA_SPEAD;
		m_posV.z -= cosf(m_rot.y) * CAMERA_SPEAD;
		m_posR.z -= cosf(m_rot.y) * CAMERA_SPEAD;
	}
	if (pCInput->GetKeyboardPress(DIK_U) == true)
	{//�J������ړ�
		m_posV.y += 1;
		m_posR.y++;
		m_posV.x -= sinf(m_rot.y) * CAMERA_SPEAD;
		m_posR.x -= sinf(m_rot.y) * CAMERA_SPEAD;
		m_posV.z -= cosf(m_rot.y) * CAMERA_SPEAD;
		m_posR.z -= cosf(m_rot.y) * CAMERA_SPEAD;
	}
	else if (pCInput->GetKeyboardPress(DIK_O) == true)
	{//�J�������ړ�
		m_posV.y -= 1;
		m_posR.y--;
		m_posV.x += sinf(m_rot.y) * CAMERA_SPEAD;
		m_posR.x += sinf(m_rot.y) * CAMERA_SPEAD;
		m_posV.z += cosf(m_rot.y) * CAMERA_SPEAD;
		m_posR.z += cosf(m_rot.y) * CAMERA_SPEAD;
	}

	//�����_�̐���
	if (pCInput->GetKeyboardPress(DIK_Z) == true)
	{//�����
		m_rot.y -= 0.1f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	else if (pCInput->GetKeyboardPress(DIK_X) == true)
	{//�E���
		m_rot.y += 0.1f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}

	//���_�̐���
	if (pCInput->GetKeyboardPress(DIK_C) == true)
	{//�����
		m_rot.y += 0.1f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
	else if (pCInput->GetKeyboardPress(DIK_V) == true)
	{//�E���
		m_rot.y -= 0.1f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
}

//============================================================================
//�J�����̐ݒ菈��
//============================================================================
void CCamera::SetCamera(LPDIRECT3DDEVICE9 device)
{
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU
	);

	//�r���[�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//�A�X�y�N�g��
		CAMERA_NEAR,CAMERA_FAR
	);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//g_aCamera.bFollowUse = true;
}