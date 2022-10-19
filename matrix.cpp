//=============================================================================
//
// �v�Z�p�}�g���N�X
// Author : tanimoto kosuke
//
//=============================================================================
#include <stdio.h>
#include "matrix.h"

//=====================================
//���K���v�Z����
//=====================================
float Normalize(float val)
{
	float valNormalize = val * (1 / sqrtf(val * val));
	return valNormalize;
}

//=====================================
//���K���v�Z����
//=====================================
D3DXVECTOR3 NormalizeLength(float valX, float valY)
{
	float valNormalize = 1 / sqrtf((valX * valX) + (valY * valY));

	D3DXVECTOR3 Length(valX * valNormalize, valY * valNormalize, 0.0f);

	return Length;
}

//=====================================
////�~�^�����蔻��v�Z����
//=====================================
bool CollisionCircle(D3DXVECTOR3 pos, float fLength, D3DXVECTOR3 posSub, float fLengthSub)
{
	float fSumLengthRad = (fLength + fLengthSub) / 2;				//�~�̔��a���m�̘a

	float fSubX = pos.x - posSub.x;									//X���W�̍���
	float fSubY = pos.y - posSub.y;									//Y���W�̍���
	float fSubLength = sqrtf((fSubX * fSubX) + (fSubY * fSubY));	//���݂�2�_�̋���

	return fSumLengthRad >= fSubLength;
}

//=====================================
//�l�p�`�����蔻��v�Z����
//=====================================
bool CollisionSquare(D3DXVECTOR3 pos, D3DXVECTOR3 posSub, float fWidth, float fHeight, float fWidthSub, float fHeightSub)
{
	float fLeft = pos.x - (fWidth / 2);		//�l�p�`����
	float fRight = pos.x + (fWidth / 2);		//�l�p�`�E��
	float fUpp = pos.y - (fHeight / 2);		//�l�p�`�㑤
	float fLow = pos.y + (fHeight / 2);		//�l�p�`����

	float fLeftSub = posSub.x - (fWidthSub / 2);		//�l�p�`����
	float fRightSub = posSub.x + (fWidthSub / 2);		//�l�p�`�E��
	float fUppSub = posSub.y - (fHeightSub / 2);		//�l�p�`�㑤
	float fLowSub = posSub.y + (fHeightSub / 2);		//�l�p�`����

	if (fLeft < fRightSub && fRight > fLeftSub
		&& fUpp < fLowSub && fLow > fUppSub)
	{
		return true;
	}
	else
	{
		return false;
	}
}
