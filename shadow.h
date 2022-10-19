//=============================================================================
//
// 影
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "Object3D.h"

//---------------------------
//マクロ関数
//---------------------------
#define MAX_SHADOW				(1)		//影の最大数
#define SHADOW_WIDTH			(10)	//影画像の横幅
#define SHADOW_HEIGHT			(10)	//影画像の縦幅

//---------------------------
//クラス
//---------------------------
class CShadow : public CObject3D
{
public:
	CShadow();
	~CShadow() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetShadow(D3DXVECTOR3 pos);

	static CShadow *Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_move;		//移動量
	D3DXMATRIX m_worldmtx;//ワールドマトリックス
	float m_fWidth;			//長さ横
	float m_fHeight;		//長さ縦
};

#endif // !_SHADOW_H_