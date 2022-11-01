//=============================================================================
//
// coin.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "coin.h"
#include "BoxHitbox.h"

const D3DXVECTOR3 CCoin::m_hitboxSize[COIN_MAX] =
{
	{10.0f, 20.0f, 10.0f},
	{10.0f, 20.0f, 10.0f},
	{10.0f, 20.0f, 10.0f},
	{10.0f, 20.0f, 10.0f}
};

//コンストラクタ
CCoin::CCoin()
{
	m_pHitbox = nullptr;
}

//デストラクタ
CCoin::~CCoin()
{

}

//初期化処理
HRESULT CCoin::Init(void)
{
	//初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CCoin::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CCoin::Update(void)
{
	//基本クラスの更新処理
	CModel::Update();

	if (m_pHitbox != nullptr)
	{//当たり判定がnullではなかったら
		if (m_pHitbox->GetCollisionState())
		{//何かと当たった場合
			m_pHitbox->Release();		//ヒットボックスを消す
			Release();					//コインを消す
		}
	}
}




//生成処理
CCoin* CCoin::Create(const D3DXVECTOR3 pos, const COIN_TYPE type)
{
	CCoin* pCoin = new CCoin;			//コインを生成する

	if (FAILED(pCoin->Init()))
	{//初期化処理
		return nullptr;
	}

	int nType = (int)CModel::MODEL_COIN_0 + (int)type;					//モデル番号を計算する

	pCoin->SetModel((CModel::ModelType)nType);							//モデルの設定処理
	pCoin->SetPos(pos);													//位置の設定処理
	pCoin->StartRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.01f, 0.0f));		//回転速度の設定

	pCoin->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, m_hitboxSize[type], CHitbox::TYPE_NEUTRAL, pCoin, 10);		//ヒットボックスを生成する

	return pCoin;				//生成したインスタンスを返す

}