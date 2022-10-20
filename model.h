//============================================================================
//
// モデル
// Author:谷本康輔
//
//============================================================================
#ifndef _MODEL_H_		//このマクロ定義がされてなかったら
#define _MODEL_H_		//2連インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//---------------------------
//クラス
//---------------------------
class CModel
{
public:
	CModel();
	~CModel();

	void Init(char *xFail);
	void Init();
	void Uninit();
	void Update();
	void Draw();

	static CModel *Create(D3DXVECTOR3 pos, char *xFail);

	void SetParent(CModel* pModel) { m_pParent = pModel; }
	virtual void SetWorldMtx(D3DXMATRIX worldmtx) { m_worldmtx = worldmtx; }
	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXMATRIX& GetWorldMtx() const { return m_worldmtx; }
private:
	//****************************************************************************
	//構造体定義
	//****************************************************************************
	//typedef struct
	//{
	//	LPD3DXMESH pMesh;
	//	LPD3DXBUFFER pBuffMat;
	//	DWORD nNumMat;
	//	LPDIRECT3DTEXTURE9 g_pTexture[IMAGE_PLAYER];
	//	D3DXMATRIX Worldmtx;	//ワールドマトリックス
	//	D3DXVECTOR3 pos;		//頂点座標
	//	D3DXVECTOR3 rot;		//向き
	//	float fFrame;			//フレーム数
	//	int nIdxModelParent;	//親モデルのインデックス
	//}PLAYER_PARTS;
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_nNumMat;
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_rot;					//角度
	D3DXMATRIX m_worldmtx;				//ワールドマトリックス
	CModel *m_pParent;
};
#endif// !_PLAYER_H_

