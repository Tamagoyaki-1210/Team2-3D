//=============================================================================
//
// message.cpp
// Author : tanimoto kosuke
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "message.h"
#include "game.h"
#include "application.h"

//静的メンバー変数宣言
bool CMessage::m_bStart;

//=====================================
// デフォルトコンストラクタ
//=====================================
CMessage::CMessage()
{

}

//=====================================
// デストラクタ
//=====================================
CMessage::~CMessage()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CMessage::Init(void)
{
	m_nMessageIdx = 0;
	m_nMessageCounter = 0;
	m_nNum = 0;
	m_bStart = false;
	m_type = MESSAGE_COUNTDOWN;
	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CMessage::Uninit(void)
{
	if (m_pObj2D != nullptr)
	{
		m_pObj2D->Release();
		m_pObj2D = nullptr;
	}
	m_nMessageIdx = 0;
	m_nMessageCounter = 0;
	m_nNum = 0;
	m_bStart = false;
}

//=====================================
// 更新処理
//=====================================
void CMessage::Update(void)
{
	// ポーズ中でない場合のみ更新
	if (CApplication::GetPause() == false)
	{
		// カウントが0より上の場合
		if (m_nMessageCounter > 0)
		{
			m_nMessageCounter--;

			// カウントが0以下になった場合
			if (m_nMessageCounter <= 0)
			{
				if (m_type == MESSAGE_COUNTDOWN)
				{// カウントダウン処理の場合
					m_nNum--;
					// 現在位置が0より大きい場合
					if (m_nNum > 0)
					{
						m_nMessageCounter = CountDownLife;
						m_pObj2D->SetAnimPattern(m_nNum);
					}
					else
					{
						Destroy();
						StartMessage();
					}
				}
				else if (m_type == MESSAGE_GOAL)
				{
					Destroy();
					WinMessage();
				}
				else if (m_type == MESSAGE_WIN)
				{
					Uninit();
					// ゲーム終了判定
					CGame::SetEndGame();
				}
				else
				{
					Destroy();
				}
			}
		}
	}
}

//=====================================
// カウントダウンメッセージ表示処理
//=====================================
void CMessage::SetCountDown(int nNum)
{
	if (m_pObj2D == nullptr)
	{
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(200.0f, 150.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_NUMBERS);
		m_pObj2D->SetTextureParameter(1, 5, 3, INT_MAX);
		m_pObj2D->SetPriority(3);
		m_nNum = nNum;
		m_pObj2D->SetAnimPattern(nNum);
		m_nMessageCounter = CountDownLife;
		m_type = MESSAGE_COUNTDOWN;
	}
}

//=====================================
// スタートメッセージ表示処理
//=====================================
void CMessage::StartMessage(void)
{
	if (m_pObj2D == nullptr)
	{
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_MESSAGE_START);
		m_pObj2D->SetTextureParameter(1, 1, 1, INT_MAX);
		m_pObj2D->SetPriority(4);
		m_nMessageCounter = 120;
		m_type = MESSAGE_START;
		m_bStart = true;
	}
}

//=====================================
// ゴールメッセージ表示処理
//=====================================
void CMessage::GoalMessage(int nMessageIdx)
{
	if (m_pObj2D == nullptr)
	{
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_MESSAGE_GOAL);
		m_pObj2D->SetTextureParameter(1, 1, 1, INT_MAX);
		m_pObj2D->SetPriority(4);
		m_nMessageCounter = 120;
		m_type = MESSAGE_GOAL;
		m_bStart = false;
		// 勝敗番号を代入する
		m_nMessageIdx = nMessageIdx;
	}
}


//=====================================
// ゴールメッセージ表示処理
//=====================================
void CMessage::WinMessage()
{
	if (m_pObj2D == nullptr)
	{
		// 同点ではない場合
		if (m_nMessageIdx != 0)
		{
			// WIN生成
			m_pObj2D = CObject_2D::Create();
			m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f));
			m_pObj2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
			m_pObj2D->SetTexture(CObject::TEXTURE_WINNER);
			m_pObj2D->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pObj2D->SetPriority(4);
		}

		// 勝敗メッセージ生成
		CObject_2D *pObject2D = CObject_2D::Create();
		pObject2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		pObject2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		pObject2D->SetTextureParameter(1, 1, 1, INT_MAX);
		pObject2D->SetPriority(4);

		// 番号でプレイヤーを変更する
		switch (m_nMessageIdx)
		{
		case 0:
			pObject2D->SetTexture(CObject::TEXTURE_DRAW);
			break;
		case 1:
			pObject2D->SetTexture(CObject::TEXTURE_1P_WIN);
			break;
		case 2:
			pObject2D->SetTexture(CObject::TEXTURE_2P_WIN);
			break;
		case 3:
			pObject2D->SetTexture(CObject::TEXTURE_3P_WIN);
			break;
		case 4:
			pObject2D->SetTexture(CObject::TEXTURE_4P_WIN);
			break;
		default:
			pObject2D->SetTexture(CObject::TEXTURE_NULL);
			break;
		}

		m_type = MESSAGE_WIN;
		m_nMessageCounter = 120;
	}
}

//=====================================
// 終了処理
//=====================================
void CMessage::Destroy(void)
{
	if (m_pObj2D != nullptr)
	{
		m_pObj2D->Release();
		m_pObj2D = nullptr;
		m_nMessageCounter = 120;
		m_bEndGame = true;
	}
	m_nMessageCounter = 0;
}


//=====================================
// 生成処理
//=====================================
CMessage* CMessage::Create()
{
	CMessage* pMessage = new CMessage;

	//初期化処理
	if (FAILED(pMessage->Init()))
	{
		return nullptr;
	}

	return pMessage;
}