//=============================================================================
//
// ����
// Author : tanimoto kosuke
//
//=============================================================================
#include "shadow.h"
#include "application.h"
#include "texture.h"
#include "renderer.h"

//=====================================
//�f�t�H���g�R���X�g���N�^
//=====================================
CShadow::CShadow() : CObject3D(OBJECT_PRIORITY_CENTER)
{

}

//=====================================
//�f�X�g���N�^
//=====================================
CShadow::~CShadow()
{

}

//=====================================
//����������
//=====================================
void CShadow::Init()
{
	CObject3D::Init();

	//�I�u�W�F�N�g�ݒ菈��
	CObject3D::SetType(TYPE_EFFECT);
	CObject3D::SetSize(m_fWidth, m_fHeight);
}

//=====================================
//�I������
//=====================================
void CShadow::Uninit()
{
	CObject3D::Uninit();
}

//=====================================
//�X�V����
//=====================================
void CShadow::Update()
{
	CObject3D::Update();
}

//=====================================
//�`�揈��
//=====================================
void CShadow::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�摜�擾����
	CApplication::GetTexture()->TextureType(CTexture::TYPE_SHADOW);
	CObject3D::Draw();

	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//============================================================================
//�e�̈ʒu�X�V����
//============================================================================
void CShadow::SetShadow(D3DXVECTOR3 pos)
{
	float fSize = SHADOW_WIDTH + (pos.y / 2);
	SetPos(pos);		//�����Ŏw�肳�ꂽ�ԍ���pos��ݒ�
	//SHADOW_WIDTH + (pos.y / 2), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1 - (pos.y / 100)));
	if (fSize > 0.0f)
	{
		SetSize(fSize, fSize);
	}
	else
	{
		SetSize(0.0f, 0.0f);
	}
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1 - (pos.y / 100)));
}

//=====================================
//�e��������
//=====================================
CShadow *CShadow::Create(D3DXVECTOR3 pos)
{
	CShadow* pShadow;	//�����|�C���^

	pShadow = new CShadow;

	if (pShadow != nullptr)
	{
		pShadow->Init();
		pShadow->SetPos(pos);
	}
	return pShadow;
}