//=============================================================================
//
// model.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _MODEL_H
#define _MODEL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include <vector>

class CModel : public CObject
{
public:

	enum ModelType
	{
		MODEL_BODY = 0,
		MODEL_HEAD,
		MODEL_LEFT_ARM,
		MODEL_LEFT_HAND,
		MODEL_RIGHT_ARM,
		MODEL_RIGHT_HAND,
		MODEL_LEFT_LEG,
		MODEL_LEFT_FOOT,
		MODEL_RIGHT_LEG,
		MODEL_RIGHT_FOOT,
		MODEL_MAX
	};

	CModel();																			//�R���X�g���N�^
	CModel(const int nPriority);														//�R���X�g���N�^
	virtual ~CModel() override;															//�f�X�g���N�^
													
	virtual HRESULT Init(void) override;												//����������
	virtual void Uninit(void) override;													//�I������
	virtual void Update(void) override;													//�X�V����
	virtual void Draw(void) override;													//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;										//�ʒu�̐ݒ菈��
	const D3DXVECTOR3 GetPos(void) override;											//�ʒu�̎擾����

	void SetRot(const D3DXVECTOR3 ros);													//�����̐ݒ菈��
	const D3DXVECTOR3 GetRot(void);														//�����̎擾����

	const D3DXVECTOR2 GetSize(void) override;											//�T�C�Y�̎擾����

	static void GetModel(ModelType type, LPD3DXMESH* pMesh, LPD3DXBUFFER* pBuffMat, DWORD* numMat);		//���f���̃��b�V�����̎擾����
	static void GetTextures(std::vector <LPDIRECT3DTEXTURE9>& vTex, CModel::ModelType type);			//�}�e���A���̃e�N�X�`���̎擾����
	static void LoadAllModels(void);													//�S���̃��f���̃��[�h����
	static void DestroyAllModels(void);													//�S���̃��f���̔j������

	static CModel* Create(ModelType type, D3DXVECTOR3 pos);								//��������
	static CModel* Create(ModelType type, D3DXVECTOR3 pos, const int nPriority);		//��������

private:

	LPD3DXMESH		m_pMesh;												//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	m_pBuffMat;												//�}�e���A�����ւ̃|�C���^
	DWORD			m_nNumMat;												//�}�e���A�����̐�
	D3DXVECTOR3		m_pos;													//���݂̈ʒu
	D3DXVECTOR3		m_LastPos;												//�O��̈ʒu
	D3DXVECTOR3		m_move;													//���f���̈ړ���
	D3DXVECTOR3		m_rot;													//����
	D3DXVECTOR3		m_minCoord, m_maxCoord;									//���f���̒��_���W�̍ŏ��l�ƍő�l
	D3DXMATRIX		m_mtxWorld;												//���[���h�}�g���b�N�X
	ModelType		m_type;													//���f���̎��

	static LPD3DXMESH		m_pMeshAll[MODEL_MAX];							//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER		m_pBuffMatAll[MODEL_MAX];						//�}�e���A�����ւ̃|�C���^
	static DWORD			m_nNumMatAll[MODEL_MAX];						//�}�e���A�����̐�
	static char*			m_pModelPass[MODEL_MAX];						//���f���̑��΃p�X
	static std::vector <LPDIRECT3DTEXTURE9> m_vModelTexture[MODEL_MAX];		//���f���̃e�N�X�`���ւ̃|�C���^�̃x�N�g��
};

#endif