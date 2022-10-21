//=============================================================================
//
// meshfield.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "meshfield.h"
#include "application.h"
#include "rendering.h"
#include "object2D.h"
#include "debugProc.h"

std::vector <CObject*> CMeshfield::m_vLandedObj;
std::vector <CMeshfield*> CMeshfield::m_vMeshfield;

//�R���X�g���N�^
CMeshfield::CMeshfield()
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec2Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIntexNumber = 0;
	m_nPolygonNumber = 0;
	m_nLineVertex = 0;
	m_nColumnVertex = 0;

	m_vMeshfield.push_back(this);
}

CMeshfield::CMeshfield(const int nPriority) : CObject::CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec2Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIntexNumber = 0;
	m_nPolygonNumber = 0;
	m_nLineVertex = 0;
	m_nColumnVertex = 0;

	m_vMeshfield.push_back(this);
}

//�f�X�g���N�^
CMeshfield::~CMeshfield()
{

}

//����������
HRESULT CMeshfield::Init(void)
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec2Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIntexNumber = 0;
	m_nPolygonNumber = 0;
	m_nLineVertex = 0;
	m_nColumnVertex = 0;

	return S_OK;
}

//�I������
void CMeshfield::Uninit(void)
{
	//VERTEX_3D* pVtx = nullptr;

	////���_�o�b�t�@�����b�N
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////���_���̐ݒ�
	//for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	//{
	//	FILE*pFile;				//�t�@�C���|�C���^��錾����

	//	//�t�@�C�����J��
	//	pFile = fopen("data\\IdxTest.txt", "w");

	//	if (pFile != NULL)
	//	{//�t�@�C�����J�����ꍇ
	//	 //�t�@�C���Ƀ����L���O���������o��

	//		for (int nCnt = 0; nCnt < /*m_nIntexNumber - 2*/m_nVertexNumber; nCnt++)
	//		{
	//			fprintf(pFile, " pos: %f %f %f\n nor: %f %f %f\n tex: %f %f\n\n", pVtx[nCnt].pos.x, pVtx[nCnt].pos.y, pVtx[nCnt].pos.z, pVtx[nCnt].nor.x, pVtx[nCnt].nor.y, pVtx[nCnt].nor.z, pVtx[nCnt].tex.x, pVtx[nCnt].tex.y);
	//		}

	//		//�t�@�C�������
	//		fclose(pFile);
	//	}
	//}

	////���_�o�b�t�@�̃A�����b�N
	//m_pVtxBuff->Unlock();

	m_vLandedObj.clear();

	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}

	int a = m_vMeshfield.size();

	for (int nCnt = 0; nCnt < a; nCnt++)
	{
		if (m_vMeshfield.data()[nCnt] == this)
		{
			m_vMeshfield.erase(m_vMeshfield.begin() + nCnt);
			break;
		}
	}
}

//�X�V����
void CMeshfield::Update(void)
{
	//Interaction();
}

//�`�揈��
void CMeshfield::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX	mtxRot, mtxTrans;											//�v�Z�p�}�g���b�N�X

	void* p = this;

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//�����h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�����h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`�揈��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertexNumber, 0, m_nPolygonNumber);

	pDevice->SetTexture(0, NULL);

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//�ʒu�̐ݒ菈��
void CMeshfield::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CMeshfield::GetSize(void)
{
	return m_size;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CMeshfield::GetPos(void)
{
	return m_pos;
}

//�e�N�X�`���̐ݒ菈��
void CMeshfield::SetTexture(CObject::TextType texture)
{
	LPDIRECT3DTEXTURE9 text = CObject_2D::GetTexturePointer(texture);
	m_pTexture = text;
}

void CMeshfield::SetTextureTiling(D3DXVECTOR2 TileSize)
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (TileSize.x * (nCnt % m_nColumnVertex)), 0.0f + (TileSize.y * (nCnt / m_nColumnVertex)));
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

