//=============================================================================
//
// �I�u�W�F�N�g
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//---------------------------
//�}�N���֐�(�I�u�W�F�N�g)
//---------------------------
#define MAX_OBJECT_PRIORITY			(7)		//�`�揇���X�g

#define OBJECT_PRIORITY_BACK		(1)		//��
#define OBJECT_PRIORITY_CENTER		(2)		//����

#define EFFECT_PRIORITY_BACK		(3)		//�G�t�F�N�g��
#define EFFECT_PRIORITY_CENTER		(4)		//�G�t�F�N�g����

#define UI_PRIORITY_UI				(5)		//UI
#define UI_PRIORITY_FADE			(6)		//�t�F�[�h

//�I�u�W�F�N�g�N���X
class CObject
{
public:
	enum Object_Type
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,	//�v���C���[
		TYPE_ENEMY,		//�G�L����
		TYPE_OBSTACLE,	//��Q��
		TYPE_ITEM,
		TYPE_BG,		//�w�i
		TYPE_EFFECT,	//�G�t�F�N�g
		TYPE_UI,		//UI
		TYPE_MAX,		//�ő�l
	};

	CObject(int priority);
	virtual ~CObject();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetType(Object_Type type);
	void Release();

	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	CObject* GetNext() { return m_pNext; }
	static CObject* GetTop(int priority) { return m_pTop[priority]; }

	const CObject::Object_Type& GetType() const;
	virtual const D3DXVECTOR3& GetPos() const = 0;
	virtual const D3DXVECTOR3& GetRot() const = 0;
	virtual const float GetWidth() const = 0;
	virtual const float GetHeight() const = 0;
	virtual const float GetLength() const = 0;
private:
	//int m_nPriority;		//�i�[��̖���
	bool m_bDeath;			//���S�t���O
	Object_Type m_type;		//�I�u�W�F�N�g�̎��
	static CObject *m_pTop[MAX_OBJECT_PRIORITY];		//�擪�I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_pCurrent[MAX_OBJECT_PRIORITY];	//�Ō��(����)�I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pPrev;		//�O��̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;		//����̃I�u�W�F�N�g�ւ̃|�C���^
};

#endif // !_OBJECT_H_