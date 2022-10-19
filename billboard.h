//============================================================================
//
//
// ビルボード描画
// Author:谷本康輔
//
//============================================================================
#ifndef _BILLBOARD_H_						//このマクロ定義がされてなかったら
#define _BILLBOARD_H_						//2連インクルード防止のマクロ定義

#include "object.h"

//****************************************************************************
//マクロ定義
//****************************************************************************
#define MAX_BILLBOARD				(4)		//ビルボードの最大設置数
#define IMAGE_BILLBOARD				(2)		//ビルボードの画像数
#define BILLBOARD_BULLET_WIDTH		(10)	//ビルボードの横幅(弾)
#define BILLBOARD_BULLET_HEIGHT		(10)	//ビルボードの縦幅(弾)
#define BILLBOARD_TREE_WIDTH		(25)	//ビルボードの横幅(木)
#define BILLBOARD_TREE_HEIGHT		(30)	//ビルボードの縦幅(木)

class CBillBoard : CObject
{
public:
	CBillBoard(int list = 0);
	~CBillBoard() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetUV();
	void SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3);
	void SetColor(D3DXCOLOR col);

	void SetType(Object_Type type);
	void SetSize(float fWidth, float fHeight);
	static CBillBoard *Create(D3DXVECTOR3 pos);

	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetNor(D3DXVECTOR3 nor) { m_nor = nor; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	virtual void SetWorldMtx(D3DXMATRIX worldmtx) { m_worldmtx = worldmtx; }
	virtual void SetWidth(float fWidth) { m_fWidth = fWidth; }
	virtual void SetHeight(float fHeight) { m_fHeight = fHeight; }
	virtual void SetLength(float fLength) { m_fLength = fLength; }
	virtual void SetAngle(float fAngle) { m_fAngle = fAngle; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetNor() const { return m_nor; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXMATRIX& GetWorldMtx() const { return m_worldmtx; }
	const float GetWidth() const { return m_fWidth; }
	const float GetHeight() const { return m_fHeight; }
	const float GetLength() const { return m_fLength; }
	const bool GetUse() const { return m_bUse; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//Bufferオブジェクト
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_nor;					//法線ベクトル
	D3DXVECTOR3 m_rot;					//角度
	D3DXMATRIX m_worldmtx;				//ワールドマトリックス
	float m_fWidth;						//長さ横
	float m_fHeight;					//長さ縦
	float m_fLength;					//長さ(スクウェアルート)
	float m_fAngle;						//角度(アークタンジェント)
	bool m_bUse;						//使用判定
};
#endif 