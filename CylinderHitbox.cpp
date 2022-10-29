//=============================================================================
//
// hitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "CylinderHitbox.h"
#include "line.h"

//コンストラクタ
CCylinderHitbox::CCylinderHitbox()
{
	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		m_pLine[nCnt] = nullptr;
	}
}

//デストラクタ
CCylinderHitbox::~CCylinderHitbox()
{

}

//初期化処理
HRESULT CCylinderHitbox::Init(void)
{
	if (FAILED(CHitbox::Init()))
	{
		return -1;
	}

	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		m_pLine[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CCylinderHitbox::Uninit(void)
{
	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		if (m_pLine[nCnt] != nullptr)
		{
			m_pLine[nCnt]->Release();
			m_pLine[nCnt] = nullptr;
		}
	}

	CHitbox::Uninit();
}

//更新処理
void CCylinderHitbox::Update(void)
{
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
				//CylinderBoxHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetRot(), pHbx->data()[nCnt]->GetSize());
				if (PointBoxHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetRot(), pHbx->data()[nCnt]->GetSize()))
				{
					pHbx->data()[nCnt]->SetCollisionState(true);
				}
			}

				break;

			case CHitbox::SHAPE_CYLINDER:

			{
				if (CylinderCylinderHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetSize()))
				{
					pHbx->data()[nCnt]->SetCollisionState(true);
				}
			}

				break;

			default:
				break;
			}
		}
	}

	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		if (m_pLine[nCnt] != nullptr)
		{
			m_pLine[nCnt]->SetPos(GetPos());
		}
	}

	CHitbox::Update();
}





CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent)
{
	CCylinderHitbox* pHitbox = new CCylinderHitbox;

	if (FAILED(pHitbox->Init()))
	{
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);
	pHitbox->SetPos(pos);
	pHitbox->SetLastPos(pos);
	pHitbox->SetSize(size);
	pHitbox->SetType(type);
	pHitbox->SetShape(CHitbox::SHAPE_CYLINDER);
	pHitbox->SetParent(pParent);

#ifdef _DEBUG

	D3DXVECTOR3 Vtx[12];

	for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			Vtx[(nCnt2 * 6) + nCnt] = D3DXVECTOR3(size.x * cosf((2.0f * D3DX_PI * nCnt) / 6), size.y * nCnt2, size.z * sinf((2.0f * D3DX_PI * nCnt) / 6));
		}
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		pHitbox->m_pLine[nCnt] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 1], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 6] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 6], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 12] = CLine::Create(pos, Vec3Null, Vtx[nCnt + 6], Vtx[nCnt + 7], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[0], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[11], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[17] = CLine::Create(pos, Vec3Null, Vtx[11], Vtx[6], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

#endif // !_DEBUG

	return pHitbox;
}







bool CCylinderHitbox::CylinderCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	D3DXVECTOR3 thisPos, thisSize;
	thisPos = GetPos();
	thisSize = GetSize();

	float fTop, fBottom;

	fTop = pos.y + size.y;
	fBottom = pos.y;

	if (fTop >= thisPos.y && fBottom <= thisPos.y + thisSize.y)
	{
		float fDistance, fRadius;
		fDistance = sqrtf(((pos.x - thisPos.x) * (pos.x - thisPos.x)) + ((pos.z - thisPos.z) * (pos.z - thisPos.z)));
		fRadius = size.x + thisSize.x;

		if (fDistance < fRadius)
		{
			D3DXVECTOR3 thisLast = GetLastPos();
			D3DXVECTOR3 parentPos = GetParent()->GetPos();

			if (thisLast.y + thisSize.y <= pos.y)
			{
				thisPos.y = (pos.y - thisSize.y - 0.01f);
				parentPos = thisPos - GetRelativePos();
				GetParent()->SetPos(parentPos);
				SetLastPos(thisPos);
			}
			else if (thisLast.y >= pos.y + size.y)
			{
				thisPos.y = (pos.y + size.y + 0.01f);
				parentPos = thisPos - GetRelativePos();
				GetParent()->SetPos(parentPos);
				SetLastPos(thisPos);
			}
			else
			{
				D3DXVECTOR3 dist = thisPos - pos;
				float fHeight = parentPos.y;
				dist.y = 0.0f;
				D3DXVec3Normalize(&dist, &dist);
				dist.x *= fRadius + 0.001f;
				dist.z *= fRadius + 0.001f;
				dist.x += pos.x;
				dist.z += pos.z;
				parentPos = dist - GetRelativePos();
				parentPos.y = fHeight;
				GetParent()->SetPos(parentPos);
				SetLastPos(parentPos + GetRelativePos());
			}

			return true;
		}
	}

	return false;
}