void CMeshfield::SetTextureTiling(float fTileSize)
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (fTileSize * (nCnt % m_nColumnVertex)), 0.0f + (fTileSize * (nCnt / m_nColumnVertex)));
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}









void CMeshfield::AddLandedObj(CObject* pObj)
{
	/*if (pObj != nullptr)
	{
		m_vLandedObj.push_back(pObj);
	}*/
}

void CMeshfield::RemoveLandedObj(CObject* pObj)
{
	/*if (pObj != nullptr)
	{
		int nSize = m_vLandedObj.size();

		for (int nCnt = 0; nCnt < nSize; nCnt++)
		{
			if (m_vLandedObj.data()[nCnt] == pObj)
			{
				m_vLandedObj.erase(m_vLandedObj.begin() + nCnt);
				break;
			}
		}
	}*/
}

CMeshfield* CMeshfield::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR2 unitSize, const int nColumn, const int nLine)
{
	CMeshfield* pField = new CMeshfield(3);

	if (FAILED(pField->Init()))
	{
		return nullptr;
	}

	pField->m_pos = pos;
	pField->m_rot = rot;
	pField->m_size = unitSize;
	pField->m_nColumnVertex = nLine;
	pField->m_nLineVertex = nColumn;
	pField->SetVertex();

	return pField;
}

CMeshfield* CMeshfield::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR2 unitSize, const int nColumn, const int nLine, const int nPriority)
{
	CMeshfield* pField = new CMeshfield(nPriority);

	if (FAILED(pField->Init()))
	{
		return nullptr;
	}

	pField->m_pos = pos;
	pField->m_rot = rot;
	pField->m_size = unitSize;
	pField->m_nColumnVertex = nLine;
	pField->m_nLineVertex = nColumn;
	pField->SetVertex();

	return pField;
}

void CMeshfield::FieldInteraction(CObject* pObj)
{
	int nFieldNum = m_vMeshfield.size();

	D3DXVECTOR3 pos = pObj->GetPos();

	for (int nCntField = 0; nCntField < nFieldNum; nCntField++)
	{
		CMeshfield* pField = m_vMeshfield.data()[nCntField];

		VERTEX_3D* pVtx = nullptr;

		//���_�o�b�t�@�����b�N
		pField->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		WORD*pIdx = nullptr;		//�C���f�b�N�X���ւ̃|�C���^

		//�C���f�b�N�X�o�b�t�@�����b�N
		pField->m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCnt = 0; nCnt < pField->m_nPolygonNumber; nCnt++)
		{
			D3DXVECTOR3 Vtx[3] = {};
			D3DXVECTOR3 Edge[3] = {};
			D3DXVECTOR3 Distance[3] = {};
			D3DXVECTOR3 Cross[3] = {};

			Vtx[0] = pVtx[pIdx[nCnt]].pos;
			Vtx[1] = pVtx[pIdx[nCnt + 1]].pos;
			Vtx[2] = pVtx[pIdx[nCnt + 2]].pos;

			D3DXMATRIX mtxOut, mtxTrans, mtxRot;

			//�����h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxOut);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pField->m_rot.y, pField->m_rot.x, pField->m_rot.z);
			D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pField->m_pos.x, pField->m_pos.y, pField->m_pos.z);
			D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxTrans);

			//���_���W���O���[�o�����W�ɕϊ�����
			D3DXVec3TransformCoord(&Vtx[0], &Vtx[0], &mtxOut);
			D3DXVec3TransformCoord(&Vtx[1], &Vtx[1], &mtxOut);
			D3DXVec3TransformCoord(&Vtx[2], &Vtx[2], &mtxOut);

			Edge[0] = Vtx[1] - Vtx[0];
			Edge[1] = Vtx[2] - Vtx[1];
			Edge[2] = Vtx[0] - Vtx[2];

			Distance[0] = pos - Vtx[0];
			Distance[1] = pos - Vtx[1];
			Distance[2] = pos - Vtx[2];

			D3DXVec3Cross(&Cross[0], &Edge[0], &Distance[0]);
			D3DXVec3Cross(&Cross[1], &Edge[1], &Distance[1]);
			D3DXVec3Cross(&Cross[2], &Edge[2], &Distance[2]);

			if (Cross[0].y * Cross[1].y >= 0 && Cross[0].y * Cross[2].y >= 0 && Cross[1].y * Cross[2].y >= 0)
			{
				D3DXVECTOR3 Normal = Vec3Null;

				if (nCnt % 2 == 0)
				{
					D3DXVec3Cross(&Normal, &Edge[0], &Edge[1]);
				}
				else
				{
					D3DXVec3Cross(&Normal, &Edge[1], &Edge[0]);
				}

				D3DXVec3Normalize(&Normal, &Normal);

				float Y = (Vtx[0].y) - ((((pos.x - (Vtx[0].x)) * Normal.x) + ((pos.z - Vtx[0].z) * Normal.z)) / Normal.y);

				if (pos.y < Y && pos.y + 50.0f >= Y)
				{
					pos.y = Y;
					pObj->SetPos(pos);
					break;
				}
			}
			
		}

		//�C���f�b�N�X�o�b�t�@���A�����b�N
		pField->m_pIdxBuff->Unlock();

		//���_�o�b�t�@�̃A�����b�N
		pField->m_pVtxBuff->Unlock();
	}
}







