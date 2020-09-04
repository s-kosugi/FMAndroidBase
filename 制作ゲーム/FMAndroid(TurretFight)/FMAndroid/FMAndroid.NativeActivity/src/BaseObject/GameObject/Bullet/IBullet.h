#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IBullet.h													*/
/*  @brief		:	�e�x�[�X�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// �e�x�[�X�N���X
class IBullet : public cSpriteObject
{
public:
	IBullet(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name);
	~IBullet(void);

	// ������
	void Initialize(void);
	void Initialize(const cVector2& pos);
	//------------------------------------------------------------------
	// ������
	// pos   : �����ʒu
	// angle : ���ˊp�x(DEGREE)
	// speed : �e��
	void Initialize(const cVector2& pos,float angle,float speed);

	void Update(void);
	IBaseObject* Finalize(void);

	// ���G�t���O�̐ݒ�
	inline void SetInvincible(bool flag) { m_bInvincible = flag; };

	// �����蔻��̔��a�̎擾
	inline const float GetDist(void) { return m_fDist; };
	// ���G�t���O�̎擾
	inline const bool  IsInvincivble(void) { return m_bInvincible; };

protected:
	cVector2	m_vPosUp;		// �ړ��x�N�g��
	float		m_fDist;		// �����蔻��̔��a
	bool		m_bInvincible;	// ���G�t���O

	// �����蔻�菈��
	void CheckHitEnemy(void);

	// �G���A�A�E�g����
	void AreaOutLeftProc(void);
	void AreaOutUpProc(void);
	void AreaOutRightProc(void);
	void AreaOutBottomProc(void);
	void AreaOutAllProc(void);

	static const int	AREAOUT_ADJUST;	// �G���A�A�E�g����
};
//================================================================================================