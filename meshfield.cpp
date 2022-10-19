//============================================================================
//
//���b�V���|���S���̏���[meshfield.cpp] (�t�@�C���w�b�_�R�����g)
//Author:�J�{�N��
//============================================================================
#include <assert.h>
#include <stdio.h>
#include "application.h"
#include "texture.h"
#include "renderer.h"
#include "meshfield.h"	//�쐬����meshfield.h���C���N���[�h����
#include "input.h"		//�쐬����input.h���C���N���[�h����
#include "debugproc.h"

//****************************************************************************
//�O���[�o���ϐ�
//****************************************************************************
//LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CMeshField::CMeshField(int priority) : CObject(priority), m_pVtxBuff(nullptr), m_pIdxBuff(nullptr)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CMeshField::~CMeshField()
{

}

//============================================================================
//���b�V���|���S���̏���������
//============================================================================
void CMeshField::Init()
{
	m_nDebug = 0;
	m_nMeshX = MAX_MESHFIELD;
	m_nMeshZ = MAX_MESHFIELD;

	//���b�V��(��)���v���v�Z�� = (���b�V���ő吔.�� * ���b�V���ő吔.�c * 2) + �k�ރ|���S����((���b�V���ő吔.�c - 1) * 4)
	m_nMeshPlimitive = (m_nMeshX * m_nMeshZ * 2) + ((m_nMeshZ - 1) * 4);

	//���_�o�b�t�@���v���v�Z�� = (���b�V���ő吔.�� + 1) * (���b�V���ő吔.�c + 1)
	m_nMeshVertex = (m_nMeshX + 1) * (m_nMeshZ + 1);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_worldmtx = D3DXMATRIX();

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nMeshVertex,
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

	//�C���f�b�N�X���v���v�Z�� = ((���b�V���ő吔.�� + 1) * (���b�V���ő吔.�c * 2)) + �k�ރ|���S���ő吔((���b�V���ő吔.�c - 1) * 2)
	m_nMeshIndex = ((m_nMeshX + 1) * (m_nMeshZ * 2)) + ((m_nMeshZ - 1) * 2);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nMeshIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	m_fWidth = MESHFIELD_WIDTH;
	m_fHeight = MESHFIELD_HEIGHT;

	//�I�u�W�F�N�g�ݒ菈��
	SetType(CObject::TYPE_OBSTACLE);
	SetSize(m_fWidth, m_fHeight);

	SetMesh();
}

//============================================================================
//���b�V���|���S���̏I������
//============================================================================
void CMeshField::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//============================================================================
//���b�V���|���S���̍X�V����
//============================================================================
void CMeshField::Update()
{
	//�L�[�{�[�h�擾
	CInput *pInput = CApplication::GetInput();

	//508
	if (pInput->GetKeyboardPress(DIK_B) == true)
	{
		m_nDebug++;
	}

	if (pInput->GetKeyboardTrigger(DIK_N) == true)
	{
		m_nDebug++;
	}
	else if(pInput->GetKeyboardTrigger(DIK_M) == true)
	{
		m_nDebug--;
	}
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	CDebugProc::Print("�f�o�b�O���l : %d\n���݂̈ʒux : %f\n���݂̈ʒuy : %f\n���݂̈ʒuz : %f\n", m_nDebug, pVtx[m_nDebug].pos.x, pVtx[m_nDebug].pos.y, pVtx[m_nDebug].pos.z);
	
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================================================================
//���b�V���|���S���̕`�揈��
//============================================================================
void CMeshField::Draw()
{
	CApplication::GetTexture()->TextureType(CTexture::TYPE_MESHFIELD_01);

	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_worldmtx);

	//�����𔽉f(YaW : y,Pitch : x,Roll : z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxTrans);

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_worldmtx);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nMeshVertex, 0, m_nMeshPlimitive);
	CApplication::GetTexture()->TextureClear();
}

