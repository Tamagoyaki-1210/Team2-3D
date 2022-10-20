//============================================================================
//
// ���f��
// Author:�J�{�N��
//
//============================================================================
#ifndef _MODEL_H_		//���̃}�N����`������ĂȂ�������
#define _MODEL_H_		//2�A�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//---------------------------
//�N���X
//---------------------------
class CModel
{
public:
	CModel();
	~CModel();

	void Init(char *xFail);
	void Init();
	void Uninit();
	void Update();
	void Draw();

	static CModel *Create(D3DXVECTOR3 pos, char *xFail);

	void SetParent(CModel* pModel) { m_pParent = pModel; }
	virtual void SetWorldMtx(D3DXMATRIX worldmtx) { m_worldmtx = worldmtx; }
	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXMATRIX& GetWorldMtx() const { return m_worldmtx; }
private:
	//****************************************************************************
	//�\���̒�`
	//****************************************************************************
	//typedef struct
	//{
	//	LPD3DXMESH pMesh;
	//	LPD3DXBUFFER pBuffMat;
	//	DWORD nNumMat;
	//	LPDIRECT3DTEXTURE9 g_pTexture[IMAGE_PLAYER];
	//	D3DXMATRIX Worldmtx;	//���[���h�}�g���b�N�X
	//	D3DXVECTOR3 pos;		//���_���W
	//	D3DXVECTOR3 rot;		//����
	//	float fFrame;			//�t���[����
	//	int nIdxModelParent;	//�e���f���̃C���f�b�N�X
	//}PLAYER_PARTS;
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_nNumMat;
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//�p�x
	D3DXMATRIX m_worldmtx;				//���[���h�}�g���b�N�X
	CModel *m_pParent;
};
#endif// !_PLAYER_H_

