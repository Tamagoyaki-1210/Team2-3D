//=============================================================================
//
// �I�u�W�F�N�g3D
// Author : tanimoto kosuke
//
//=============================================================================
#include "objectX.h"
#include "renderer.h"
#include "application.h"
#include "light.h"

//=====================================
//�f�t�H���g�R���X�g���N�^
//=====================================
CObjectX::CObjectX(int list) : CObject(list)
{

}

//=====================================
//�f�X�g���N�^
//=====================================
CObjectX::~CObjectX()
{

}

//=====================================
//����������
//=====================================
void CObjectX::Init(char *xFail)
{
	CObjectX::Init();

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
}
//=====================================
//����������
//=====================================
void CObjectX::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldmtx = D3DXMATRIX();
}

//=====================================
//�I������
//=====================================
void CObjectX::Uninit()
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
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=====================================
//�X�V����
//=====================================
void CObjectX::Update()
{

}

//=====================================
//�`�揈��
//=====================================
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxParent;						//�e�p�}�g���N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_worldmtx);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	//�����𔽉f(YaW : y,Pitch : x,Roll : z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y + m_fPalentY, m_pos.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxTrans);

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
		matShadow.Diffuse = D3DXCOLOR(0.0f, 0.0f ,0.0f, 1.0f);

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
//�I�u�W�F�N�g�ݒ菈��
//=====================================
void CObjectX::SetType(Object_Type type)
{
	CObject::SetType(type);
}

//=====================================
//�I�u�W�F�N�g�ݒ菈��
//=====================================
void CObjectX::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_fAngle = atan2f(fWidth, fHeight);
	m_fLength = sqrtf((fWidth * fWidth) + (fHeight * fHeight)) / 2;
}

//=====================================
//�I�u�W�F�N�g2D��������
//=====================================
CObjectX *CObjectX::Create(D3DXVECTOR3 pos, char *xFail)
{
	CObjectX *pObjectX = new CObjectX;	//�I�u�W�F�N�g2D�|�C���^

	if (pObjectX != nullptr)
	{
		pObjectX->Init(xFail);
		pObjectX->SetPos(pos);
	}

	return pObjectX;
}