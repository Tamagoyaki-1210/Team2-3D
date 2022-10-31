//=============================================================================
//
// meshfield.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include <vector>

class CMeshfield : public CObject
{
public:
	CMeshfield();										//�R���X�g���N�^
	CMeshfield(const int nPriority);					//�R���X�g���N�^
	~CMeshfield() override;								//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override;			//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����

	void SetTexture(CObject::TextType texture);			//�e�N�X�`���̐ݒ菈��
	void SetTextureTiling(D3DXVECTOR2 TileSize);		//�e�N�X�`���̑傫���̐ݒ菈��
	void SetTextureTiling(float fTileSize);				//�e�N�X�`���̑傫���̐ݒ菈��		

	static CMeshfield* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
		const D3DXVECTOR2 unitSize, const int NumberLines, const int NumberColumns);							//��������
	static CMeshfield* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, 
		const D3DXVECTOR2 unitSize, const int NumberLines, const int NumberColumns, const int nPriority);		//��������

	static void FieldInteraction(CObject* pObj);		//�����蔻��̏���

	LPDIRECT3DVERTEXBUFFER9 GetBuff();

private:
	void SetVertex(void);								//���_�C���f�b�N�X�̐ݒ菈��

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;					//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;						//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR3 m_rot;									//����
	D3DXVECTOR2 m_size;									//�P�ʂ̃T�C�Y
	D3DXMATRIX m_mtxWorld;								//�����h�}�g���b�N�X
	int m_nVertexNumber;								//���b�V���t�B�[���h�̒��_��
	int m_nIntexNumber;									//���b�V���t�B�[���h�̃C���f�b�N�X��
	int m_nPolygonNumber;								//���b�V���t�B�[���h�̃|���S����
	int m_nLineVertex;									//�v�Z�p�̃O���[�o���ϐ�(�� + 1)
	int m_nColumnVertex;								//�v�Z�p�̃O���[�o���ϐ�(�s�� + 1)

	static std::vector <CObject*> m_vLandedObj;			//�ꎞ�I
	static std::vector <CMeshfield*> m_vMeshfield;		//���b�V���t�B�[���h�ւ̃|�C���^�̃x�N�g��

};


#endif