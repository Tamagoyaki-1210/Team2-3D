//============================================================================
//
//
//�r���{�[�h�̏���[billboard.cpp] (�t�@�C���w�b�_�R�����g)
//Author:�J�{�N��
//
//============================================================================
#include "billboard.h"	//�쐬����billboard.h���C���N���[�h����
#include "renderer.h"
#include "application.h"
#include "texture.h"
//#include "shadow.h"		//�쐬����shadow.h���C���N���[�h����

//�f�t�H���g�R���X�g���N�^
//=====================================
CBillBoard::CBillBoard(int list) : CObject(list), m_pVtxBuff(nullptr)
{

}

//=====================================
//�f�X�g���N�^
//=====================================
CBillBoard::~CBillBoard()
{

}

//****************************************************************************
//�O���[�o���ϐ�
//****************************************************************************
//bool g_ZBillBoardDebug = false;						//Z�o�b�t�@�̃f�o�b�O

//============================================================================
//�r���{�[�h�̏���������
//============================================================================
void CBillBoard::Init()
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

	SetUV();

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

	m_bUse = true;
}

//============================================================================
//�r���{�[�h�̏I������
//============================================================================
void CBillBoard::Uninit()
{
	if (m_bUse == true)
	{
		m_bUse = false;
		//���_�o�b�t�@�̔j��
		if (m_pVtxBuff != nullptr)
		{
			m_pVtxBuff->Release();
			m_pVtxBuff = nullptr;
		}
		//�I�u�W�F�N�g�̔j��
		Release();
	}
}

//============================================================================
//�r���{�[�h�̍X�V����
//============================================================================
void CBillBoard::Update()
{
	//for (int nCntBillBoard = 0; nCntBillBoard < MAX_BILLBOARD; nCntBillBoard++)
	//{
	//	if (g_aBillBoard[nCntBillBoard].bUse == true)
	//	{
	//		SetpositionShadow(g_aBillBoard[nCntBillBoard].IndxShadow, D3DXVECTOR3(g_aBillBoard[nCntBillBoard].pos.x, 0.0f, g_aBillBoard[nCntBillBoard].pos.z),
	//			SHADOW_WIDTH + (g_aBillBoard[nCntBillBoard].pos.y / 2), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1 - (g_aBillBoard[nCntBillBoard].pos.y / 100)));
	//	}
	//}

	//if (GetKeyboardTrigger(DIK_F7) == true)
	//{//Z�o�b�t�@�e�X�g
	//	g_ZBillBoardDebug = !g_ZBillBoardDebug;
	//}
	SetUV();
	//m_rot.x++;
	//m_rot.z++;
}

//============================================================================
//�r���{�[�h�̕`�揈��
//============================================================================
void CBillBoard::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X

		//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_worldmtx);

	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	D3DXMatrixInverse(&m_worldmtx, NULL, &mtxView);
	m_worldmtx._41 = 0.0f;
	m_worldmtx._42 = 0.0f;
	m_worldmtx._43 = 0.0f;

	////�J�����̋t�s���ݒ�
	//m_worldmtx._11 = mtxView._11;
	//m_worldmtx._12 = mtxView._21;
	//m_worldmtx._13 = mtxView._31;

	////�e
	//m_worldmtx._21 = mtxView._12;
	//m_worldmtx._22 = mtxView._22;
	//m_worldmtx._23 = mtxView._32;

	//m_worldmtx._31 = mtxView._13;
	//m_worldmtx._32 = mtxView._23;
	//m_worldmtx._33 = mtxView._33;

	////�����𔽉f(YaW : y,Pitch : x,Roll : z)
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBillBoard[nCntBillBoard].rot.y, g_aBillBoard[nCntBillBoard].rot.x, g_aBillBoard[nCntBillBoard].rot.z);
	//D3DXMatrixMultiply(&g_aBillBoard[nCntBillBoard].Worldmtx, &g_aBillBoard[nCntBillBoard].Worldmtx, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldmtx, &m_worldmtx, &mtxTrans);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	////Z�o�b�t�@�̒l����O��Z�o�b�t�@�̒l��菬�����ꍇ
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//if (g_ZBillBoardDebug == false)
	//{
	//	//Z�o�b�t�@��`�悷��
	//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//}
	//else
	//{
	//	//Z�o�b�t�@��`�悷��
	//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//}

	////�A���t�@�e�X�g��L��
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_worldmtx);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	CApplication::GetTexture()->TextureType(CTexture::TYPE_PLAYER);

	//�r���{�[�h�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	////Z�o�b�t�@��`�悷��
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	////Z�o�b�t�@�̒l����O��Z�o�b�t�@�̒l��菬�����ꍇ
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	////�A���t�@�e�X�g�𖳌��ɖ߂�
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//�e�N�X�`���̉���
	CApplication::GetTexture()->TextureClear();

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//=====================================
//UV�ݒ菈��
//=====================================
void CBillBoard::SetUV()
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[0].pos.z = m_pos.z;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[1].pos.z = m_pos.z;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[2].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[2].pos.z = m_pos.z;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[3].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[3].pos.z = m_pos.z;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
//�F�ݒ菈��(���_��)
//=====================================
void CBillBoard::SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3)
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
void CBillBoard::SetColor(D3DXCOLOR col)
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
//��ʐݒ菈��
//=====================================
void CBillBoard::SetType(Object_Type type)
{
	CObject::SetType(type);
}

//=====================================
//�T�C�Y�ݒ菈��
//=====================================
void CBillBoard::SetSize(float fWidth, float fHeight)
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
CBillBoard *CBillBoard::Create(D3DXVECTOR3 pos)
{
	CBillBoard *pBillBoard = new CBillBoard;	//�I�u�W�F�N�g2D�|�C���^

	if (pBillBoard != nullptr)
	{
		pBillBoard->Init();
		pBillBoard->SetPos(pos);
	}
	return pBillBoard;
}