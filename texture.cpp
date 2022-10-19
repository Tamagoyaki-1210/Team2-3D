//=============================================================================
//
// 画像
// Author : tanimoto kosuke
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "application.h"

//=====================================
//デフォルトコンストラクタ
//=====================================
CTexture::CTexture()
{

}

//=====================================
//デストラクタ
//=====================================
CTexture::~CTexture()
{

}

//=====================================
//終了処理
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
//読み込み処理
//=====================================
void CTexture::Load()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//無し
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BackGround\\white_screen.jpg", &m_pTextureType[TYPE_NONE]);

	//プレイヤー
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Player\\mofu.jpg", &m_pTextureType[TYPE_PLAYER]);

	//床
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Field\\field000.jpg", &m_pTextureType[TYPE_MESHFIELD_01]);

	//影
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Shadow\\shadow000.jpg", &m_pTextureType[TYPE_SHADOW]);
}

//=====================================
//画像種類処理
//=====================================
void CTexture::TextureType(Texture_Type textype)
{
	//テクスチャの設定
	CApplication::GetRenderer()->GetDevice()->SetTexture(0, m_pTextureType[textype]);
}

//=====================================
//画像種類処理
//=====================================
void CTexture::TextureClear()
{
	//テクスチャの設定
	CApplication::GetRenderer()->GetDevice()->SetTexture(0, nullptr);
}