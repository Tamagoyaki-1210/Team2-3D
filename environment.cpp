//=============================================================================
//
// environment.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "environment.h"
#include "application.h"
#include "rendering.h"

//コンストラクタ
CEnvironment::CEnvironment()
{

}

//デストラクタ
CEnvironment::~CEnvironment()
{

}

//初期化
HRESULT CEnvironment::Init(void)
{
	//初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	return S_OK;
}

//終了
void CEnvironment::Uninit(void)
{
	//基本クラスの終了処理
	CModel::Uninit();
}

//更新
void CEnvironment::Update(void)
{
	//基本クラスの更新処理
	CModel::Update();
}

//描画
void CEnvironment::Draw(void)
{
	CModel::Draw();
}

//生成
CEnvironment * CEnvironment::Create(D3DXVECTOR3 pos, EnvironmentType type)
{
	//インスタンスを生成する
	CEnvironment* pEnvironment = new CEnvironment;

	//プレイヤーの初期化処理
	if (FAILED(pEnvironment->Init()))
	{
		return nullptr;
	}

	switch (type)
	{
	case CEnvironment::ENVIRONMENT_MOUNT:
	{
		pEnvironment->SetModel(MODEL_MOUNT_FUJI);	//モデルの設定処理
	}
		break;
	case CEnvironment::ENVIRONMENT_TYPE_MAX:
		break;
	default:
		break;
	}
	pEnvironment->SetPos(pos);				//位置の設定処理

	return pEnvironment;
}
