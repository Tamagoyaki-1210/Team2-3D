//=============================================================================
//
// warning.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _WARNING_H
#define _WARNING_H

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object2D.h"

//---------------------------
//�N���X�錾
//---------------------------
class CWarning : public CObject_2D
{
public:
	enum WARNING
	{
		MESSAGE_FALLING_STONE = 0,
		MESSAGE_MAX
	};

	CWarning();
	CWarning(const int nPriority);
	~CWarning() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void BlinkColor(void);

	static CWarning* Create(const D3DXVECTOR3 pos);			//��������

private:
	int m_nLife;			// ����
	int m_nMaxBlink;	// �_�ŉ�
	bool m_bBlink;			// �_�Ŕ���
};

#endif // !_FONT_H