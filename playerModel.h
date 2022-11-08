//=============================================================================
//
// model.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _PLAYER_MODEL_H
#define _PLAYER_MODEL_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"
#include "player.h"
#include "stage.h"
#include "model.h"

//=============================================================================
//インクルードファイル
//=============================================================================
class CModelPart;
class CAnimator;
class CObject_2D;
class CUIString;

class CPlayerModel : public CObject
{
public:

	enum PlayerHeadStyle
	{
		HEAD_NORMAL = 0,
		HEAD_SANTA,
		HEAD_PUMPKIN,

		HEAD_MAX
	};

	CPlayerModel();										//コンストラクタ
	~CPlayerModel() override;							//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理
	void SetRot(const D3DXVECTOR3 rot);					//向きの設定処理

	const D3DXVECTOR2 GetSize(void) override;			//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理
	static const D3DXCOLOR*  GetPlayerColors(void);		//カーラーの取得処理

	static CModel::ModelType GetHeadType(int nIdx);

	static CPlayerModel* Create(const D3DXVECTOR3 pos, int nIdx);		//生成処理

private:

	static CModel::ModelType m_HeadTypeAll[HEAD_MAX];

	D3DXVECTOR3 m_pos;									//位置
	D3DXVECTOR3 m_rot;									//向き
	D3DXMATRIX  m_mtxWorld;								//ワールドマトリックス
	CModelPart* m_pModel[CPlayer::PARTS_MAX];			//モデルへのポインタ
	CAnimator* m_pAnimator;								//アニメーター
	int m_nPresentHead;									//頭の種類
	int m_nPresentColor;								//現在のカーラーインデックス
	D3DXCOLOR m_presentColor;							//現在のカーラー
	int m_nIdx;											//インデックス
	CObject_2D* m_pIcon;								//アイコン
	CUIString*  m_pUiString;

	static CModel::ModelType m_HeadType[PLAYER_MAX];
	static D3DXCOLOR m_playersCol[PLAYER_MAX];

};






#endif