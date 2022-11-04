//=============================================================================
//
// stage.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "stage.h"
#include "application.h"
#include "meshfield.h"
#include "object2D.h"
#include "object3D.h"
#include "billboard.h"
#include "model.h"
#include "player.h"
#include "UIString.h"
#include "Letter.h"
#include "debugProc.h"
#include "font.h"
#include "halfsphere.h"
#include "CylinderHitbox.h"
#include "BoxHitbox.h"
#include "coin.h"
#include "goal.h"
#include "camera.h"
#include "SpikeBall.h"
#include <string>
#include "score.h"

//アニメーション情報のテキストファイルの相対パス
char* CStage::m_pStagePass[STAGE_TYPE_MAX] =
{
	{ "data\\STAGESET\\StageSet1.txt" },
};

CMeshfield *CStage::m_pField = nullptr;
CHalfSphere* CStage::m_pSphere[PLAYER_MAX] = {};
CPlayer* CStage::m_pPlayer[PLAYER_MAX] = {};
bool CStage::m_bResult = false;

//=====================================
// デフォルトコンストラクタ
//=====================================
CStage::CStage()
{

}

//=====================================
// デストラクタ
//=====================================
CStage::~CStage()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CStage::Init(void)
{
	// メッシュフィールドの生成
	m_pField = CMeshfield::Create(D3DXVECTOR3(-200.0f, -150.0f, 1100.0f), Vec3Null, D3DXVECTOR2(30.0f, 70.0f), 20, 10, 3);

	// スフィアメッシュ
	m_pSphere[0] = CHalfSphere::Create(D3DXVECTOR3(0.0f, -2000.0f, 1000.0f), D3DXVECTOR3(30000.0f, 0.0f, 30000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CHalfSphere::SPHERE_UP);

	m_pSphere[1] = CHalfSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(35000.0f, 0.0f, 35000.0f), D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI), CHalfSphere::SPHERE_DOWN);

	// ステージ読み込み処理
	Load();

	CGoal::Create();

	// プレイヤーの生成
	m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, -100.0f, -100.0f), 0);
	m_pPlayer[1] = CPlayer::Create(D3DXVECTOR3(-50.0f, -100.0f, -100.0f), 1);
	m_pPlayer[2] = CPlayer::Create(D3DXVECTOR3(-100.0f, -100.0f, -100.0f), 2);
	m_pPlayer[3] = CPlayer::Create(D3DXVECTOR3(-150.0f, -100.0f, -100.0f), 3);

	//CBoxHitbox::Create(D3DXVECTOR3(-200.0f, -150.0f, 200.0f), Vec3Null, D3DXVECTOR3(50.0f, 300.0f, 50.0f), CHitbox::TYPE_OBSTACLE, nullptr, -30, CHitbox::EFFECT_LAUNCH);
	//CCylinderHitbox::Create(D3DXVECTOR3(150.0f, -150.0f, 200.0f), Vec3Null, D3DXVECTOR3(150.0f, 300.0f, 150.0f), CHitbox::TYPE_NEUTRAL, nullptr);

	if (CApplication::GetCamera() != nullptr)
	{
		CApplication::GetCamera()->SetPos(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, -200.0f, 100.0f));
	}

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CStage::Uninit(void)
{
	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (m_pPlayer[nCnt] != nullptr)
		{
			m_pPlayer[nCnt]->Release();
			m_pPlayer[nCnt] = nullptr;
		}
	}

	if (m_pSphere[0] != nullptr)
	{
		m_pSphere[0]->Release();
		m_pSphere[0] = nullptr;
	}

	if (m_pField != nullptr)
	{
		m_pField->Release();
		m_pField = nullptr;
	}
}

//=====================================
// 更新処理
//=====================================
void CStage::Update(void)
{
	GameResult();
}

//=====================================
// 終了処理
//=====================================
void CStage::SetModelType(D3DXVECTOR3 pos, ModelType type)
{
	switch (type)
	{
	case CStage::MODEL_SPIKEBALL:
	{
		// 鉄球
		CSpikeBall::Create(D3DXVECTOR3(pos));
	}
		break;
	default:
		break;
	}
}

//=====================================
// 生成処理
//=====================================
CStage* CStage::Create(void)
{
	CStage* pStage = new CStage;

	if (FAILED(pStage->Init()))
	{
		return nullptr;
	}

	return pStage;
}

