//=============================================================================
//
// オブジェクトX
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//オブジェクトXクラス
class CObjectX : public CObject
{
public:
	CObjectX(int list = 0);
	~CObjectX() override;

	void Init(char *xFail);
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetType(Object_Type type);
	void SetSize(float fWidth, float fHeight);
	static CObjectX *Create(D3DXVECTOR3 pos, char *xFail);

	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetNor(D3DXVECTOR3 nor) { m_nor = nor; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	virtual void SetWorldMtx(D3DXMATRIX worldmtx) { m_worldmtx = worldmtx; }
	virtual void SetWidth(float fWidth) { m_fWidth = fWidth; }
	virtual void SetHeight(float fHeight) { m_fHeight = fHeight; }
	virtual void SetPalentY(float fPalentY) { m_fPalentY = fPalentY; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetNor() const { return m_nor; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXMATRIX& GetWorldMtx() const { return m_worldmtx; }
	const float GetWidth() const { return m_fWidth; }
	const float GetHeight() const { return m_fHeight; }
	const float GetLength() const { return m_fLength; }
private:
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_nNumMat;
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_nor;					//法線ベクトル
	D3DXVECTOR3 m_rot;					//角度
	D3DXMATRIX m_worldmtx;				//ワールドマトリックス
	float m_fWidth;						//長さ横
	float m_fHeight;					//長さ縦
	float m_fLength;					//長さ(スクウェアルート)
	float m_fAngle;						//角度(アークタンジェント)
	float m_fPalentY;					//親モデル位置の高さ
};

#endif // !_OBJECTX_H_