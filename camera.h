//============================================================================
//
//
// カメラの処理
// Author:谷本康輔
//
//============================================================================
#ifndef _CAMERA_H_						//このマクロ定義がされてなかったら
#define _CAMERA_H_						//2連インクルード防止のマクロ定義

#include <d3dx9.h>

//****************************************************************************
//マクロ定義
//****************************************************************************
#define CAMERA_NEAR				(10)	//カメラのニアー
#define CAMERA_FAR				(3000)	//カメラのファー
#define CAMERA_SPEAD			(2)		//カメラの移動速度

class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init();
	void Uninit();
	void Update();
	void Input();
	void SetCamera(LPDIRECT3DDEVICE9 device);
	D3DXVECTOR3 GetRot() { return m_rot; }
	D3DXVECTOR3 GetRotDest() { return m_rotDest; }
private:
	//****************************************************************************
	//構造体定義
	//****************************************************************************
	D3DXVECTOR3 m_posV;			//視点
	D3DXVECTOR3 m_posR;			//注視点
	D3DXVECTOR3 m_vecU;			//上方向ベクトル
	D3DXVECTOR3 m_rot;			//方向
	D3DXVECTOR3 m_posVDest;		//目的の視点
	D3DXVECTOR3 m_posRDest;		//目的の注視点
	D3DXVECTOR3 m_rotDest;		//目的の方向
	D3DXVECTOR3 m_move;			//移動量
	D3DXMATRIX m_mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		//ビューマトリックス
	float m_fDistance;			//視点から注視点の距離
	bool m_bFollowUse;			//追従機能判定
};
#endif #pragma once
