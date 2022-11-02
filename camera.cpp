//=============================================================================
//
// camera.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "application.h"
#include "rendering.h"
#include "inputMouse.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "goal.h"
#include "message.h"
//#include "BoxHitbox.h"

//�R���X�g���N�^
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_
	m_DestPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̎��_
	m_DestPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̌���
	m_fDistance = 0.0f;				//���_����v���C���[�܂ł̋���
	m_fDistanceFocalPoint = 0.0f;		//�����_����v���C���[�܂ł̋���
	m_fLenght = 0.0f;
	m_nDelay = 0;
}

//�f�X�g���N�^
CCamera::~CCamera()
{

}

//����������
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_
	m_DestPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̎��_
	m_DestPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̌���
	m_fDistance = 0.0f;				//���_����v���C���[�܂ł̋���
	m_fDistanceFocalPoint = 0.0f;		//�����_����v���C���[�܂ł̋���
	m_fLenght = 0.0f;
	m_nDelay = 0;

	return S_OK;
}

//�I������
void CCamera::Uninit(void)
{

}

//�X�V����
void CCamera::Update(void)
{
#ifndef DEBUG

	if (CInputKeyboard::GetKeyboardPress(DIK_LEFT))
	{
		D3DXVECTOR3 v = m_posR - m_posV;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		float fDot = D3DXVec3Dot(&v, &unit);
		float fAngle = acosf(fDot);
		if (v.z < 0.0f)
		{
			fAngle *= -1.0f;
		}

		fAngle += D3DX_PI * 0.5f;
		m_posV.x += cosf(fAngle) * 5.0f;
		m_posV.z += sinf(fAngle) * 5.0f;
		m_posR.x += cosf(fAngle) * 5.0f;
		m_posR.z += sinf(fAngle) * 5.0f;

	}
	if (CInputKeyboard::GetKeyboardPress(DIK_UP))
	{
		D3DXVECTOR3 v = m_posR - m_posV;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		float fDot = D3DXVec3Dot(&v, &unit);
		float fAngle = acosf(fDot);
		if (v.z < 0.0f)
		{
			fAngle *= -1.0f;
		}

		m_posV.x += cosf(fAngle) * 5.0f;
		m_posV.z += sinf(fAngle) * 5.0f;
		m_posR.x += cosf(fAngle) * 5.0f;
		m_posR.z += sinf(fAngle) * 5.0f;
	}
	if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT))
	{
		D3DXVECTOR3 v = m_posR - m_posV;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		float fDot = D3DXVec3Dot(&v, &unit);
		float fAngle = acosf(fDot);
		if (v.z < 0.0f)
		{
			fAngle *= -1.0f;
		}

		fAngle += -D3DX_PI * 0.5f;
		m_posV.x += cosf(fAngle) * 5.0f;
		m_posV.z += sinf(fAngle) * 5.0f;
		m_posR.x += cosf(fAngle) * 5.0f;
		m_posR.z += sinf(fAngle) * 5.0f;
	}
	if (CInputKeyboard::GetKeyboardPress(DIK_DOWN))
	{
		D3DXVECTOR3 v = m_posR - m_posV;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		float fDot = D3DXVec3Dot(&v, &unit);
		float fAngle = acosf(fDot);
		if (v.z < 0.0f)
		{
			fAngle *= -1.0f;
		}

		fAngle += D3DX_PI;
		m_posV.x += cosf(fAngle) * 5.0f;
		m_posV.z += sinf(fAngle) * 5.0f;
		m_posR.x += cosf(fAngle) * 5.0f;
		m_posR.z += sinf(fAngle) * 5.0f;
	}

	DIMOUSESTATE* pMouse = CApplication::GetMouse()->GetMouseState();

	if (pMouse->lY > 0)
	{
		if (m_posR.y > m_posV.y - 150.0f)
		{
			m_posR.y += -5.0f;
		}
	}
	else if (pMouse->lY < 0)
	{
		if (m_posR.y < m_posV.y + 150.0f)
		{
			m_posR.y += 5.0f;
		}
	}
	if (pMouse->lX > 0)
	{
		m_rot.y += -D3DX_PI * 0.005f;
	}
	else if (pMouse->lX < 0)
	{
		m_rot.y += D3DX_PI * 0.005f;
	}

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= 2.0f * D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += 2.0f * D3DX_PI;
	}

	m_posR.x = m_posV.x + m_fLenght * cosf(m_rot.y);
	m_posR.z = m_posV.z + m_fLenght * sinf(m_rot.y);

	CDebugProc::Print("\nPosV: %f, %f, %f\nPosR: %f, %f, %f", m_posV.x, m_posV.y, m_posV.z, m_posR.x, m_posR.y, m_posR.z);

#endif // DEBUG

	if (CMessage::GetStart())
	{
		D3DXVECTOR3 v = m_posR - m_posV;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		float fDot = D3DXVec3Dot(&v, &unit);
		float fAngle = acosf(fDot);
		if (v.z < 0.0f)
		{
			fAngle *= -1.0f;
		}

		m_posV.x += cosf(fAngle) * 1.0f;
		m_posV.z += sinf(fAngle) * 1.0f;
		m_posR.x += cosf(fAngle) * 1.0f;
		m_posR.z += sinf(fAngle) * 1.0f;
	}

	if (m_posV.z >= 750.0f)
	{
		m_posV.z = 750.0f;

		//CGoal::SetGoal(true);
	}
}

//�ݒ菈��
void CCamera::Set(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		50000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

const D3DXVECTOR3 CCamera::GetPos(void)
{
	return m_posV;
}

const D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

//�J�����̌����̎擾����
const D3DXVECTOR3 CCamera::GetDirection(void)
{
	D3DXVECTOR3 dir = m_posR - m_posV;
	D3DXVec3Normalize(&dir, &dir);

	return dir;
}

const D3DXVECTOR3 CCamera::GetFocalPoint(void)
{
	return m_posR;
}


void CCamera::SetFocalPoint(const D3DXVECTOR3 pos)
{
	m_posR = pos;
}

//���_�����_�̐ݒ�
void CCamera::SetPos(const D3DXVECTOR3 posV, const D3DXVECTOR3 posR)
{
	m_posV = posV;
	m_posR = posR;
}

CCamera* CCamera::Create(D3DXVECTOR3 pos, D3DXVECTOR3 focalPoint)
{
	CCamera* pCamera = new CCamera;

	if (FAILED(pCamera->Init()))
	{
		return nullptr;
	}

	pCamera->m_posV = pos;
	pCamera->m_posR = focalPoint;

	D3DXVECTOR3 v = pCamera->m_posR - pCamera->m_posV;
	D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&v, &v);

	pCamera->m_rot.y = acosf(D3DXVec3Dot(&v, &unit));
	if (pCamera->m_posR.z < pCamera->m_posV.z)
	{
		pCamera->m_rot.y *= -1.0f;
	}

	pCamera->m_fLenght = sqrtf(((pCamera->m_posR.x - pCamera->m_posV.x) * (pCamera->m_posR.x - pCamera->m_posV.x)) + ((pCamera->m_posR.z - pCamera->m_posV.z) * (pCamera->m_posR.z - pCamera->m_posV.z)));
	return pCamera;
}