//============================================================================
//���b�V���|���S���̓����蔻�菈��
//============================================================================
bool CMeshField::FieldCollision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld)
{
	m_fVecNor = 0.0f;
	bool bRange = false;

	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < m_nMeshIndex - 2; nCnt++)
	{
		//3�̒��_
		D3DXVECTOR3 pos1 = pVtx[pIdx[nCnt]].pos;
		D3DXVECTOR3 pos2 = pVtx[pIdx[nCnt + 1]].pos;
		D3DXVECTOR3 pos3 = pVtx[pIdx[nCnt + 2]].pos;

		if (pos1 == pos2 || pos2 == pos3 || pos1 == pos3)
		{
			continue;
		}

		//�|���S���̒��_�ƃv���C���[�̈ʒu����
		D3DXVECTOR3 VecB1 = pos - pos1;
		D3DXVECTOR3 VecB2 = pos - pos2;
		D3DXVECTOR3 VecB3 = pos - pos3;

		if (nCnt % 2 != 0)
		{
			//�|���S�����`������3��
			D3DXVECTOR3 VecA1 = pos2 - pos1;
			D3DXVECTOR3 VecA2 = pos3 - pos2;
			D3DXVECTOR3 VecA3 = pos1 - pos3;

			//3�ӂƃv���C���[�ʒu�����̊O��
			float fCross1 = (VecA1.x * VecB1.z) - (VecA1.z * VecB1.x);
			float fCross2 = (VecA2.x * VecB2.z) - (VecA2.z * VecB2.x);
			float fCross3 = (VecA3.x * VecB3.z) - (VecA3.z * VecB3.x);

			//3�̊O�ς��S��+ ���� �S��-�̏ꍇ(���b�V���t�B�[���h�͈͓̔��̏ꍇ)
			if ((fCross1 >= 0 && fCross2 >= 0 && fCross3 >= 0)
				|| (fCross1 < 0 && fCross2 < 0 && fCross3 < 0))
			{
				bRange = true;
				//1�̒��_����2�̒��_�܂ł̕ӂ�2���
				D3DXVECTOR3 VecC1 = pos2 - pos1;
				D3DXVECTOR3 VecC2 = pos3 - pos1;

				//�ʖ@���x�N�g��
				D3DXVECTOR3 VecNor;

				//2�̕ӂ̊O�ς���ʖ@���x�N�g�������
				D3DXVec3Cross(&VecNor, &VecC1, &VecC2);
				//���K��
				D3DXVec3Normalize(&VecNor, &VecNor);

				//�ʖ@���x�N�g���ƃv���C���[�ʒu�����̓��ς���v���C���[�̈ʒu.y���t�Z�����l
 				m_fVecNor = pos1.y - (((pos.x - pos1.x) * VecNor.x) + ((pos.z - pos1.z) * VecNor.z)) / VecNor.y;
			}
		}
		else
		{
			//�|���S�����`������3��
			D3DXVECTOR3 VecA1 = pos1 - pos2;
			D3DXVECTOR3 VecA2 = pos2 - pos3;
			D3DXVECTOR3 VecA3 = pos3 - pos1;

			//3�ӂƃv���C���[�ʒu�����̊O��
			float fCross1 = (VecA1.x * VecB1.z) - (VecA1.z * VecB1.x);
			float fCross2 = (VecA2.x * VecB2.z) - (VecA2.z * VecB2.x);
			float fCross3 = (VecA3.x * VecB3.z) - (VecA3.z * VecB3.x);

			//3�̊O�ς��S��+ ���� �S��-�̏ꍇ(���b�V���t�B�[���h�͈͓̔��̏ꍇ)
			if ((fCross1 >= 0 && fCross2 >= 0 && fCross3 >= 0)
				|| (fCross1 < 0 && fCross2 < 0 && fCross3 < 0))
			{
				bRange = true;

				D3DXVECTOR3 VecC1 = pos2 - pos1;
				D3DXVECTOR3 VecC2 = pos3 - pos1;

				//�ʖ@���x�N�g��
				D3DXVECTOR3 VecNor;
				//�O��
				D3DXVec3Cross(&VecNor, &VecC1, &VecC2);
				//���K��
				D3DXVec3Normalize(&VecNor, &VecNor);

				//�ʖ@���x�N�g���ƃv���C���[�ʒu�����̓��ς���v���C���[�̈ʒu.y���t�Z�����l
				m_fVecNor = pos1.y - (((pos.x - pos1.x) * VecNor.x) + ((pos.z - pos1.z) * VecNor.z)) / VecNor.y;
			}
		}
	}
	//�C���f�b�N�X�̃A�����b�N
	m_pIdxBuff->Unlock();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//if (pos->x < posMesh.x + (m_nMeshX * (MESHFIELD_WIDTH / 2))
	//	&& pos->x > posMesh.x - (m_nMeshX * (MESHFIELD_WIDTH / 2))
	//	&& pos->z < posMesh.z + (m_nMeshZ * (MESHFIELD_HEIGHT / 2))
	//	&& pos->z > posMesh.z - (m_nMeshZ * (MESHFIELD_HEIGHT / 2)))
	//{//���ɏ���Ă���ꍇ
	//	if (pos->y <= posMesh.y && posOld->y >= posMesh.y)
	//	{//���������b�V����荂���ꍇ
	//		pos->y = posMesh.y;
	//		bIsGround = true;
	//	}
	//}
	return bRange;
}

