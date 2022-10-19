//=============================================================================
//
// オブジェクト3D
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//オブジェクト3Dクラス
class CObject3D : public CObject
{
public:
	CObject3D(int priority = 0);
	~CObject3D() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetUV();
	void SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3);
	void SetColor(D3DXCOLOR col);

	void SetType(Object_Type type);
	void SetSize(float fWidth, float fHeight);
	static CObject3D *Create(D3DXVECTOR3 pos);

	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetNor(D3DXVECTOR3 nor) { m_nor = nor; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	virtual void SetWorldMtx(D3DXMATRIX worldmtx) { m_worldmtx = worldmtx; }
	virtual void SetWidth(float fWidth) { m_fWidth = fWidth; }
	virtual void SetHeight(float fHeight) { m_fHeight = fHeight; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetNor() const { return m_nor; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXMATRIX& GetWorldMtx() const { return m_worldmtx; }
	const float GetWidth() const { return m_fWidth; }
	const float GetHeight() const { return m_fHeight; }
	const float GetLength() const { return m_fLength; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファ
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_nor;					//法線ベクトル
	D3DXVECTOR3 m_rot;					//角度
	D3DXMATRIX m_worldmtx;				//ワールドマトリックス
	float m_fWidth;						//長さ横
	float m_fHeight;					//長さ縦
	float m_fLength;					//長さ(スクウェアルート)
	float m_fAngle;						//角度(アークタンジェント)
};

#endif // !_OBJECT3D_H_