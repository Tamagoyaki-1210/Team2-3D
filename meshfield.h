//============================================================================
//
//
// ���b�V���|���S���̏���
// Author:�J�{�N��
//
//============================================================================
#ifndef _MESHFIELD_H_						//���̃}�N����`������ĂȂ�������
#define _MESHFIELD_H_						//2�A�C���N���[�h�h�~�̃}�N����`

#include "object.h"
//****************************************************************************
//�}�N����`
//****************************************************************************
#define MESHFIELD_WIDTH			(50)	//���b�V���|���S���̉���
#define MESHFIELD_HEIGHT		(50)	//���b�V���|���S���̏c��
#define MAX_MESHFIELD			(20)		//���b�V���̃|���S���ő吔


class CMeshField : CObject
{
public:
	CMeshField(int list = 0);
	~CMeshField() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	bool FieldCollision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld);

	float GetVecNor() { return m_fVecNor; }

	void SetMesh();
	void SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3);
	void SetColor(D3DXCOLOR col);

	void SetType(Object_Type type);
	void SetSize(float fWidth, float fHeight);
	static CMeshField *Create(D3DXVECTOR3 pos);

	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetNor(D3DXVECTOR3 nor) { m_nor = nor; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	virtual void SetWorldMtx(D3DXMATRIX worldmtx) { m_worldmtx = worldmtx; }
	virtual void SetWidth(float fWidth) { m_fWidth = fWidth; }
	virtual void SetHeight(float fHeight) { m_fHeight = fHeight; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetNor() const { return m_nor; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXMATRIX& GetWorldMtx() const { return m_worldmtx; }
	const float GetWidth() const { return m_fWidth; }
	const float GetHeight() const { return m_fHeight; }
	const float GetLength() const { return m_fLength; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_nor;					//�@���x�N�g��
	D3DXVECTOR3 m_rot;					//�p�x
	D3DXMATRIX m_worldmtx;				//���[���h�}�g���b�N�X
	float m_fWidth;						//������
	float m_fHeight;					//�����c
	float m_fLength;					//����(�X�N�E�F�A���[�g)
	float m_fAngle;						//�p�x(�A�[�N�^���W�F���g)

	int m_nDebug;
	int m_nMeshPlimitive;
	int m_nMeshVertex;
	int m_nMeshIndex;		//���̍��v��
	int m_nMeshX;			//x���̌�
	int m_nMeshZ;			//z���̌�

	float m_fVecNor;		//���b�V���@���x�N�g��
	float m_fVecVtx[MESHFIELD_WIDTH * MESHFIELD_HEIGHT];		//���_���̖@���x�N�g���̔z��
};
#endif