void CStage::GameResult()
{
	bool bGoal[PLAYER_MAX] = {};
	bool bRot[PLAYER_MAX] = {};

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		bGoal[nCnt] = m_pPlayer[nCnt]->GetGoal();
		bRot[nCnt] = m_pPlayer[nCnt]->GetRotCmp();
	}
	
	if (bGoal[0] && bGoal[1] && bGoal[2] && bGoal[3]
		&& bRot[0] && bRot[1] && bRot[2] && bRot[3])
	{
		m_bResult = true;
		ScoreComparison();
	}
}

int CStage::ScoreComparison()
{
	int nCnt = 0;

	if (m_bResult)
	{
		D3DXVECTOR2 PlayerScore[PLAYER_MAX] = {};
		D3DXVECTOR2 nChange;

		for (int nCount = 0; nCount < PLAYER_MAX; nCount++)
		{
			PlayerScore[nCount].x = (float)CScore::GetScore(nCount);
			PlayerScore[nCount].y = (float)nCount;
		}

		for (int nCount = 0; nCount < PLAYER_MAX - 1; nCount++)
		{
			for (int nCount2 = nCount + 1; nCount2 < PLAYER_MAX; nCount2++)
			{
				if (PlayerScore[nCount].x < PlayerScore[nCount2].x)
				{
					nChange = PlayerScore[nCount2];
					PlayerScore[nCount2] = PlayerScore[nCount];
					PlayerScore[nCount] = nChange;
				}
			}
		}

		if ((int)PlayerScore[3].x == (int)PlayerScore[0].x)
		{
			m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[1].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[2].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[3].y]->SetWinner(true);

			m_pPlayer[(int)PlayerScore[0].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[1].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[2].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[3].y]->MoveWinner();
			nCnt = 4;
		}
		else if ((int)PlayerScore[2].x == (int)PlayerScore[0].x)
		{
			m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[1].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[2].y]->SetWinner(true);

			m_pPlayer[(int)PlayerScore[0].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[1].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[2].y]->MoveWinner();
			nCnt = 3;
		}
		else if ((int)PlayerScore[1].x == (int)PlayerScore[0].x)
		{
			m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);
			m_pPlayer[(int)PlayerScore[1].y]->SetWinner(true);

			m_pPlayer[(int)PlayerScore[0].y]->MoveWinner();
			m_pPlayer[(int)PlayerScore[1].y]->MoveWinner();
			nCnt = 2;
		}
		else
		{
			m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);

			m_pPlayer[(int)PlayerScore[0].y]->MoveWinner();
			nCnt = 1;
		}
	}

	return nCnt;
}

