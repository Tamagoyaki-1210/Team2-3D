//=============================================================================
//
// �I�u�W�F�N�g2D
// Author : tanimoto kosuke
//
//=============================================================================
#include "object2D.h"
#include "renderer.h"
#include "application.h"

//=====================================
//�f�t�H���g�R���X�g���N�^
//=====================================
CObject2D::CObject2D(int list) : CObject(list), m_pVtxBuff(nullptr)
{
	
}

//=====================================
//�f�X�g���N�^
//=====================================
CObject2D::~CObject2D()
{

}

//=====================================
//����������
//=====================================
void CObject2D::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[0].pos.y = m_pos.y - cosf(m_fAngle + m_rot.y) * m_fLength;
	pVtx[0].pos.z = m_pos.z;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle - m_rot.y) * m_fLength;
	pVtx[1].pos.z = m_pos.z;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle - m_rot.y) * m_fLength;
	pVtx[2].pos.z = m_pos.z;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle + m_rot.y) * m_fLength;
	pVtx[3].pos.z = m_pos.z;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CObject2D::Uninit()
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
void CObject2D::Update()
{

}

//=====================================
//�`�揈��
//=====================================
void CObject2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================
//UV�ݒ菈��
//=====================================
void CObject2D::SetUV()
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[0].pos.y = m_pos.y - cosf(m_fAngle + m_rot.y) * m_fLength;
	pVtx[0].pos.z = m_pos.z;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle - m_rot.y) * m_fLength;
	pVtx[1].pos.z = m_pos.z;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle - m_rot.x) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle - m_rot.y) * m_fLength;
	pVtx[2].pos.z = m_pos.z;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.x) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle + m_rot.y) * m_fLength;
	pVtx[3].pos.z = m_pos.z;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
//���_�e�N�X�`���ݒ菈��(�A�j���[�V����)
//=====================================
void CObject2D::SetAnim(int nAnimX, int nAnimY, int nControl)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f / nAnimX) * m_nAnimCounterX, (1.0f / nAnimY) * m_nAnimCounterY);
	pVtx[1].tex = D3DXVECTOR2((1.0f / nAnimX) * (m_nAnimCounterX + 1.0f), (1.0f / nAnimY) * m_nAnimCounterY);
	pVtx[2].tex = D3DXVECTOR2((1.0f / nAnimX) * m_nAnimCounterX, (1.0f / nAnimY) * (m_nAnimCounterY + 1.0f));
	pVtx[3].tex = D3DXVECTOR2((1.0f / nAnimX) * (m_nAnimCounterX + 1.0f), (1.0f / nAnimY) * (m_nAnimCounterY + 1.0f));

	m_nAnimControl++;

	if (nControl <= m_nAnimControl)
	{
		m_nAnimCounterX++;
		m_nAnimControl = 0;
		if (nAnimX <= m_nAnimCounterX)
		{
			m_nAnimCounterX = 0;
			m_nAnimCounterY++;
			if (nAnimY <= m_nAnimCounterY)
			{
				m_nAnimCounterY = 0;
			}
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
//���_�e�N�X�`���ݒ菈��(���_�e�N�X�`��)
//=====================================
void CObject2D::SetTex(int tex, int div)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((tex + 0.0f) / div, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((tex + 1.0f) / div, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((tex + 0.0f) / div, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((tex + 1.0f) / div, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
//�F�ݒ菈��(���_��)
//=====================================
void CObject2D::SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

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
void CObject2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

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
void CObject2D::SetType(Object_Type type)
{
	CObject::SetType(type);
}

//=====================================
//�I�u�W�F�N�g�ݒ菈��
//=====================================
void CObject2D::SetSize(float fWidth, float fHeight)
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
CObject2D *CObject2D::Create(D3DXVECTOR3 pos)
{
	CObject2D *pObject2D = new CObject2D;	//�I�u�W�F�N�g2D�|�C���^

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(pos);
	}
	return pObject2D;
}