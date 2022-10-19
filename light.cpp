//============================================================================
//
//ライトの処理[light.cpp] (ファイルヘッダコメント)
//Author:谷本康輔
//============================================================================
#include "light.h"
#include "input.h"		//作成したinput.hをインクルードする
#include "application.h"
#include "renderer.h"

//============================================================================
//ライトの初期化処理
//============================================================================
void CLight::Init()
{
	//ライトをクリアする
	ZeroMemory(&m_light[0], sizeof(m_light));

	//ライトの方向を設定
	D3DXVECTOR3 vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	//正規化する(大きさ1のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[0].Direction = vecDir;

	m_light[1].Direction = D3DXVECTOR3(-0.2f, -0.8f, 0.4f);
	m_light[2].Direction = D3DXVECTOR3(0.0f, 0.8f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	for (int nCnt = 0;nCnt < MAX_LIGHT; nCnt++)
	{
		//ライトの種類を設定(平行光源)
		m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;		
		//ライトの拡散光を設定(ライトの色)
		m_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	

		//ライトを設定する
		pDevice->SetLight(nCnt, &m_light[nCnt]);

		//ライトを有効にする
		pDevice->LightEnable(nCnt, TRUE);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================================================
//ライトの終了処理
//============================================================================
void CLight::Uninit()
{

}

//============================================================================
//ライトの更新処理
//============================================================================
void CLight::Update()
{

}