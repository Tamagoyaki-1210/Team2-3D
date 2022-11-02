//=============================================================================
//
// BoxHitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "BoxHitbox.h"
#include "line.h"

//�R���X�g���N�^
CBoxHitbox::CBoxHitbox()
{
	for (int nCnt = 0; nCnt < 12; nCnt++)
	{
		m_pLine[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CBoxHitbox::~CBoxHitbox()
{

}

//����������
HRESULT CBoxHitbox::Init(void)
{
	if (FAILED(CHitbox::Init()))
	{
		return -1;
	}

	for (int nCnt = 0; nCnt < 12; nCnt++)
	{
		m_pLine[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CBoxHitbox::Uninit(void)
{
	CHitbox::Uninit();

	for (int nCnt = 0; nCnt < 12; nCnt++)
	{
		if (m_pLine[nCnt] != nullptr)
		{
			m_pLine[nCnt]->Release();
			m_pLine[nCnt] = nullptr;
		}
	}
}

//�X�V����
void CBoxHitbox::Update(void)
{
	SetPos(GetPos() + D3DXVECTOR3(0.2f, 0.0f, 0.0f));

	std::vector <CHitbox*>* pHbx = GetAllHitbox();

	for (int nCnt = 0; nCnt < (int)pHbx->size(); nCnt++)
	{
		if (pHbx->data()[nCnt] != this)
		{
			HITBOX_SHAPE shape = pHbx->data()[nCnt]->GetShape();

			switch (shape)
			{
			case CHitbox::SHAPE_SPHERE:
				break;

			case CHitbox::SHAPE_BOX:

			{
				if (BoxBoxHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetRot(), pHbx->data()[nCnt]->GetSize()))
				{
					//pHbx->data()[nCnt]->SetCollisionState(true);

					if (GetEffect() != EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() == EFFECT_MAX)
					{
						pHbx->data()[nCnt]->SetEffect(GetEffect());
					}
				}

			}

			break;

			case CHitbox::SHAPE_CYLINDER:

			{
				if (BoxBoxHit(pHbx->data()[nCnt]->GetPos(), Vec3Null, pHbx->data()[nCnt]->GetSize()))
				{
					//pHbx->data()[nCnt]->SetCollisionState(true);

					if (GetEffect() != EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() == EFFECT_MAX)
					{
						pHbx->data()[nCnt]->SetEffect(GetEffect());
					}
				}
			}

			break;

			default:
				break;
			}
		}
	}

	for (int nCnt = 0; nCnt < 12; nCnt++)
	{
		if (m_pLine[nCnt] != nullptr)
		{
			m_pLine[nCnt]->SetPos(GetPos());
		}
	}

	CHitbox::Update();
}




CBoxHitbox* CBoxHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent)
{
	CBoxHitbox* pHitbox = new CBoxHitbox;

	if (FAILED(pHitbox->Init()))
	{
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);
	pHitbox->SetPos(pos);
	pHitbox->SetLastPos(pos);
	pHitbox->SetSize(size);
	pHitbox->SetType(type);
	pHitbox->SetShape(CHitbox::SHAPE_BOX);
	pHitbox->SetParent(pParent);

#ifdef _DEBUG

	D3DXVECTOR3 VtxPos[8] = {};
	VtxPos[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
	VtxPos[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
	VtxPos[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
	VtxPos[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);
	VtxPos[4] = D3DXVECTOR3(-size.x, size.y, size.z);
	VtxPos[5] = D3DXVECTOR3(size.x, size.y, size.z);
	VtxPos[6] = D3DXVECTOR3(size.x, size.y, -size.z);
	VtxPos[7] = D3DXVECTOR3(-size.x, size.y, -size.z);

	pHitbox->m_pLine[0] = CLine::Create(pos, Vec3Null, VtxPos[0], VtxPos[1], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[1] = CLine::Create(pos, Vec3Null, VtxPos[1], VtxPos[2], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[2] = CLine::Create(pos, Vec3Null, VtxPos[2], VtxPos[3], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[3] = CLine::Create(pos, Vec3Null, VtxPos[3], VtxPos[0], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
																   
	pHitbox->m_pLine[4] = CLine::Create(pos, Vec3Null, VtxPos[0], VtxPos[4], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, VtxPos[1], VtxPos[5], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[6] = CLine::Create(pos, Vec3Null, VtxPos[2], VtxPos[6], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[7] = CLine::Create(pos, Vec3Null, VtxPos[3], VtxPos[7], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
																	   
	pHitbox->m_pLine[8] = CLine::Create(pos, Vec3Null, VtxPos[4], VtxPos[5], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[9] = CLine::Create(pos, Vec3Null, VtxPos[5], VtxPos[6], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[10] = CLine::Create(pos, Vec3Null, VtxPos[6], VtxPos[7], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, VtxPos[7], VtxPos[4], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

#endif // !DEBUG


	return pHitbox;
}

CBoxHitbox* CBoxHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore)
{
	CBoxHitbox* pHitbox = new CBoxHitbox;

	if (FAILED(pHitbox->Init()))
	{
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);
	pHitbox->SetPos(pos);
	pHitbox->SetLastPos(pos);
	pHitbox->SetSize(size);
	pHitbox->SetType(type);
	pHitbox->SetShape(CHitbox::SHAPE_BOX);
	pHitbox->SetParent(pParent);
	pHitbox->SetScore(nScore);

#ifdef _DEBUG

	D3DXVECTOR3 VtxPos[8] = {};
	VtxPos[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
	VtxPos[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
	VtxPos[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
	VtxPos[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);
	VtxPos[4] = D3DXVECTOR3(-size.x, size.y, size.z);
	VtxPos[5] = D3DXVECTOR3(size.x, size.y, size.z);
	VtxPos[6] = D3DXVECTOR3(size.x, size.y, -size.z);
	VtxPos[7] = D3DXVECTOR3(-size.x, size.y, -size.z);

	pHitbox->m_pLine[0] = CLine::Create(pos, Vec3Null, VtxPos[0], VtxPos[1], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[1] = CLine::Create(pos, Vec3Null, VtxPos[1], VtxPos[2], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[2] = CLine::Create(pos, Vec3Null, VtxPos[2], VtxPos[3], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[3] = CLine::Create(pos, Vec3Null, VtxPos[3], VtxPos[0], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	pHitbox->m_pLine[4] = CLine::Create(pos, Vec3Null, VtxPos[0], VtxPos[4], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, VtxPos[1], VtxPos[5], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[6] = CLine::Create(pos, Vec3Null, VtxPos[2], VtxPos[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[7] = CLine::Create(pos, Vec3Null, VtxPos[3], VtxPos[7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	pHitbox->m_pLine[8] = CLine::Create(pos, Vec3Null, VtxPos[4], VtxPos[5], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[9] = CLine::Create(pos, Vec3Null, VtxPos[5], VtxPos[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[10] = CLine::Create(pos, Vec3Null, VtxPos[6], VtxPos[7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, VtxPos[7], VtxPos[4], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif // !DEBUG


	return pHitbox;
}

CBoxHitbox* CBoxHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore, INTERACTION_EFFECT effect)
{
	CBoxHitbox* pHitbox = new CBoxHitbox;

	if (FAILED(pHitbox->Init()))
	{
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);
	pHitbox->SetPos(pos);
	pHitbox->SetLastPos(pos);
	pHitbox->SetSize(size);
	pHitbox->SetType(type);
	pHitbox->SetShape(CHitbox::SHAPE_BOX);
	pHitbox->SetParent(pParent);
	pHitbox->SetScore(nScore);
	pHitbox->SetEffect(effect);

#ifdef _DEBUG

	D3DXVECTOR3 VtxPos[8] = {};
	VtxPos[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
	VtxPos[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
	VtxPos[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
	VtxPos[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);
	VtxPos[4] = D3DXVECTOR3(-size.x, size.y, size.z);
	VtxPos[5] = D3DXVECTOR3(size.x, size.y, size.z);
	VtxPos[6] = D3DXVECTOR3(size.x, size.y, -size.z);
	VtxPos[7] = D3DXVECTOR3(-size.x, size.y, -size.z);

	pHitbox->m_pLine[0] = CLine::Create(pos, Vec3Null, VtxPos[0], VtxPos[1], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[1] = CLine::Create(pos, Vec3Null, VtxPos[1], VtxPos[2], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[2] = CLine::Create(pos, Vec3Null, VtxPos[2], VtxPos[3], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[3] = CLine::Create(pos, Vec3Null, VtxPos[3], VtxPos[0], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	pHitbox->m_pLine[4] = CLine::Create(pos, Vec3Null, VtxPos[0], VtxPos[4], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, VtxPos[1], VtxPos[5], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[6] = CLine::Create(pos, Vec3Null, VtxPos[2], VtxPos[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[7] = CLine::Create(pos, Vec3Null, VtxPos[3], VtxPos[7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	pHitbox->m_pLine[8] = CLine::Create(pos, Vec3Null, VtxPos[4], VtxPos[5], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[9] = CLine::Create(pos, Vec3Null, VtxPos[5], VtxPos[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[10] = CLine::Create(pos, Vec3Null, VtxPos[6], VtxPos[7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, VtxPos[7], VtxPos[4], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif // !DEBUG


	return pHitbox;
}





bool CBoxHitbox::BoxBoxHit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	//bool bInteraction = false;

	D3DXVECTOR3 thisPos = GetPos();
	D3DXVECTOR3 thisSize = GetSize();
	D3DXVECTOR3 thisLastPos = GetLastPos();

	if (thisPos.y + thisSize.y > pos.y && thisPos.y < pos.y + size.y)
	{
		D3DXVECTOR3 Vtx[4], V[4], P[4], PCtrl, R[4], RCtrl, N;
		D3DXMATRIX mtxOut, mtxTrans, mtxRot;
		float fResult;

		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);

		D3DXMatrixIdentity(&mtxOut);
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxTrans);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			D3DXVec3TransformCoord(&Vtx[nCnt], &Vtx[nCnt], &mtxOut);
		}

		V[0] = Vtx[1] - Vtx[0];
		V[1] = Vtx[2] - Vtx[1];
		V[2] = Vtx[3] - Vtx[2];
		V[3] = Vtx[0] - Vtx[3];

		P[0] = D3DXVECTOR3(thisPos.x - Vtx[0].x, 0.0f, thisPos.z - Vtx[0].z);
		P[1] = D3DXVECTOR3(thisPos.x - Vtx[1].x, 0.0f, thisPos.z - Vtx[1].z);
		P[2] = D3DXVECTOR3(thisPos.x - Vtx[2].x, 0.0f, thisPos.z - Vtx[2].z);
		P[3] = D3DXVECTOR3(thisPos.x - Vtx[3].x, 0.0f, thisPos.z - Vtx[3].z);

		D3DXVec3Cross(&R[0], &V[0], &P[0]);
		D3DXVec3Cross(&R[1], &V[1], &P[1]);
		D3DXVec3Cross(&R[2], &V[2], &P[2]);
		D3DXVec3Cross(&R[3], &V[3], &P[3]);

		if (R[0].y * R[1].y >= 0 && R[1].y * R[2].y >= 0 && R[2].y * R[3].y >= 0 && R[3].y * R[0].y >= 0)
		{
			if (thisLastPos.y >= pos.y + size.y && thisPos.y < pos.y + size.y)
			{
				thisPos.y = pos.y + size.y;

				GetParent()->SetPos(thisPos - GetRelativePos());

				return true;
			}
			else if (thisLastPos.y + thisSize.y <= pos.y && thisPos.y + thisSize.y <= pos.y)
			{
				thisPos.y = pos.y - thisSize.y;

				GetParent()->SetPos(thisPos - GetRelativePos());

				return true;
			}
			else
			{
				for (int Count = 0; Count < 4; Count++)
				{
					PCtrl = D3DXVECTOR3(thisLastPos.x - Vtx[Count].x, 0.0f, thisLastPos.z - Vtx[Count].z);
					D3DXVec3Cross(&RCtrl, &V[Count], &PCtrl);

					D3DXVECTOR3 Ctrl;

					if (RCtrl.y * R[Count].y <= 0)
					{
						P[0] = D3DXVECTOR3(thisPos.x - thisLastPos.x, 0.0f, thisPos.z - thisLastPos.z);
						P[1] = D3DXVECTOR3(Vtx[Count].x - thisLastPos.x, 0.0f, Vtx[Count].z - thisLastPos.z);
						D3DXVec3Normalize(&N, &P[0]);

						D3DXVec3Cross(&R[0], &P[1], &V[Count]);
						D3DXVec3Cross(&R[1], &N, &V[Count]);

						if (R[1].y == 0)
						{
							break;
						}

						fResult = R[0].y / R[1].y;

						if (fResult > 0)
						{
							fResult -= 0.1f;
						}
						else if (fResult < 0)
						{
							fResult += 0.1f;
						}

						D3DXVECTOR3 Cross, VtxtoPos, VtxtoCross;
						float Dot, Lenght1, Lenght2, Alpha;

						Cross = D3DXVECTOR3(thisLastPos.x + (N.x * fResult), 0.0f, thisLastPos.z + (N.z * fResult));
						VtxtoPos = D3DXVECTOR3(thisPos.x - Vtx[Count].x, 0.0f, thisPos.z - Vtx[Count].z);
						VtxtoCross = D3DXVECTOR3(Cross.x - Vtx[Count].x, 0.0f, Cross.z - Vtx[Count].z);

						D3DXVec3Normalize(&N, &VtxtoCross);

						Dot = D3DXVec3Dot(&VtxtoCross, &VtxtoPos);
						Lenght1 = sqrtf((VtxtoCross.x * VtxtoCross.x) + (VtxtoCross.z * VtxtoCross.z));
						Lenght2 = sqrtf((VtxtoPos.x * VtxtoPos.x) + (VtxtoPos.z * VtxtoPos.z));

						if ((Lenght1 * Lenght2) * (Lenght1 * Lenght2) >= Dot * Dot && Lenght1 * Lenght2 != 0)
						{
							Alpha = acosf((Dot) / (Lenght1 * Lenght2));

							fResult = (Lenght2 * cosf(Alpha));

							/*diff.x = (Vtx[Count].x + (N.x * fResult)) - thisPos.x;
							diff.z = (Vtx[Count].z + (N.z * fResult)) - thisPos.z;*/

							thisPos.x = Vtx[Count].x + (N.x * fResult);
							thisPos.z = Vtx[Count].z + (N.z * fResult);
						}
						else
						{
							/*diff.x = (thisLastPos.x + (N.x * fResult)) - thisPos.x;
							diff.z = (thisLastPos.z + (N.z * fResult)) - thisPos.z;*/

							thisPos.x = thisLastPos.x + (N.x * fResult);
							thisPos.z = thisLastPos.z + (N.z * fResult);
						}

						break;
					}
				}

				if (GetParent() != nullptr)
				{
					GetParent()->SetPos(thisPos - GetRelativePos());
				}

				return true;
			}
		}
	}

	return false;
}



