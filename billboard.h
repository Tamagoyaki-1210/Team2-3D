//============================================================================
//
//
// �r���{�[�h�`��
// Author:�J�{�N��
//
//============================================================================
#ifndef _BILLBOARD_H_						//���̃}�N����`������ĂȂ�������
#define _BILLBOARD_H_						//2�A�C���N���[�h�h�~�̃}�N����`

#include "object.h"

//****************************************************************************
//�}�N����`
//****************************************************************************
#define MAX_BILLBOARD				(4)		//�r���{�[�h�̍ő�ݒu��
#define IMAGE_BILLBOARD				(2)		//�r���{�[�h�̉摜��
#define BILLBOARD_BULLET_WIDTH		(10)	//�r���{�[�h�̉���(�e)
#define BILLBOARD_BULLET_HEIGHT		(10)	//�r���{�[�h�̏c��(�e)
#define BILLBOARD_TREE_WIDTH		(25)	//�r���{�[�h�̉���(��)
#define BILLBOARD_TREE_HEIGHT		(30)	//�r���{�[�h�̏c��(��)

class CBillBoard : CObject
{
public:
	CBillBoard(int list = 0);
	~CBillBoard() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetUV();
	void SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3);
	void SetColor(D3DXCOLOR col);

	void SetType(Object_Type type);
	void SetSize(float fWidth, float fHeight);
	static CBillBoard *Create(D3DXVECTOR3 pos);

	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetNor(D3DXVECTOR3 nor) { m_nor = nor; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	virtual void SetWorldMtx(D3DXMATRIX worldmtx) { m_worldmtx = worldmtx; }
	virtual void SetWidth(float fWidth) { m_fWidth = fWidth; }
	virtual void SetHeight(float fHeight) { m_fHeight = fHeight; }
	virtual void SetLength(float fLength) { m_fLength = fLength; }
	virtual void SetAngle(float fAngle) { m_fAngle = fAngle; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetNor() const { return m_nor; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXMATRIX& GetWorldMtx() const { return m_worldmtx; }
	const float GetWidth() const { return m_fWidth; }
	const float GetHeight() const { return m_fHeight; }
	const float GetLength() const { return m_fLength; }
	const bool GetUse() const { return m_bUse; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//Buffer�I�u�W�F�N�g
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_nor;					//�@���x�N�g��
	D3DXVECTOR3 m_rot;					//�p�x
	D3DXMATRIX m_worldmtx;				//���[���h�}�g���b�N�X
	float m_fWidth;						//������
	float m_fHeight;					//�����c
	float m_fLength;					//����(�X�N�E�F�A���[�g)
	float m_fAngle;						//�p�x(�A�[�N�^���W�F���g)
	bool m_bUse;						//�g�p����
};
#endif 