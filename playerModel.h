//=============================================================================
//
// model.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _PLAYER_MODEL_H
#define _PLAYER_MODEL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include "player.h"
#include "stage.h"
#include "model.h"

//=============================================================================
//�C���N���[�h�t�@�C��
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

	CPlayerModel();										//�R���X�g���N�^
	~CPlayerModel() override;							//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��
	void SetRot(const D3DXVECTOR3 rot);					//�����̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override;			//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����
	static const D3DXCOLOR*  GetPlayerColors(void);		//�J�[���[�̎擾����

	static CModel::ModelType GetHeadType(int nIdx);

	static CPlayerModel* Create(const D3DXVECTOR3 pos, int nIdx);		//��������

private:

	static CModel::ModelType m_HeadTypeAll[HEAD_MAX];

	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR3 m_rot;									//����
	D3DXMATRIX  m_mtxWorld;								//���[���h�}�g���b�N�X
	CModelPart* m_pModel[CPlayer::PARTS_MAX];			//���f���ւ̃|�C���^
	CAnimator* m_pAnimator;								//�A�j���[�^�[
	int m_nPresentHead;									//���̎��
	int m_nPresentColor;								//���݂̃J�[���[�C���f�b�N�X
	D3DXCOLOR m_presentColor;							//���݂̃J�[���[
	int m_nIdx;											//�C���f�b�N�X
	CObject_2D* m_pIcon;								//�A�C�R��
	CUIString*  m_pUiString;

	static CModel::ModelType m_HeadType[PLAYER_MAX];
	static D3DXCOLOR m_playersCol[PLAYER_MAX];

};






#endif