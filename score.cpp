//=============================================================================
//
// score.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "score.h"


std::vector <CScore*> CScore::m_vScore;

//コンストラクタ
CScore::CScore()
{
	//メンバー変数をクリアする
	m_nScore = 0;
	m_nPlayerIdx = 0;
}

//デストラクタ
CScore::~CScore()
{

}

//初期化処理
HRESULT CScore::Init(void)
{
	//初期化処理
	m_nScore = 0;
	m_nPlayerIdx = -1;

	return S_OK;
}

//終了処理
void CScore::Uninit(void)
{

}

//スコアを足す処理
void CScore::AddScore(const int nScore)
{
	m_nScore += nScore;
}







//スコアを足す処理
void CScore::AddScore(const int nPlayerIdx, const int nScore)
{
	m_vScore.data()[nPlayerIdx]->AddScore(nScore);
}


//クリア処理
void CScore::Clear(void)
{
	for (int nCnt = 0; nCnt < (int)m_vScore.size(); nCnt++)
	{
		m_vScore.data()[nCnt]->Uninit();
		delete m_vScore.data()[nCnt];
		m_vScore.data()[nCnt] = nullptr;
	}

	m_vScore.clear();
}

//生成処理
CScore* CScore::Create(const int nPlayerIdx)
{
	CScore* pScore = new CScore;

	if (FAILED(pScore->Init()))
	{
		return nullptr;
	}

	pScore->m_nScore = 0;
	pScore->m_nPlayerIdx = nPlayerIdx;
	
	return pScore;
}