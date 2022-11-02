//=============================================================================
//
// silhouette.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "silhouette.h"
#include "application.h"
#include "rendering.h"


//�R���X�g���N�^
CSilhouette::CSilhouette() : CObject_2D(5)
{

}

//�f�X�g���N�^
CSilhouette::~CSilhouette()
{

}

HRESULT CSilhouette::Init(void)
{
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));
	SetTexture(CObject::TEXTURE_NULL);
	SetTextureParameter(1, 1, 1, INT_MAX);
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	return S_OK;
}


void CSilhouette::Uninit(void)
{
	CObject_2D::Uninit();
}


void CSilhouette::Draw(void)
{
	//�f�o�C�X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�X�e���V���o�b�t�@��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//�X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	//�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//�X�e���V���e�X�g�̔�r���@�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	//�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	CObject_2D::Draw();

	//�X�e���V���o�b�t�@�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

CSilhouette* CSilhouette::Create(void)
{
	CSilhouette* pObj = new CSilhouette;

	if (FAILED(pObj->Init()))
	{
		return nullptr;
	}

	return pObj;
}