//=============================================================================
//
// player.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CModelPart;
class CAnimator;
class CCylinderHitbox;
class CScore;
class CUIString;
class CBoxHitbox;

class CPlayer : public CObject
{
public:

	enum Parts
	{
		BODY = 0,
		HEAD,
		LEFT_ARM,
		LEFT_HAND,
		RIGHT_ARM,
		RIGHT_HAND,
		LEFT_LEG,
		LEFT_FOOT,
		RIGHT_LEG,
		RIGHT_FOOT,
		PARTS_MAX
	};

	enum STATE
	{
		STATE_NEUTRAL = 0,
		STATE_RUNNING,
		STATE_JUMP,
		STATE_PUNCH,
		STATE_DAMAGE,
		STATE_MAX
	};

	enum PlayerColor
	{
		PLAYER_RED = 0,
		PLAYER_GREEN,
		PLAYER_BLUE,
		PLAYER_YELLOW,
		PLAYER_MAGENTA,
		PLAYER_CYAN,
		PLAYER_BLACK,
		PLAYER_WHITE,

		PLAYER_COLOR_MAX
	};

	CPlayer();							//コンストラクタ
	~CPlayer() override;								//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override { m_pos = pos; }		//位置の設定処理
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }					//位置の設定処理

	const D3DXVECTOR2 GetSize(void) override { return Vec2Null; }		//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override { return m_pos; }			//位置の取得処理

	D3DXVECTOR3 GetDestRot(void) { return m_DestRot; }	//目的の角度の取得処理

	static CPlayer* Create(const D3DXVECTOR3 pos,int nCntPlayer);	//生成処理
	static D3DXCOLOR* GetPlayerColors(void);

	void PlayerController(int nCntPlayer);
	void SetPlayerIdx(int nCntPlayer);
	void SetFriction(const float fFriction);

	bool GetGoal() { return m_bGoal; }

	bool GetRotCmp();

	void MoveWinner();

	void SetWinner(bool bWinner);

	void WinnerAnim();
	void LoserAnim();

	void PlayerRespawn();
private:
	void GoalMove();

	static D3DXCOLOR m_playerColor[PLAYER_COLOR_MAX];
	static const float m_MaxWalkingSpeed;
	static const float m_AccelerationCoeff;

	D3DXVECTOR3 m_pos;									//位置
	D3DXVECTOR3 m_move;									//速度
	D3DXVECTOR3 m_rot;									//向き
	D3DXVECTOR3 m_DestRot;								//目的の角度
	D3DXMATRIX  m_mtxWorld;								//ワールドマトリックス
	bool		m_bJump;								//ジャンプしているかどうか
	int			m_nInvincibilityCnt;					//無敵状態のカウンター
	int			m_nCntAttack;
	float		m_fFrictionCoeff;						//摩擦係数

	float m_fAngle;
	bool m_bGoal;
	bool m_bMove;
	bool m_bWinner;
	bool m_bPos;
	bool m_bRot;
	bool m_bHit;
	bool m_bPunch;
	bool m_bAttacking;

	int m_nScore[PLAYER_MAX];

	D3DXVECTOR3 m_TargetPos;

	D3DXVECTOR3 GoalPos;

	CModelPart* m_pModel[PARTS_MAX];					//モデルへのポインタ
	CAnimator* m_pAnimator;

	STATE m_State;
	CCylinderHitbox* m_pHitbox;							//ヒットボックス
	CBoxHitbox*       m_pAttackHitbox;					//攻撃ヒットボックス
	CScore* m_pScore;
	CUIString* m_pScoreUI;

	int m_nIdxPlayer;
	int m_nFrame;
	//CModel* m_pModel;									//モデル
};

#endif