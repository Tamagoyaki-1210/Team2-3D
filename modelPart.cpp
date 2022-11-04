//=============================================================================
//
// modelPart.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "modelPart.h"
#include "application.h"
#include "rendering.h"
#include "directionalLight.h"

//�R���X�g���N�^
CModelPart::CModelPart()
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;							//���f���̒��_���W�̍ŏ��l�ƍő�l
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = CModel::MODEL_BODY;
	m_pParent = nullptr;
	m_vModelTexture.clear();
	m_vCol.clear();
}

//�f�X�g���N�^
CModelPart::~CModelPart()
{

}

//����������
HRESULT CModelPart::Init(void)
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;							//���f���̒��_���W�̍ŏ��l�ƍő�l
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = CModel::MODEL_BODY;
	m_pParent = nullptr;
	m_vModelTexture.clear();
	m_vCol.clear();

	return S_OK;
}

//�I������
void CModelPart::Uninit(void)
{
	m_vCol.clear();
}

//�X�V����
void CModelPart::Update(void)
{

}

//�`�揈��
void CModelPart::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxShadow, mtxParent;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;									//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;										//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, Normal;
	D3DXPLANE planeField;

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMatrix();
	}

	D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
	D3DXVec3Normalize(&dir, &dir);

	vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);
	pos = D3DXVECTOR3(0.0f, -149.0f, 0.0f);
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

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;

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

		D3DXCOLOR c = {};
		bool bCol = false;

		for (int i = 0; i < (int)m_vCol.size(); i++)
		{
			if (m_vCol.data()[i].nMatNumber == nCntMat)
			{
				bCol = true;
				c = pMat[nCntMat].MatD3D.Diffuse;
				pMat[nCntMat].MatD3D.Diffuse = m_vCol.data()[i].col;
				break;
			}
		}

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

		if (bCol)
		{
			pMat[nCntMat].MatD3D.Diffuse = c;
		}
	}

	//�ێ��������}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//�`�揈��
void CModelPart::Draw(D3DXMATRIX mtxParent)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxShadow;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;									//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;										//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, Normal;
	D3DXPLANE planeField;

	D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
	D3DXVec3Normalize(&dir, &dir);

	vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);
	pos = D3DXVECTOR3(0.0f, -149.0f, 0.0f);
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

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;

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

		D3DXCOLOR c = {};
		bool bCol = false;

		for (int i = 0; i < (int)m_vCol.size(); i++)
		{
			if (m_vCol.data()[i].nMatNumber == nCntMat)
			{
				bCol = true;
				c = pMat[nCntMat].MatD3D.Diffuse;
				pMat[nCntMat].MatD3D.Diffuse = m_vCol.data()[i].col;
				break;
			}
		}

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

		if (bCol)
		{
			pMat[nCntMat].MatD3D.Diffuse = c;
		}
	}

	//�ێ��������}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	pDevice->SetTexture(0, nullptr);
}

//�e�̐ݒ菈��
void CModelPart::SetParent(CModelPart* pParent)
{
	m_pParent = pParent;
}

//�e�̎擾����
CModelPart* CModelPart::GetParent(void)
{
	return m_pParent;
}

//�ʒu�̐ݒ菈��
void CModelPart::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CModelPart::GetPos(void)
{
	return m_pos;
}

//�����̐ݒ菈��
void CModelPart::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//�����̎擾����
const D3DXVECTOR3 CModelPart::GetRot(void)
{
	return m_rot;
}

//�T�C�Y�̎擾����
const D3DXVECTOR3 CModelPart::GetSize(void)
{
	return Vec3Null;
}

D3DXMATRIX CModelPart::GetMatrix(void)
{
	return m_mtxWorld;
}

//�J�[���[�̐ݒ菈��
void CModelPart::SetModelColor(const int nNumMat, const D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < (int)m_vCol.size(); nCnt++)
	{
		if (m_vCol.data()[nCnt].nMatNumber == nNumMat)
		{
			CModel::ModelColor mCol = {};
			mCol.nMatNumber = nNumMat;
			mCol.col = col;
			m_vCol.data()[nCnt] = mCol;
			return;
		}
	}

	CModel::ModelColor mCol = {};
	mCol.nMatNumber = nNumMat;
	mCol.col = col;

	m_vCol.push_back(mCol);
}







//��������
CModelPart* CModelPart::Create(CModel::ModelType type, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CModelPart* pModel = new CModelPart;

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_rot = rot;
	pModel->m_LastPos = pos;
	pModel->m_type = type;

	CModel::GetModel(type, &pModel->m_pMesh, &pModel->m_pBuffMat, &pModel->m_nNumMat);
	CModel::GetTextures(pModel->m_vModelTexture, type);

	return pModel;
}