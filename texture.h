//=============================================================================
//
// 画像
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//---------------------------
//クラス
//---------------------------
class CTexture
{
public:
	enum Texture_Type
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,		//プレイヤー
		TYPE_MESHFIELD_01,	//床01
		TYPE_SHADOW,		//影
		TYPE_MAX
	};

	CTexture();
	~CTexture();

	void Uninit();
	void Load();
	void TextureType(Texture_Type textype);
	void TextureClear();
private:
	LPDIRECT3DTEXTURE9 m_pTextureType[TYPE_MAX];		//Texture種別
};

#endif // !_TEXTURE_H_
