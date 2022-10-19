//============================================================================
//
//カメラの処理[camera.cpp] (ファイルヘッダコメント)
//Author:谷本康輔
//============================================================================
#include "camera.h"		//作成したcamera.hをインクルードする
#include "input.h"		//作成したinput.hをインクルードする
#include "application.h"
#include "player.h"
#include "debugproc.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CCamera::CCamera()
{

}

//=====================================
// デストラクタ
//=====================================
CCamera::~CCamera()
{

}

//============================================================================
//カメラの初期化処理
//============================================================================
void CCamera::Init()
{
	//始点・注視点・上方向を設定する
	m_posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視点から注視点の距離
	m_fDistance = sqrtf(powf(m_posR.x - m_posV.x, 2) + powf(m_posR.z - m_posV.z, 2));
	m_bFollowUse = false;
}

//============================================================================
//カメラの終了処理
//============================================================================
void CCamera::Uninit()
{

}

//============================================================================
//カメラの更新処理
//============================================================================
void CCamera::Update()
{
	Input();

	//++++++++++++++++++++++++++++++++++++
	// 角度の正規化
	//++++++++++++++++++++++++++++++++++++
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}
	//++++++++++++++++++++++++++++++++++++
	// カメラ追従
	//++++++++++++++++++++++++++++++++++++
	if (m_bFollowUse)
	{
		CObject *pCenter = (CObject*)CObjectX::GetTop(OBJECT_PRIORITY_CENTER);	//オブジェクトの先頭ポインタ
		if (pCenter != nullptr)
		{
			//現在位置ポインタに先頭ポインタを代入
			CObject *pObject = pCenter;

			//現在位置ポインタが使用中の場合
			while (pObject != nullptr)
			{
				CObject::Object_Type objtype = pObject->GetType();

				if (objtype == CObject::TYPE_PLAYER)
				{
					D3DXVECTOR3 pos = pCenter->GetPos();
					D3DXVECTOR3 rot = pCenter->GetRot();

					m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					m_posRDest.x = pos.x + sinf(rot.x);
					//m_posRDest.y = pos.y + cosf(rot.y + D3DX_PI);
					m_posRDest.z = pos.z + cosf(rot.z);

					m_posVDest.x = pos.x + sinf(rot.x) ;
					//m_posVDest.y = pos.y - cosf(rot.x) * -m_fDistance;
					m_posVDest.z = pos.z + cosf(rot.z);

					m_posR.x += (m_posRDest.x - m_posR.x);
					//m_posR.y += (m_posRDest.y - m_posR.y) / 2;
					m_posR.z += (m_posRDest.z - m_posR.z);

					m_posV.x += (m_posVDest.x - m_posV.x);
					//m_posV.y += (m_posVDest.y - m_posV.y) / 2;
					m_posV.z += (m_posVDest.z - m_posV.z) - 400.0f;

					//m_rotDest.y = rot.y + D3DX_PI;
				}
				//現在位置ポインタに次回ポインタを代入する(ポインタを進める処理)
				pObject = pObject->GetNext();
			}
		}
	}
	//CDebugProc::Print("現在の角度x : %f\n現在の角度y : %f\n現在の角度z : %f\n", m_rot.x, m_rot.y, m_rot.z);
}

//=====================================
//入力処理
//=====================================
void CCamera::Input()
{
	//キーボード取得
	CInput *pCInput = CApplication::GetInput();

	//カメラ追従判定切り替え
	if (pCInput->GetKeyboardTrigger(DIK_F2))
	{
		m_bFollowUse = !m_bFollowUse;
	}

	//視点 & 注視点の同時移動
	if (pCInput->GetKeyboardPress(DIK_LEFT) == true)
	{//カメラ左移動
		m_posV.x -= sinf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posR.x -= sinf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posV.z -= cosf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posR.z -= cosf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
	}
	else if (pCInput->GetKeyboardPress(DIK_RIGHT))
	{//カメラ右移動
		m_posV.x += sinf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posR.x += sinf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posV.z += cosf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
		m_posR.z += cosf(m_rot.y + (D3DX_PI / 2)) * CAMERA_SPEAD;
	}
	if (pCInput->GetKeyboardPress(DIK_UP) == true)
	{//カメラ前方移動
		m_posV.x += sinf(m_rot.y) * CAMERA_SPEAD;
		m_posR.x += sinf(m_rot.y) * CAMERA_SPEAD;
		m_posV.z += cosf(m_rot.y) * CAMERA_SPEAD;
		m_posR.z += cosf(m_rot.y) * CAMERA_SPEAD;
	}
	else if (pCInput->GetKeyboardPress(DIK_DOWN) == true)
	{//カメラ後方移動
		m_posV.x -= sinf(m_rot.y) * CAMERA_SPEAD;
		m_posR.x -= sinf(m_rot.y) * CAMERA_SPEAD;
		m_posV.z -= cosf(m_rot.y) * CAMERA_SPEAD;
		m_posR.z -= cosf(m_rot.y) * CAMERA_SPEAD;
	}
	if (pCInput->GetKeyboardPress(DIK_U) == true)
	{//カメラ上移動
		m_posV.y += 1;
		m_posR.y++;
		m_posV.x -= sinf(m_rot.y) * CAMERA_SPEAD;
		m_posR.x -= sinf(m_rot.y) * CAMERA_SPEAD;
		m_posV.z -= cosf(m_rot.y) * CAMERA_SPEAD;
		m_posR.z -= cosf(m_rot.y) * CAMERA_SPEAD;
	}
	else if (pCInput->GetKeyboardPress(DIK_O) == true)
	{//カメラ下移動
		m_posV.y -= 1;
		m_posR.y--;
		m_posV.x += sinf(m_rot.y) * CAMERA_SPEAD;
		m_posR.x += sinf(m_rot.y) * CAMERA_SPEAD;
		m_posV.z += cosf(m_rot.y) * CAMERA_SPEAD;
		m_posR.z += cosf(m_rot.y) * CAMERA_SPEAD;
	}

	//注視点の旋回
	if (pCInput->GetKeyboardPress(DIK_Z) == true)
	{//左回り
		m_rot.y -= 0.1f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	else if (pCInput->GetKeyboardPress(DIK_X) == true)
	{//右回り
		m_rot.y += 0.1f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}

	//視点の旋回
	if (pCInput->GetKeyboardPress(DIK_C) == true)
	{//左回り
		m_rot.y += 0.1f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
	else if (pCInput->GetKeyboardPress(DIK_V) == true)
	{//右回り
		m_rot.y -= 0.1f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
}

//============================================================================
//カメラの設定処理
//============================================================================
void CCamera::SetCamera(LPDIRECT3DDEVICE9 device)
{
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU
	);

	//ビューマトリックスの設定
	device->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//アスペクト比
		CAMERA_NEAR,CAMERA_FAR
	);
	//プロジェクションマトリックスの設定
	device->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//g_aCamera.bFollowUse = true;
}