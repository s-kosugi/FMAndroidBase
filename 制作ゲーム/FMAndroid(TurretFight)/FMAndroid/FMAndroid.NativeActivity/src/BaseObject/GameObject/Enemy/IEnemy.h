#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IEnemy.h													*/
/*  @brief		:	�G�x�[�X�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// �G�x�[�X�N���X
class IEnemy : public cSpriteObject
{
public:
	enum class STATE
	{
		NORMAL,		// �ʏ���
		DEAD,		// ���S���
	};
	enum class DIRECTION
	{
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
	};
public:
	IEnemy(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~IEnemy(void);

	// ������
	void Initialize(void);
	// ������
	// pos   : �����ʒu
	void Initialize(const cVector2& pos);
	void Update(void);
	IBaseObject* Finalize(void);

	// �_���[�W
	void Damage(void);

	// �����蔻�苗���̎擾
	inline const float GetDist(void) { return m_fDist; };

	// ��Ԃ̎擾
	inline const STATE GetState(void) { return m_eState; };


protected:
	cVector2	m_vPosUp;		// �ړ��x�N�g��
	float		m_fDist;		// �����蔻��̔��a

	STATE		m_eState;		// ���
	short		m_nHp;			// �ϋv��

	short		m_nScore;		// �l���X�R�A

	// �G���A�A�E�g����
	virtual void AreaOutLeftProc(void);
	virtual void AreaOutUpProc(void);
	virtual void AreaOutRightProc(void);
	virtual void AreaOutBottomProc(void);
	virtual void AreaOutAllProc(void);

	// ��ԕʏ���
	virtual void Normal(void);
	virtual void Dead(void);

	// ��ʊO�z�u����
	// �߂�l : �z�u����
	DIRECTION ArrangeOffScreen(void);

	// �v���C���[�֌������ړ��ʂ�ݒ肷��
	// speed : ��{�ړ���
	void GotoPlayer(float speed);

	static const int	AREAOUT_ADJUST;	// �G���A�A�E�g����
};
//================================================================================================