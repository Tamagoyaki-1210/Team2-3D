//=============================================================================
//
// �v�Z�p�}�g���N�X
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _MATRIX_H_
#define _MATRIX_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

float Normalize(float val);
D3DXVECTOR3 NormalizeLength(float valX, float valY);
bool CollisionCircle(D3DXVECTOR3 pos, float fLength, D3DXVECTOR3 posSub, float fLengthSub);		//�~�^�����蔻��v�Z����
bool CollisionSquare(D3DXVECTOR3 pos, D3DXVECTOR3 posSub, float fWidth, float fHeight, float fWidthSub, float fHeightSub);	//�l�p�`�����蔻��v�Z����

#endif // !_MATRIX_H_
