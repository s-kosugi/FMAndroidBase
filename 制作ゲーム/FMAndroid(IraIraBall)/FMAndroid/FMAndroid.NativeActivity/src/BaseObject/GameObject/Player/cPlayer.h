#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cPlayer.h													*/
/*  @brief		:	�v���C���[�N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/18													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"

// �v���C���[�N���X
class cPlayer : public cSpriteObject
{
public:
	// �v���C���[���
	enum class STATE {
		START,
		NORMAL,
		DEAD,
		GOAL,
	};

	cPlayer(IBaseObject* parent);
	~cPlayer(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	// �v���C���[��Ԃ̕ύX
	void ChangeState(STATE state);

	// ��Ԃ̎擾
	const inline STATE GetState(void) { return m_eState; };

	// �����蔻��̔��a�̎擾
	const inline float GetDist(void) { return DIST; };

private:
	// �Ǔ�����̑��x������
	static const float REFLECTION;
	// ���C��
	static const float FRICTION;
	// �������X���l�̐؂�̂�
	static const float SLOPE_MIN_ROUNDDOWN;
	// �Z���T�[�̒l�̑傫�����g���傫���ɂ��킹��
	static const float SENSOR_RATE;
	// �����蔻��̔��a
	static const float DIST;
	// ���S��Ԃ̎���
	static const float DEAD_TIME;
	// ���S�G�t�F�N�g�̋ʂ̐�
	static const int DEAD_EFFECT_NUM;
	// ���S�G�t�F�N�g�̈ړ��X�s�[�h
	static const float DEAD_EFFECT_SPEED;
	// �S�[����Ԃ̎���
	static const float GOAL_TIME;

	// ���x
	cVector2 m_vVelocity;

	// �v���C���[���
	STATE m_eState;


	// �J�n��Ԃ̏���
	void Start();
	// �ʏ��ԏ���
	void Normal();
	// ���S���
	void Dead();
	// �S�[�����
	void Goal();


	// AndroidSensorVector�̖߂�l��cPlayer���g����l�ɂ���
	cVector2 CalcSensorVector(VECTOR dxvector);

	// �ǔ���
	void CheckHitWall(void);

	// ���Ԑ؂�`�F�b�N
	void CheckTimeOver(void);

	// �A�j���[�V��������
	void Animation(void);
};