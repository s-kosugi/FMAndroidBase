#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.h													*/
/*  @brief		:	�v���C���[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/03													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

//================================================================================================
// �v���C���[�N���X
class cPlayer : public cSpriteObject
{
public:
	cPlayer(IBaseObject* parent);
	~cPlayer(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

private:
	// �v���C���[���
	enum STATE
	{
		NORMAL,
		LASER,
		DEAD
	};

	// �ʏ�e���x
	static const float NORMAL_BUL_SPD;
	// �e���ˊԊu
	static const float NORMAL_BUL_INTERVAL;
	// �e���ˈʒu����
	static const float BUL_FIRE_POS;

	// �\���D��x
	static const int   PRIORITY;


	// �����蔻��̔��a
	float m_fDist;

	// �v���C���[���
	STATE m_eState;

	// �ʏ���
	void Normal(void);

	// ���[�U�[���ˏ��
	void Laser(void);

	// ���S���
	void Dead(void);

	// ���[�U�[���ˏ���
	void StartLaser(void);

	// �G�Ƃ̓����蔻�菈��
	void CheckHitEnemy(void);
};
//================================================================================================