//=====================================
//���b�V���ݒ菈��
//=====================================
void CMeshField::SetMesh()
{
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMeshZ = 0; nCntMeshZ < m_nMeshZ + 1; nCntMeshZ++)
	{
		for (int nCntMeshX = 0; nCntMeshX < m_nMeshX + 1; nCntMeshX++)
		{
			//���݂̒��_ = nVtx[���b�V����x�� + (���b�V����z�� * (���b�V���ő吔.�� + 1))]
			int nVtx = nCntMeshX + (nCntMeshZ * (m_nMeshX + 1));
			//�I�𒆒��_�̈ʒu�ݒ�
			pVtx[nVtx].pos = D3DXVECTOR3(
				(float)((nCntMeshX * MESHFIELD_WIDTH) - (m_nMeshX * MESHFIELD_WIDTH / 2)),		//�e���_�̉��ʒu = (���b�V����.�� * ����) - (���b�V���ő吔.�� * �����̔���)
				(float)(rand() % 100),
				//0.0f,
				(float)((-nCntMeshZ * MESHFIELD_HEIGHT) + (m_nMeshZ * MESHFIELD_HEIGHT / 2))	//�e00���_�̏c�ʒu = -(���b�V����.�c * ����) + (���b�V���ő吔.�c * �����̔���)
				);

			//�I�𒆒��_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[nVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//�I�𒆒��_�̃J���[�̐ݒ�
			pVtx[nVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�I�𒆒��_�̃e�N�X�`�����W�̐ݒ�
			pVtx[nVtx].tex = D3DXVECTOR2((float)nCntMeshX, (float)nCntMeshZ);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nDeg = 0;		//�k�ރ|���S��

	//�C���f�b�N�X�̐ݒ�
	for (int nCntMeshZ = 0; nCntMeshZ < m_nMeshZ; nCntMeshZ++)
	{//z���J�E���g
		if(nCntMeshZ != 0)
		{//�k�ރ|���S�����K�v�ȏꍇ
			pIdx[(((m_nMeshX + 1) * 2) * nCntMeshZ) + nDeg] = (WORD)(((m_nMeshX + 1) * nCntMeshZ) - 1);		//pIdx[���Ō�̃C���f�b�N�X] = x,z���v�Z
			pIdx[(((m_nMeshX + 1) * 2) * nCntMeshZ) + nDeg + 1] = (WORD)((m_nMeshX + 1) * (nCntMeshZ + 1));	//pIdx[���Ō�̃C���f�b�N�X + 1] = x,z���v�Z
			nDeg += 2;	//�k�ރ|���S����2�����
		}
		//x���J�E���g
		for (int nCntMeshX = 0; nCntMeshX < (m_nMeshX + 1); nCntMeshX++)
		{
			//pIdx[(���J�E���gx�� * 2) + ((�����镪��x�� * 2) * ���J�E���gz��) + �k�ރ|���S��]
			pIdx[(nCntMeshX * 2) + (((m_nMeshX + 1) * 2) * nCntMeshZ) + nDeg]	
				// = (�����镪��x��) + ���J�E���gx�� + ((�����镪��x��) * ���J�E���gz��)
				= (WORD)((m_nMeshX + 1) + nCntMeshX + ((m_nMeshX + 1) * nCntMeshZ));

			//pIdx[���+1]
			pIdx[(nCntMeshX * 2) + (((m_nMeshX + 1) * 2) * nCntMeshZ) + nDeg + 1]
				// = ���J�E���gx�� + ((�����镪��x��) * ���J�E���gz��)
				= (WORD)(nCntMeshX + ((m_nMeshX + 1) * nCntMeshZ));
		}
	}
	//�C���f�b�N�X�̃A�����b�N
	m_pIdxBuff->Unlock();
}

//=====================================
//�F�ݒ菈��(���_��)
//=====================================
void CMeshField::SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3)
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
void CMeshField::SetColor(D3DXCOLOR col)
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
void CMeshField::SetType(Object_Type type)
{
	CObject::SetType(type);
}

//=====================================
//�T�C�Y�ݒ菈��
//=====================================
void CMeshField::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_fAngle = atan2f(fWidth, fHeight);
	m_fLength = sqrtf((fWidth * fWidth) + (fHeight * fHeight)) / 2;
}

//=====================================
//����������
//=====================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos)
{
	CMeshField* pMeshField = new CMeshField;		//�v���C���[�|�C���^

	if (pMeshField != nullptr)
	{
		pMeshField->Init();
		pMeshField->SetPos(pos);
	}
	return pMeshField;
}