//=====================================
//読み込み処理
//=====================================
void CStage::Load()
{
	char aStr[256] = {};		//読み込む用文字列

								//ファイルを開く
	FILE* pFile = fopen(m_pStagePass[0], "r");

	if (pFile != nullptr)
	{//ファイルが開いた場合
		fscanf(pFile, "%s", aStr);

		while (strncmp(aStr, "END_SCRIPT", 10) != 0)
		{//文字列の初期化と読み込み
			fscanf(pFile, "%s", aStr);

			// メッシュフィールド読み込み
			if (strncmp(aStr, "FIELDSET", 8) == 0)
			{
				while (strncmp(aStr, "END_FIELDSET", 12) != 0)
				{
					fscanf(pFile, "%s", aStr);
					if (strncmp(aStr, "TEXTURE_NAME", 12) == 0)
					{//この後にコメント
						fscanf(pFile, "%s", aStr);
						fscanf(pFile, "%s", aStr);
						m_pField->LoadTexture(aStr);
					}
					else if (strncmp(aStr, "TEXTURE_TILING", 14) == 0)
					{//この後にコメント
						fscanf(pFile, "%s", aStr);
						fscanf(pFile, "%s", aStr);			// メッシュフィールドのタイリングを読み込む処理
						std::string s = aStr;				// std::stringに変換する
						float fTaling = std::stof(s);		//floatに変換する
						m_pField->SetTextureTiling(fTaling);
					}
				}
			}
			else if (strncmp(aStr, "SPHERESET", 9) == 0)
			{
				int nSphere = 0;
				while (strncmp(aStr, "END_SPHERESET", 13) != 0)
				{
					fscanf(pFile, "%s", aStr);
					while (strncmp(aStr, "END_SPHERE", 10) != 0)
					{
						fscanf(pFile, "%s", aStr);
						if (strncmp(aStr, "SPHERE", 6) == 0)
						{
							fscanf(pFile, "%s", aStr);
							if (strncmp(aStr, "TEXTURE_NAME", 12) == 0)
							{
								fscanf(pFile, "%s", aStr);
								fscanf(pFile, "%s", aStr);
								m_pSphere[nSphere]->LoadTexture(aStr);
							}
						}
					}
					nSphere++;
				}
			}
			else if (strncmp(aStr, "COINALLSET", 10) == 0)
			{
				int nCoinType = 0;
				while (strncmp(aStr, "END_COINALLSET", 14) != 0)
				{
					fscanf(pFile, "%s", aStr);
					if (strncmp(aStr, "COINTYPESET", 11) == 0)
					{
						fscanf(pFile, "%s", aStr);
						while (strncmp(aStr, "END_COINTYPESET", 15) != 0)
						{
							fscanf(pFile, "%s", aStr);
							if (strncmp(aStr, "COINSET", 7) == 0)
							{
								while (strncmp(aStr, "END_COINSET", 11) != 0)
								{
									fscanf(pFile, "%s", aStr);
									if (strncmp(aStr, "COIN", 4) == 0)
									{
										while (strncmp(aStr, "END_COIN", 8) != 0)
										{
											fscanf(pFile, "%s", aStr);
											if (strncmp(aStr, "POS", 3) == 0)
											{
												fscanf(pFile, "%s", aStr);
												fscanf(pFile, "%s", aStr);	//X座標の読み込む処理
												std::string s = aStr;		//std::stringに変換する
												float x = std::stof(s);		//floatに変換する

												fscanf(pFile, "%s", aStr);	//Y座標の読み込む処理
												s = aStr;					//std::stringに変換する
												float y = std::stof(s);		//floatに変換する

												fscanf(pFile, "%s", aStr);	//Z座標の読み込む処理
												s = aStr;					//std::stringに変換する
												float z = std::stof(s);		//floatに変換する

												CCoin::Create(D3DXVECTOR3(x, y, z), (CCoin::COIN_TYPE)nCoinType);
											}
										}
									}
								}
							}
						}
						nCoinType++;
					}
				}
			}
			else if (strncmp(aStr, "MODELALLSET", 11) == 0)
			{
				int nModelType = 0;
				while (strncmp(aStr, "END_MODELALLSET", 15) != 0)
				{
					fscanf(pFile, "%s", aStr);
					if (strncmp(aStr, "MODELTYPESET", 12) == 0)
					{
						fscanf(pFile, "%s", aStr);
						while (strncmp(aStr, "END_MODELTYPESET", 16) != 0)
						{
							fscanf(pFile, "%s", aStr);
							if (strncmp(aStr, "MODELSET", 8) == 0)
							{
								while (strncmp(aStr, "END_MODELSET", 12) != 0)
								{
									fscanf(pFile, "%s", aStr);
									if (strncmp(aStr, "MODEL", 5) == 0)
									{
										while (strncmp(aStr, "END_MODEL", 9) != 0)
										{
											fscanf(pFile, "%s", aStr);
											if (strncmp(aStr, "POS", 3) == 0)
											{
												fscanf(pFile, "%s", aStr);
												fscanf(pFile, "%s", aStr);	//X座標の読み込む処理
												std::string s = aStr;		//std::stringに変換する
												float x = std::stof(s);		//floatに変換する

												fscanf(pFile, "%s", aStr);	//Y座標の読み込む処理
												s = aStr;					//std::stringに変換する
												float y = std::stof(s);		//floatに変換する

												fscanf(pFile, "%s", aStr);	//Z座標の読み込む処理
												s = aStr;					//std::stringに変換する
												float z = std::stof(s);		//floatに変換する

												SetModelType(D3DXVECTOR3(x, y, z), (ModelType)nModelType);
											}
										}
									}
								}
							}
						}
						nModelType++;
					}
				}
			}
		}
	}
	//ファイルを閉じる
	fclose(pFile);
}