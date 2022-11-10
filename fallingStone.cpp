//=============================================================================
//
// fallingStone.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fallingStone.h"
#include "CylinderHitbox.h"
#include "application.h"
#include "rendering.h"
#include "meshfield.h"
#include "camera.h"


CFallingStone::CFallingStone()
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_shadowPosY = 0.0f;
	m_fBound = 0.0f;								//�e�̃G���A�̕�
	m_fDir = 0.0f;									//�����̕���
	m_frameRot = Vec3Null;							//��]���x
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = (CModel::ModelType)0;
	m_vModelTexture.clear();
	m_pHitbox = nullptr;
}

CFallingStone::~CFallingStone()
{

}

//����������
HRESULT CFallingStone::Init(void)
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_shadowPosY = 0.0f;
	m_fBound = 0.0f;								//�e�̃G���A�̕�
	m_fDir = 1.0f;									//�����̕���
	m_frameRot = Vec3Null;							//��]���x
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = (CModel::ModelType)0;
	m_vModelTexture.clear();
	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CFallingStone::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
}

//�X�V����
void CFallingStone::Update(void)
{
	if (m_move != Vec3Null)
	{
		m_pos += m_move;
	}

	if (m_move.y >= -7.0f)
	{
		m_move.y += -0.5f;
	}

	if (m_frameRot != Vec3Null)
	{
		m_rot += m_frameRot;
	}

	if (CMeshfield::FieldInteraction(this))
	{
		if (m_move.x < 1.0f)
		{
			m_move.x = 3.0f * m_fDir;
			m_move.y = 7.0f;
			StartRotation(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.01f * m_fDir));
		}
	}

	if (m_pos.y <= -500.0f)
	{
		Release();
	}

	if (m_pHitbox != nullptr)
	{
		//m_pHitbox->SetPos(m_pos);
		m_pHitbox->Update();

		if (m_pHitbox->GetCollisionState())
		{
			m_pHitbox->SetCollisionState(false);
			m_move.x = 3.0f * m_fDir;
			m_move.y = 7.0f;
			StartRotation(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.01f * m_fDir));
		}
	}

	if (GetPos().z < CApplication::GetCamera()->GetPos().z - 100.0f)
	{
		Release();
	}
}

//�`�揈��
void CFallingStone::Draw(void)
{
	if (GetPos().z < CApplication::GetCamera()->GetPos().z + 650.0f)
	{
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//�f�o�C�X�̎擾
		D3DXMATRIX mtxRot, mtxTrans, mtxShadow;							//�v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef;									//���݂̃}�e���A���ۑ��p
		D3DXMATERIAL *pMat;										//�}�e���A���f�[�^�ւ̃|�C���^
		D3DXVECTOR4 vecLight;
		D3DXVECTOR3 pos, Normal;
		D3DXPLANE planeField;


		D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		D3DXVec3Normalize(&dir, &dir);

		vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);

		pos = D3DXVECTOR3(0.0f, m_shadowPosY, 0.0f);

		if (m_pos.y < m_shadowPosY - 10.0f || (m_pos.x > m_spawnPos.x + m_fBound && m_fDir > 0.0f) || (m_pos.x < m_spawnPos.x - m_fBound && m_fDir < 0.0f))
		{
			pos.y = -5000.0f;
		}

		Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);
		D3DXMatrixIdentity(&mtxShadow);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		D3DXPlaneFromPointNormal(&planeField, &pos, &Normal);
		D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

		D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

		//���݂̃}�e���A����ێ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			D3DXCOLOR col = pMat[nCntMat].MatD3D.Diffuse;

			pMat[nCntMat].MatD3D.Diffuse.r = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.g = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.b = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.a = 0.5f;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);

			pMat[nCntMat].MatD3D.Diffuse.r = col.r;
			pMat[nCntMat].MatD3D.Diffuse.g = col.g;
			pMat[nCntMat].MatD3D.Diffuse.b = col.b;
			pMat[nCntMat].MatD3D.Diffuse.a = col.a;
		}


		//�X�e���V���o�b�t�@��L���ɂ���
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		//�X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ�
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

		//�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		//�X�e���V���e�X�g�̔�r���@�̐ݒ�
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

		//�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

		pMat = nullptr;

		//�ێ��������}�e���A����߂�
		pDevice->SetMaterial(&matDef);


		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���݂̃}�e���A����ێ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}

		//�ێ��������}�e���A����߂�
		pDevice->SetMaterial(&matDef);

		//�X�e���V���o�b�t�@�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

		pMat = nullptr;

		//�ێ��������}�e���A����߂�
		pDevice->SetMaterial(&matDef);


		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���݂̃}�e���A����ێ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}

		//�ێ��������}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//�ʒu�̐ݒ菈��
void CFallingStone::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CFallingStone::GetPos(void)
{
	return m_pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CFallingStone::GetSize(void)
{
	return Vec2Null;
}



void CFallingStone::StartRotation(const D3DXVECTOR3 frameRot)
{
	m_frameRot = frameRot;
}


void CFallingStone::StopRotating(void)
{
	m_frameRot = Vec3Null;
}

void CFallingStone::SetDirection(const float fLateralDirection)
{
	if (fLateralDirection >= 0)
	{
		m_fDir = 1.0f;
	}
	else
	{
		m_fDir = -1.0f;
	}
}






//��������
CFallingStone* CFallingStone::Create(CModel::ModelType type, D3DXVECTOR3 pos, const D3DXVECTOR3 spawnPos, const float ShadowHeight, const float fBound, const float fDir)
{
	CFallingStone* pModel = new CFallingStone;

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_rot = Vec3Null;
	pModel->m_LastPos = pos;
	pModel->m_type = type;
	pModel->m_shadowPosY = ShadowHeight;
	pModel->m_fBound = fBound;
	pModel->m_fDir = fDir;
	pModel->m_spawnPos = spawnPos;

	CModel::GetModel(type, &pModel->m_pMesh, &pModel->m_pBuffMat, &pModel->m_nNumMat);
	CModel::GetTextures(pModel->m_vModelTexture, type);

	pModel->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(20.0f, 40.0f, 20.0f), CHitbox::TYPE_OBSTACLE, -30, pModel, CHitbox::EFFECT_LAUNCH);

	return pModel;
}