//=============================================================================
//
// �摜
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//---------------------------
//�N���X
//---------------------------
class CTexture
{
public:
	enum Texture_Type
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,		//�v���C���[
		TYPE_MESHFIELD_01,	//��01
		TYPE_SHADOW,		//�e
		TYPE_MAX
	};

	CTexture();
	~CTexture();

	void Uninit();
	void Load();
	void TextureType(Texture_Type textype);
	void TextureClear();
private:
	LPDIRECT3DTEXTURE9 m_pTextureType[TYPE_MAX];		//Texture���
};

#endif // !_TEXTURE_H_
