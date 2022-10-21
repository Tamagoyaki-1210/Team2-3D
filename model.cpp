//=============================================================================
//
// model.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"
#include "application.h"
#include "object2D.h"
#include "rendering.h"
#include "directionalLight.h"

LPD3DXMESH		CModel::m_pMeshAll[MODEL_MAX] = {};					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER	CModel::m_pBuffMatAll[MODEL_MAX] = {};				//�}�e���A�����ւ̃|�C���^
DWORD			CModel::m_nNumMatAll[MODEL_MAX] = {};				//�}�e���A�����̐�
std::vector <LPDIRECT3DTEXTURE9>     CModel::m_vModelTexture[CModel::MODEL_MAX];		//���f���̃e�N�X�`���ւ̃|�C���^�̃x�N�g��

char*			CModel::m_pModelPass[MODEL_MAX] =
{
	{"data\\MODELS\\Tear.x"},
	{"data\\MODELS\\CrobatBody.x"},
	{ "data\\MODELS\\CrobatLeftWing.x" },
	{ "data\\MODELS\\CrobatRightWing.x" },
	{ "data\\MODELS\\CrobatLeftWingSmall.x" },
	{ "data\\MODELS\\CrobatRightWingSmall.x" }
};

//�R���X�g���N�^
CModel::CModel()
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;								//���f���̒��_���W�̍ŏ��l�ƍő�l
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = CModel::MODEL_JEWEL_TEAR;
}

CModel::CModel(const int nPriority) : CObject::CObject(nPriority)
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;								//���f���̒��_���W�̍ŏ��l�ƍő�l
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = CModel::MODEL_JEWEL_TEAR;
}

//�f�X�g���N�^
CModel::~CModel()
{

}

//����������
HRESULT CModel::Init(void)
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

	/*std::vector <LPDIRECT3DTEXTURE9> v;

	v.clear();

	LPDIRECT3DTEXTURE9 pText = CObject_2D::GetTexturePointer(CObject::TextureNumbers);
	
	v.push_back(nullptr);
	v.push_back(pText);

	LPDIRECT3DTEXTURE9 a = v.data()[0];
	LPDIRECT3DTEXTURE9 b = v.data()[1];*/

	return S_OK;
}

//�I������
void CModel::Uninit(void)
{
	
}

//�X�V����
void CModel::Update(void)
{
	
}

//�`�揈��
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxShadow;							//�v�Z�p�}�g���b�N�X
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
		pDevice->SetTexture(0, m_vModelTexture[m_type].data()[nCntMat]);

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

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_vModelTexture[m_type].data()[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ێ��������}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//�ʒu�̐ݒ菈��
void CModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

void CModel::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

const D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//�|���S���̃T�C�Y�̎擾����
const D3DXVECTOR2 CModel::GetSize(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}





//���f�����̎擾����
void CModel::GetModel(ModelType type, LPD3DXMESH* pMesh, LPD3DXBUFFER* pBuffMat, DWORD* numMat)
{
	*pMesh = m_pMeshAll[type];
	*pBuffMat = m_pBuffMatAll[type];
	*numMat = m_nNumMatAll[type];
}

//���f���S���̓ǂݍ��ݏ���
void CModel::LoadAllModels(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < CModel::MODEL_MAX; nCnt++)
	{
		m_vModelTexture[nCnt].clear();

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_pModelPass[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMatAll[nCnt],
			NULL,
			&m_nNumMatAll[nCnt],
			&m_pMeshAll[nCnt]);

		D3DXMATERIAL *pMat = nullptr;

		//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMatAll[nCnt]->GetBufferPointer();

		for (int a = 0; a < (int)m_nNumMatAll[nCnt]; a++)
		{
			LPDIRECT3DTEXTURE9 pTex = nullptr;

			D3DXCreateTextureFromFile(pDevice, pMat->pTextureFilename, &pTex);
			pMat++;
			m_vModelTexture[nCnt].push_back(pTex);
		}
	}	
}

//���f���S���̔j������
void CModel::DestroyAllModels(void)
{
	for (int nCnt = 0; nCnt < CModel::MODEL_MAX; nCnt++)
	{
		if (m_pMeshAll[nCnt] != nullptr)
		{
			m_pMeshAll[nCnt]->Release();
			m_pMeshAll[nCnt] = nullptr;
		}

		if (m_pBuffMatAll[nCnt] != nullptr)
		{
			m_pBuffMatAll[nCnt]->Release();
			m_pBuffMatAll[nCnt] = nullptr;
		}
	}
}

void CModel::GetTextures(std::vector <LPDIRECT3DTEXTURE9>& vTex, CModel::ModelType type)
{
	vTex.clear();

	for (int nCnt = 0; nCnt < (int)m_nNumMatAll[type]; nCnt++)
	{
		vTex.push_back(m_vModelTexture[type].data()[nCnt]);
	}
}

//��������
CModel* CModel::Create(ModelType type, D3DXVECTOR3 pos)
{
	CModel* pModel = new CModel(3);

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_LastPos = pos;
	pModel->m_move = Vec3Null;
	pModel->m_rot = Vec3Null;
	pModel->m_pMesh = m_pMeshAll[type];
	pModel->m_pBuffMat = m_pBuffMatAll[type];
	pModel->m_nNumMat = m_nNumMatAll[type];
	pModel->m_type = type;

	return pModel;
}

CModel* CModel::Create(ModelType type, D3DXVECTOR3 pos, const int nPriority)
{
	CModel* pModel = new CModel(nPriority);

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_LastPos = pos;
	pModel->m_move = Vec3Null;
	pModel->m_rot = Vec3Null;
	pModel->m_pMesh = m_pMeshAll[type];
	pModel->m_pBuffMat = m_pBuffMatAll[type];
	pModel->m_nNumMat = m_nNumMatAll[type];
	pModel->m_type = type;

	return pModel;
}