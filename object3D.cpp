//=============================================================================
//
// �I�u�W�F�N�g3D
// Author : tanimoto kosuke
//
//=============================================================================
#include "object3D.h"
#include "renderer.h"
#include "application.h"

//=====================================
//�f�t�H���g�R���X�g���N�^
//=====================================
CObject3D::CObject3D(int priority) : CObject(priority), m_pVtxBuff(nullptr)
{

}

//=====================================
//�f�X�g���N�^
//=====================================
CObject3D::~CObject3D()
{

}

//=====================================
//����������
//=====================================
void CObject3D::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldmtx = D3DXMATRIX();

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
//�I������
//=====================================
void CObject3D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=====================================
//�X�V����
//=====================================
void CObject3D::Update()
{

}

//=====================================
//�`�揈��
//=====================================
void CObject3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_worldmtx);

	//�����𔽉f(YaW : y,Pitch : x,Roll : z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_worldmtx);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	////�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//pDevice->SetIndices(g_pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	////�|���S���̕`��
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMeshVertex, 0, m_nMeshPlimitive);
}

//=====================================
//UV�ݒ菈��
//=====================================
void CObject3D::SetUV()
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[0].pos.y = m_pos.y;
	pVtx[0].pos.z = m_pos.z + cosf(m_fAngle + m_rot.z) * m_fLength;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[1].pos.y = m_pos.y;
	pVtx[1].pos.z = m_pos.z + cosf(m_fAngle - m_rot.z) * m_fLength;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[2].pos.y = m_pos.y;
	pVtx[2].pos.z = m_pos.z - cosf(m_fAngle - m_rot.z) * m_fLength;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[3].pos.y = m_pos.y;
	pVtx[3].pos.z = m_pos.z - cosf(m_fAngle + m_rot.z) * m_fLength;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
//�F�ݒ菈��(���_��)
//=====================================
void CObject3D::SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3)
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col0;
	pVtx[1].col = col1;
	pVtx[2].col = col2;
	pVtx[3].col = col3;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
//�F�ݒ菈��(�S��)
//=====================================
void CObject3D::SetColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
//�I�u�W�F�N�g�ݒ菈��
//=====================================
void CObject3D::SetType(Object_Type type)
{
	CObject::SetType(type);
}

//=====================================
//�T�C�Y�ݒ菈��
//=====================================
void CObject3D::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_fAngle = atan2f(fWidth, fHeight);
	m_fLength = sqrtf((fWidth * fWidth) + (fHeight * fHeight)) / 2;

	SetUV();
}

//=====================================
//�I�u�W�F�N�g2D��������
//=====================================
CObject3D *CObject3D::Create(D3DXVECTOR3 pos)
{
	CObject3D *pObject3D = new CObject3D;	//�I�u�W�F�N�g2D�|�C���^

	if (pObject3D != nullptr)
	{
		pObject3D->Init();
		pObject3D->SetPos(pos);
	}
	return pObject3D;
}