bool CCylinderHitbox::CylinderBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	D3DXVECTOR3 thisPos = GetPos();
	D3DXVECTOR3 thisSize = GetSize();

	if (thisPos.y + thisSize.y >= pos.y && thisPos.y <= pos.y + size.y)
	{
		D3DXVECTOR3 Vtx[4] = {};
		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);

		D3DXMATRIX mtxW, mtxRot, MtxTrans;
		D3DXMatrixIdentity(&mtxW);
		D3DXMatrixTranslation(&MtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxW, &mtxW, &MtxTrans);
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxW, &mtxW, &mtxRot);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			D3DXVec3TransformCoord(&Vtx[nCnt], &Vtx[nCnt], &mtxW);
		}

		D3DXVECTOR3 edgeVector[4], ObjVector[4], Cross[4];

		edgeVector[0] = Vtx[1] - Vtx[0];
		edgeVector[1] = Vtx[2] - Vtx[1];
		edgeVector[2] = Vtx[3] - Vtx[2];
		edgeVector[3] = Vtx[0] - Vtx[3];

		D3DXVECTOR3 YVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVECTOR3 Normal[4] = {};
		D3DXVECTOR3 nearPoint[4] = {};

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			/*D3DXVECTOR3 vDis = thisPos - pos;
			vDis.y = 0.0f;
			D3DXVec3Normalize(&vDis, &vDis);*/
			D3DXVECTOR3 normCross = Vec3Null;
			D3DXVec3Cross(&Normal[nCnt], &edgeVector[nCnt], &YVector);
			D3DXVec3Normalize(&Normal[nCnt], &Normal[nCnt]);
			D3DXVec3Cross(&normCross, &edgeVector[nCnt], &Normal[nCnt]);

			if (normCross.y > 0.0f)
			{
				Normal[nCnt].x *= -1.0f;
				Normal[nCnt].y *= -1.0f;
				Normal[nCnt].z *= -1.0f;
			}

			nearPoint[nCnt] = thisPos + D3DXVECTOR3(Normal[nCnt].x * thisSize.x /** 0.5f*/, 0.0f, Normal[nCnt].z * thisSize.z /** 0.5f*/);
		}
		int nIdx = 0;
		int nVtxIdx = 0;
		bool bInt = false;

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			ObjVector[0] = nearPoint[nCnt] - Vtx[0];
			ObjVector[1] = nearPoint[nCnt] - Vtx[1];
			ObjVector[2] = nearPoint[nCnt] - Vtx[2];
			ObjVector[3] = nearPoint[nCnt] - Vtx[3];

			ObjVector[0].y = 0.0f;
			ObjVector[1].y = 0.0f;
			ObjVector[2].y = 0.0f;
			ObjVector[3].y = 0.0f;

			D3DXVec3Cross(&Cross[0], &edgeVector[0], &ObjVector[0]);
			D3DXVec3Cross(&Cross[1], &edgeVector[1], &ObjVector[1]);
			D3DXVec3Cross(&Cross[2], &edgeVector[2], &ObjVector[2]);
			D3DXVec3Cross(&Cross[3], &edgeVector[3], &ObjVector[3]);

			if (Cross[0].y * Cross[1].y >= 0 && Cross[0].y * Cross[2].y >= 0 && Cross[0].y * Cross[3].y >= 0 && Cross[1].y * Cross[2].y >= 0 && Cross[1].y * Cross[3].y >= 0 && Cross[2].y * Cross[3].y >= 0)
			{
				nIdx = nCnt;
				bInt = true;
				nVtxIdx = nCnt + 2;

				if (nVtxIdx >= 4)
				{
					nVtxIdx -= 4;
				}

				break;
			}
		}
		if (bInt)
		{
			D3DXVECTOR3 LastPos = GetLastPos();
			D3DXVECTOR3 parentPos = GetParent()->GetPos();

			if (LastPos.y >= pos.y + size.y)
			{
				//D3DXVECTOR3 diff = Vec3Null;
				//diff.y = (pos.y + size.y) - thisPos.y;
				thisPos.y = pos.y + size.y + 0.001f;
				//SetPos(thisPos);
				parentPos = thisPos - GetRelativePos();
				GetParent()->SetPos(parentPos);
			}
			else if (LastPos.y + thisSize.y <= pos.y)
			{
				//D3DXVECTOR3 diff = Vec3Null;
				//diff.y = (pos.y - thisSize.y) - thisPos.y;
				thisPos.y = (pos.y - thisSize.y) - 0.0001f;
				//SetPos(thisPos);
				parentPos = thisPos - GetRelativePos();
				GetParent()->SetPos(parentPos);
			}
			else
			{
				D3DXVECTOR3 Center = thisPos - Vtx[nVtxIdx];
				Center.y = 0.0f;
				D3DXVECTOR3 radius = nearPoint[nIdx] - thisPos;
				radius.y = 0.0f;
				D3DXVECTOR3 versRad = Vec3Null;
				D3DXVec3Normalize(&versRad, &radius);

				D3DXVECTOR3 c[2] = {};
				D3DXVec3Cross(&c[0], &Center, &edgeVector[nVtxIdx]);
				D3DXVec3Cross(&c[1], &versRad, &edgeVector[nVtxIdx]);
				float f1, f2;
				f1 = D3DXVec3Length(&c[1]);
				f2 = D3DXVec3Length(&c[0]);

				if (f2 == 0.0f)
				{
					return false;
				}

				float fK = f1 / f2;

				D3DXVECTOR3 edgeNormal = Vec3Null, dir = Vec3Null;
				D3DXVec3Normalize(&edgeNormal, &edgeVector[nVtxIdx]);
				dir = thisPos - GetLastPos();
				dir.y = 0.0f;
				D3DXVec3Normalize(&dir, &dir);
				
				float fAngle, fLength;

				fAngle = acosf(D3DXVec3Dot(&edgeNormal, &dir));

				D3DXVECTOR3 T = D3DXVECTOR3(thisPos.x + (versRad.x * fK), 0.0f, thisPos.z + (versRad.z * fK));
				D3DXVECTOR3 TVec = nearPoint[nIdx] - T;
				TVec.y = 0.0f;
				fLength = D3DXVec3Length(&TVec);

				D3DXVECTOR3 newPos = nearPoint[nIdx] + D3DXVECTOR3(0.001f + Normal[nVtxIdx].x/* * (thisSize.x * 0.25f)*/, 0.0f, 0.001f + Normal[nVtxIdx].z /** (thisSize.z * 0.25f)*/) + D3DXVECTOR3(Normal[nVtxIdx].x * (fLength + 0.001f) * sinf(fAngle), 0.0f, Normal[nVtxIdx].z * (fLength + 0.001f) * sinf(fAngle));

				GetParent()->SetPos(newPos - GetRelativePos());

			}


			return true;
		}
	}

	return false;
}

bool CCylinderHitbox::PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
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
				thisPos.y = pos.y + size.y + 0.01f;
				SetLastPos(thisPos);

				GetParent()->SetPos(thisPos - GetRelativePos());

				return true;
			}
			else if (thisLastPos.y + thisSize.y <= pos.y && thisPos.y + thisSize.y > pos.y)
			{
				thisPos.y = pos.y - thisSize.y - 0.01f;

				SetLastPos(thisPos);
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
							fResult -= 0.001f;
						}
						else if (fResult < 0)
						{
							fResult += 0.001f;
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


							thisPos.x = Vtx[Count].x + (N.x * (fResult));
							thisPos.z = Vtx[Count].z + (N.z * (fResult));
						}
						else
						{

							thisPos.x = thisLastPos.x + (N.x * fResult);
							thisPos.z = thisLastPos.z + (N.z * fResult);
						}

						break;
					}
				}

				GetParent()->SetPos(thisPos - GetRelativePos());
				SetLastPos(thisPos);
				SetPos(thisPos);

				return true;
			}
		}
	}

	return false;
}