//���_�C���f�b�N�X�̐ݒ菈��
void CMeshfield::SetVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	//���_���̌v�Z
	m_nVertexNumber = m_nLineVertex * m_nColumnVertex;
	//�|���S�����̌v�Z
	m_nPolygonNumber = (((((m_nColumnVertex - 1) * 2) + 2) * 2) + ((((m_nColumnVertex - 1) * 2) + 4) * ((m_nLineVertex - 1) - 2)));
	//�C���f�b�N�X���̌v�Z
	m_nIntexNumber = (((((m_nColumnVertex - 1) * 2) + 2) * 2) + ((((m_nColumnVertex - 1) * 2) + 4) * ((m_nLineVertex - 1) - 2))) + 2;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVertexNumber,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIntexNumber,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	{	
		//���_�̈ʒu�̏�����
		pVtx[nCnt].pos = D3DXVECTOR3((float)(m_size.x * (nCnt % m_nColumnVertex)), /*(float)CObject::random(-500, 500) * 0.1f*/0.0f, (float)(-m_size.y * (nCnt / m_nColumnVertex)));
		//���_�̖@���̏�����
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//���_�J���[�̏�����
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (1.0f * (nCnt % m_nColumnVertex)), 0.0f + (1.0f * (nCnt / m_nColumnVertex)));
	}

	/*pVtx[250].pos.y += (float)random(150, 200);
	pVtx[251].pos.y += (float)random(150, 200);
	pVtx[252].pos.y += (float)random(150, 200);
	pVtx[253].pos.y += (float)random(150, 200);
	pVtx[254].pos.y += (float)random(150, 200);
	pVtx[255].pos.y += (float)random(150, 200);
	pVtx[256].pos.y += (float)random(150, 200);*/

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	WORD*pIdx = nullptr;		//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nStart = 0;		//�v�Z�p�̃��[�J���ϐ�

						//�C���f�b�N�X���̐ݒ�
	for (int nCnt = 0; nCnt < m_nLineVertex - 1; nCnt++)
	{
		for (int nCntColumn = 0; nCntColumn < m_nColumnVertex * 2; nCntColumn += 2)
		{
			//��s�̃C���f�b�N�X�̐ݒ�
			pIdx[(nCnt * m_nColumnVertex) + nCntColumn + nStart] = m_nColumnVertex + (m_nColumnVertex * (nCnt)) + (nCntColumn / 2);
			int a = m_nColumnVertex + (m_nColumnVertex * (nCnt)) + (nCntColumn / 2);
			pIdx[(nCnt * m_nColumnVertex) + nCntColumn + nStart + 1] = (m_nColumnVertex * (nCnt)) + (nCntColumn / 2);
			a = (m_nColumnVertex * (nCnt)) + (nCntColumn / 2);
			a++;

			if (nCntColumn + 2 >= 2 * m_nColumnVertex && nCnt != m_nLineVertex - 2)
			{
				//�k�ރ|���S���p�̃C���f�b�N�X�̐ݒ�
				pIdx[(nCnt * m_nColumnVertex) + nCntColumn + nStart + 2] = (m_nColumnVertex * (nCnt)) + (nCntColumn / 2);
				pIdx[(nCnt * m_nColumnVertex) + nCntColumn + nStart + 3] = m_nColumnVertex + (m_nColumnVertex * (nCnt + 1));
				nStart += 2 + m_nColumnVertex;
			}

		}

	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	pVtx = nullptr;

	pIdx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < m_nIntexNumber - 2; nCnt++)
	{
		if (pIdx[nCnt] != pIdx[nCnt + 1]  && pIdx[nCnt] != pIdx[nCnt + 2] && pIdx[nCnt + 1] != pIdx[nCnt + 2])
		{
			D3DXVECTOR3 V1, V2, Norm, N;

			V1 = pVtx[pIdx[nCnt + 1]].pos - pVtx[pIdx[nCnt]].pos;
			V2 = pVtx[pIdx[nCnt + 2]].pos - pVtx[pIdx[nCnt + 1]].pos;


			if (nCnt % 2 == 0)
			{
				D3DXVec3Cross(&Norm, &V1, &V2);
			}
			else
			{
				D3DXVec3Cross(&Norm, &V2, &V1);
			}

			D3DXVec3Normalize(&Norm, &Norm);

			N = pVtx[pIdx[nCnt]].nor + Norm;
			//D3DXVec3Normalize(&N, &N);
			pVtx[pIdx[nCnt]].nor = N;
			N = pVtx[pIdx[nCnt + 1]].nor + Norm;
			//D3DXVec3Normalize(&N, &N);
			pVtx[pIdx[nCnt + 1]].nor = N;
			N = pVtx[pIdx[nCnt + 2]].nor + Norm;
			//D3DXVec3Normalize(&N, &N);
			pVtx[pIdx[nCnt + 2]].nor = N;
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	{
		D3DXVECTOR3 N = pVtx[nCnt].nor;
		D3DXVec3Normalize(&N, &N);
		pVtx[nCnt].nor = N;
	}
	
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	/*

	FILE*pFile;				//�t�@�C���|�C���^��錾����

	//�t�@�C�����J��
	pFile = fopen("data\\VtxSave.txt", "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
		{
			D3DXCOLOR col = pVtx[nCnt].col;

			fprintf(pFile, "%f %f %f\n%f %f %f\n%f %f %f %f\n%f %f\n\n", pVtx[nCnt].pos.x, pVtx[nCnt].pos.y, pVtx[nCnt].pos.z, pVtx[nCnt].nor.x, pVtx[nCnt].nor.y, pVtx[nCnt].nor.z, col.r, col.g, col.b, col.a, pVtx[nCnt].tex.x, pVtx[nCnt].tex.y);
		}

		//�t�@�C�������
		fclose(pFile);
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	//�t�@�C�����J��
	pFile = fopen("data\\IdxSave.txt", "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
	 //�t�@�C���Ƀ����L���O���������o��

		for (int nCnt = 0; nCnt < m_nIntexNumber; nCnt++)
		{
			fprintf(pFile, "%d\n", pIdx[nCnt]);
		}

		//�t�@�C�������
		fclose(pFile);
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();
	*/
	
}