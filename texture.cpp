//=============================================================================
//
// �摜
// Author : tanimoto kosuke
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "application.h"

//=====================================
//�f�t�H���g�R���X�g���N�^
//=====================================
CTexture::CTexture()
{

}

//=====================================
//�f�X�g���N�^
//=====================================
CTexture::~CTexture()
{

}

//=====================================
//�I������
//=====================================
void CTexture::Uninit()
{
	for (int nInd = 0; nInd < TYPE_MAX; nInd++)
	{
		if (m_pTextureType[nInd] == nullptr)
		{
			continue;
		}
		//m_pTexture[nInd]->Release();
		m_pTextureType[nInd] = nullptr;
	}
}

//=====================================
//�ǂݍ��ݏ���
//=====================================
void CTexture::Load()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//����
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BackGround\\white_screen.jpg", &m_pTextureType[TYPE_NONE]);

	//�v���C���[
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Player\\mofu.jpg", &m_pTextureType[TYPE_PLAYER]);

	//��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Field\\field000.jpg", &m_pTextureType[TYPE_MESHFIELD_01]);

	//�e
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Shadow\\shadow000.jpg", &m_pTextureType[TYPE_SHADOW]);
}

//=====================================
//�摜��ޏ���
//=====================================
void CTexture::TextureType(Texture_Type textype)
{
	//�e�N�X�`���̐ݒ�
	CApplication::GetRenderer()->GetDevice()->SetTexture(0, m_pTextureType[textype]);
}

//=====================================
//�摜��ޏ���
//=====================================
void CTexture::TextureClear()
{
	//�e�N�X�`���̐ݒ�
	CApplication::GetRenderer()->GetDevice()->SetTexture(0, nullptr);
}