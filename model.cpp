//============================================================================
//
// ���f���̏���
// Author:�J�{�N��
//
//============================================================================
#include "model.h"		//�쐬����player.h���C���N���[�h����
#include "input.h"		//�쐬����input.h���C���N���[�h����
#include "camera.h"		//�쐬����camera.h���C���N���[�h����
#include "application.h"
#include "renderer.h"
#include "texture.h"
#include "debugproc.h"
#include "light.h"

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CModel::CModel()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CModel::~CModel()
{

}

//=====================================
//����������
//=====================================
void CModel::Init(char *xFail)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���(��)
	D3DXLoadMeshFromX(
		//"Data\\Model\\00_niwamaru_body.x",
		(LPCSTR)xFail,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh
	);

	m_pParent = nullptr;
}

//=====================================
//����������
//=====================================
void CModel::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldmtx = D3DXMATRIX();
}

//=====================================
//�I������
//=====================================
void CModel::Uninit()
{
	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=====================================
//�X�V����
//=====================================
void CModel::Update()
{

}


//=====================================
//�`�揈��
//=====================================
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxParent;						//�e�p�}�g���N�X
	D3DMATERIAL9 matDef;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_worldmtx);
	
	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	//�����𔽉f(YaW : y,Pitch : x,Roll : z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetWorldMtx();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//�e���f���̃}�g���b�N�X�Ƃ̊|���Z
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxParent);

	//++++++++++++++++++++++++++
	// ���ʓ��e�@
	//++++++++++++++++++++++++++
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;

	//�V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	D3DLIGHT9 light = CApplication::GetLight()->GetLight();
	vecLight = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	D3DXMatrixMultiply(&mtxShadow, &m_worldmtx, &mtxShadow);

	//�V���h�E�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//���݂̃}�e���A���̃|�C���^���擾
	D3DXMATERIAL *pMatShadow = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//�e�N�X�`���̓ǂݏo��
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�e�p�}�g���b�N�X����
		D3DMATERIAL9 matShadow = pMatShadow[nCntMat].MatD3D;

		//�e�̐F�����F�ɂ���
		matShadow.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&matShadow);
		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_worldmtx);

	//���݂̃}�e���A���̃|�C���^���擾
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//�e�N�X�`���̓ǂݏo��
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ێ����Ă��}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=====================================
//���f����������
//=====================================
CModel *CModel::Create(D3DXVECTOR3 pos, char *xFail)
{
	CModel *pModel = new CModel;		//�v���C���[�|�C���^

	if (pModel != nullptr)
	{
		pModel->Init(xFail);
		pModel->SetPos(pos);
	}
	return pModel;
}