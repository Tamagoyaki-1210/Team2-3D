//============================================================================
//
//
// メッシュポリゴンの処理
// Author:谷本康輔
//
//============================================================================
#ifndef _MESHFIELD_H_						//このマクロ定義がされてなかったら
#define _MESHFIELD_H_						//2連インクルード防止のマクロ定義

#include "object.h"
//****************************************************************************
//マクロ定義
//****************************************************************************
#define MESHFIELD_WIDTH			(50)	//メッシュポリゴンの横幅
#define MESHFIELD_HEIGHT		(50)	//メッシュポリゴンの縦幅
#define MAX_MESHFIELD			(20)		//メッシュのポリゴン最大数


class CMeshField : CObject
{
public:
	CMeshField(int list = 0);
	~CMeshField() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	bool FieldCollision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld);

	float GetVecNor() { return m_fVecNor; }

	void SetMesh();
	void SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3);
	void SetColor(D3DXCOLOR col);

	void SetType(Object_Type type);
	void SetSize(float fWidth, float fHeight);
	static CMeshField *Create(D3DXVECTOR3 pos);

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
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//インデックスバッファ
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_nor;					//法線ベクトル
	D3DXVECTOR3 m_rot;					//角度
	D3DXMATRIX m_worldmtx;				//ワールドマトリックス
	float m_fWidth;						//長さ横
	float m_fHeight;					//長さ縦
	float m_fLength;					//長さ(スクウェアルート)
	float m_fAngle;						//角度(アークタンジェント)

	int m_nDebug;
	int m_nMeshPlimitive;
	int m_nMeshVertex;
	int m_nMeshIndex;		//軸の合計数
	int m_nMeshX;			//x軸の個数
	int m_nMeshZ;			//z軸の個数

	float m_fVecNor;		//メッシュ法線ベクトル
	float m_fVecVtx[MESHFIELD_WIDTH * MESHFIELD_HEIGHT];		//頂点毎の法線ベクトルの配列
};
#endif