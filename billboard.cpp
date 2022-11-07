//=============================================================================
//
// billboard.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "billboard.h"
#include "application.h"
#include "rendering.h"
#include "object2D.h"

//�R���X�g���N�^
CBillboard::CBillboard()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_fFrameRot = Vec3Null;
	m_size = Vec2Null;
	D3DXMatrixIdentity(&m_mtxWorld);
}

CBillboard::CBillboard(const int nPriority) : CObject::CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_fFrameRot = Vec3Null;
	m_size = Vec2Null;
	D3DXMatrixIdentity(&m_mtxWorld);
}

//�f�X�g���N�^
CBillboard::~CBillboard()
{

}

//����������
HRESULT CBillboard::Init(void)
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_fFrameRot = Vec3Null;
	m_size = Vec2Null;
	D3DXMatrixIdentity(&m_mtxWorld);

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].pos = Vec3Null;					//���_���W�̐ݒ�
			pVtx[nCnt].nor = Vec3Null;					//�@���x�N�g���̐ݒ�
			pVtx[nCnt].nor.y = 1.0f;					//�@���x�N�g���̐ݒ�
			pVtx[nCnt].col = ColorWhite;					//���_�J���[�̐ݒ�
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//�I������
void CBillboard::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}
}

//�X�V����
void CBillboard::Update(void)
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx = NULL;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX	mtxRot, mtxOut;											//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;														//�r���[�}�g���b�N�X

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�J�����̋t�s���ݒ�
	mtxOut._11 = mtxView._11;
	mtxOut._13 = mtxView._31;
	mtxOut._31 = mtxView._13;
	mtxOut._33 = mtxView._33;

	//�����h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxOut);

	D3DXVECTOR3 Vtx[3] = {};
	Vtx[0] = pVtx[0].pos;
	Vtx[1] = pVtx[1].pos;
	Vtx[2] = pVtx[2].pos;

	D3DXVec3TransformCoord(&Vtx[0], &Vtx[0], &mtxOut);
	D3DXVec3TransformCoord(&Vtx[1], &Vtx[1], &mtxOut);
	D3DXVec3TransformCoord(&Vtx[2], &Vtx[2], &mtxOut);

	D3DXVECTOR3 V1, V2, N;

	V1 = Vtx[1] - Vtx[0];
	V2 = Vtx[2] - Vtx[1];

	D3DXVec3Cross(&N, &V2, &V1);
	D3DXVec3Normalize(&N, &N);

	pVtx[0].nor = N;
	pVtx[1].nor = N;
	pVtx[2].nor = N;
	pVtx[3].nor = N;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//�`�揈��
void CBillboard::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX	mtxRot, mtxTrans;											//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;														//�r���[�}�g���b�N�X

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���C�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	/*pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);*/

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�����h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._33 = mtxView._33;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�����h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�l�p�`��`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���C�g��L���ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//���̐ݒ�ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	/*pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);*/

	//�e�N�X�`���ւ̃|�C���^��NULL�ɂ���
	pDevice->SetTexture(0, NULL);

}

//�T�C�Y�̐ݒ菈��
void CBillboard::SetSize(const D3DXVECTOR2 size)
{
	m_size = size;

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_size.x, +m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, +m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, -m_size.y, 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//�ʒu�̐ݒ菈��
void CBillboard::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CBillboard::GetSize(void)
{
	return m_size;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_pos;
}

//�e�N�X�`���̎�ނ̐ݒ菈��
void CBillboard::SetTexture(TextType textType)
{
	LPDIRECT3DTEXTURE9 text = CObject_2D::GetTexturePointer(textType);
	m_pTexture = text;														//�e�N�X�`���̎�ނ̐ݒ�
}





//��������
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CBillboard* pObj = new CBillboard(3);

	if (FAILED(pObj->Init()))
	{
		return nullptr;
	}

	pObj->m_pos = pos;
	pObj->SetSize(size);

	return pObj;
}

//��������
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, const int nPriority)
{
	CBillboard* pObj = new CBillboard(nPriority);

	if (FAILED(pObj->Init()))
	{
		return nullptr;
	}

	pObj->m_pos = pos;
	pObj->SetSize(size);

	return pObj;
}