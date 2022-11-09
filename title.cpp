//=============================================================================
//
// title.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "title.h"
#include "Application.h"
#include "meshfield.h"
#include "camera.h"
#include "playerModel.h"
#include "AnimateUI.h"
#include "halfsphere.h"
#include "model.h"
#include "coin.h"
#include "SpikeBall.h"
#include "bouncePole.h"
#include "lavaFloor.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CTitle::CTitle()
{
	for (int nCnt = 0; nCnt < MAX_TITLE_MODEL; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}

	m_pTitle = nullptr;
}

//=====================================
// デストラクタ
//=====================================
CTitle::~CTitle()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CTitle::Init(void)
{
	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-200.0f, 0.0f, 2500.0f), Vec3Null, D3DXVECTOR2(100.0f, 1000.0f), 30, 5);
	pField->SetTexture(CObject::TEXTURE_BLOCK);
	pField->SetTextureTiling(D3DXVECTOR2(1.0f, 10.0f));

	if (CApplication::GetCamera() != nullptr)
	{
		CApplication::GetCamera()->SetPos(D3DXVECTOR3(0.0f, 200.0f, -600.0f), D3DXVECTOR3(0.0f, -0.0f, 0.0f));
	}

	CHalfSphere* pSphere = CHalfSphere::Create(D3DXVECTOR3(0.0f, -8000.0f, 1000.0f), D3DXVECTOR3(30000.0f, 0.0f, 30000.0f), D3DXVECTOR3(D3DX_PI * -0.15f, D3DX_PI, 0.0f), CHalfSphere::SPHERE_UP);

	pSphere->LoadTexture("data\\TEXTURE\\sky002.jpg");

	m_pModel[0] = CPlayerModel::Create(D3DXVECTOR3(-125.0f, 50.0f, -280.0f), 0, false);
	m_pModel[1] = CPlayerModel::Create(D3DXVECTOR3(-37.5f, 50.0f, -280.0f), 1, false);
	m_pModel[2] = CPlayerModel::Create(D3DXVECTOR3(37.5f, 50.0f, -280.0f), 2, false);
	m_pModel[3] = CPlayerModel::Create(D3DXVECTOR3(125.0f, 50.0f, -280.0f), 3, false);

	CAnimateUI::UIAnimation animInfo;
	animInfo.deltaSize = D3DXVECTOR2(1.0f, 0.5f);
	animInfo.nChangeTime = 60;

	m_pTitle = CAnimateUI::Create(CObject::TEXTURE_TITLE_UI, D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.25f, 0.0f), D3DXVECTOR2(320.0f, 160.0f),
		ColorWhite, animInfo);

	CModel* pModel = CModel::Create(CModel::MODEL_WINDMILL, D3DXVECTOR3(0.0f, -100.0f, 2000.0f));
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	pModel->SetShadowDraw(false);

	pModel = CModel::Create(CModel::MODEL_BALLOON, D3DXVECTOR3(700.0f, -250.0f, 600.0f));
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.25f, 0.0f));
	pModel->SetShadowDraw(false);

	pModel = CModel::Create(CModel::MODEL_BALLOON, D3DXVECTOR3(-500.0f, -50.0f, 800.0f));
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.15f, 0.0f));
	pModel->SetModelColor(1, D3DXCOLOR(0.75f, 0.2f, 0.75f, 1.0f));
	pModel->SetShadowDraw(false);

	pModel = CModel::Create(CModel::MODEL_BALLOON, D3DXVECTOR3(-300.0f, -90.0f, -250.0f));
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.15f, 0.0f));
	pModel->SetModelColor(1, D3DXCOLOR(0.10f, 1.0f, 0.8f, 1.0f));
	pModel->SetShadowDraw(false);

	pModel = CModel::Create(CModel::MODEL_BALLOON, D3DXVECTOR3(1300.0f, 100.0f, 1300.0f));
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.85f, 0.0f));
	pModel->SetModelColor(1, D3DXCOLOR(0.10f, 1.0f, 0.2f, 1.0f));
	pModel->SetShadowDraw(false);

	CCoin::Create(D3DXVECTOR3(-125.0f, 75.0f, -200.0f), CCoin::COIN_0);
	CCoin::Create(D3DXVECTOR3(-125.0f, 75.0f, -225.0f), CCoin::COIN_0);
	CCoin::Create(D3DXVECTOR3(-100.0f, 75.0f, -225.0f), CCoin::COIN_0);
	CCoin::Create(D3DXVECTOR3(-100.0f, 75.0f, -200.0f), CCoin::COIN_0);

	CCoin::Create(D3DXVECTOR3(- 50.0f, 75.0f, -150.0f), CCoin::COIN_1);
	CCoin::Create(D3DXVECTOR3(- 50.0f, 75.0f, -175.0f), CCoin::COIN_1);
	CCoin::Create(D3DXVECTOR3(- 25.0f, 75.0f, -175.0f), CCoin::COIN_1);
	CCoin::Create(D3DXVECTOR3(- 25.0f, 75.0f, -150.0f), CCoin::COIN_1);

	CCoin::Create(D3DXVECTOR3(50.0f, 75.0f, -150.0f), CCoin::COIN_2);
	CCoin::Create(D3DXVECTOR3(50.0f, 75.0f, -175.0f), CCoin::COIN_2);
	CCoin::Create(D3DXVECTOR3(25.0f, 75.0f, -175.0f), CCoin::COIN_2);
	CCoin::Create(D3DXVECTOR3(25.0f, 75.0f, -150.0f), CCoin::COIN_2);

	CCoin::Create(D3DXVECTOR3(125.0f, 75.0f, -200.0f), CCoin::COIN_3);
	CCoin::Create(D3DXVECTOR3(125.0f, 75.0f, -225.0f), CCoin::COIN_3);
	CCoin::Create(D3DXVECTOR3(100.0f, 75.0f, -225.0f), CCoin::COIN_3);
	CCoin::Create(D3DXVECTOR3(100.0f, 75.0f, -200.0f), CCoin::COIN_3);

	CSpikeBall::Create(D3DXVECTOR3(-75.0f, 75.0f, -400.0f));
	CSpikeBall::Create(D3DXVECTOR3( 75.0f, 75.0f, -400.0f));

	CBouncePole::Create(D3DXVECTOR3(-90.0f, 75.0f, 300.0f));

	/*CLavaFloor::Create(D3DXVECTOR3(-175.0f, 50.0f, -420.0f));
	CLavaFloor::Create(D3DXVECTOR3(-125.0f, 50.0f, -420.0f));
	CLavaFloor::Create(D3DXVECTOR3(- 75.0f, 50.0f, -420.0f));
	CLavaFloor::Create(D3DXVECTOR3(- 25.0f, 50.0f, -420.0f));
	CLavaFloor::Create(D3DXVECTOR3(  25.0f, 50.0f, -420.0f));
	CLavaFloor::Create(D3DXVECTOR3(  75.0f, 50.0f, -420.0f));
	CLavaFloor::Create(D3DXVECTOR3(  125.0f, 50.0f, -420.0f));
	CLavaFloor::Create(D3DXVECTOR3(  175.0f, 50.0f, -420.0f));*/
	pField = CMeshfield::Create(D3DXVECTOR3(-175.0f, 1.0f, -401.0f), Vec3Null, D3DXVECTOR2(400.0f, 100.0f), 2, 2);
	pField->SetTexture(CObject::TEXTURE_LAVA);
	pField->SetTextureTiling(D3DXVECTOR2(5.0f, 0.5f));
	pField->SetTextureAnim(0.001f, 0.0f);
	

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CTitle::Uninit(void)
{

}

//=====================================
// 更新処理
//=====================================
void CTitle::Update(void)
{

}

//=====================================
// 生成処理
//=====================================
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = new CTitle;

	if (FAILED(pTitle->Init()))
	{
		return nullptr;
	}

	return pTitle;
}