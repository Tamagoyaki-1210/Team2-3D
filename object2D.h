//=============================================================================
//
// �I�u�W�F�N�g2D
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//�I�u�W�F�N�g2D�N���X
class CObject2D : public CObject
{
public:
	CObject2D(int list = 0);
	~CObject2D() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	
	void SetUV();
	void SetAnim(int nAnimX, int nAnimY, int nControl);
	void SetTex(int tex, int div);
	void SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3);
	void SetColor(D3DXCOLOR col);

	void SetType(Object_Type type);
	void SetSize(float fWidth, float fHeight);
	static CObject2D *Create(D3DXVECTOR3 pos);

	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	virtual void SetWidth(float fWidth) { m_fWidth = fWidth; }
	virtual void SetHeight(float fHeight) { m_fHeight = fHeight; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const float GetWidth() const { return m_fWidth; }
	const float GetHeight() const { return m_fHeight; }
	const float GetLength() const { return m_fLength; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//Buffer�I�u�W�F�N�g
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//�p�x
	float m_fWidth;						//������
	float m_fHeight;					//�����c
	float m_fLength;					//����(�X�N�E�F�A���[�g)
	float m_fAngle;						//�p�x(�A�[�N�^���W�F���g)
	int m_nAnimCounterX;				//�A�j���[�V�����J�E���^�[X���W
	int m_nAnimCounterY;				//�A�j���[�V�����J�E���^�[Y���W
	int m_nAnimControl;					//�A�j���[�V��������
};

#endif // !_OBJECT2D_H_