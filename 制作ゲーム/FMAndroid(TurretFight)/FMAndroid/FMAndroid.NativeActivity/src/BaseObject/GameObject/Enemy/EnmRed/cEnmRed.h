#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmRed.h													*/
/*  @brief		:	�Ԃ��G�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "..\IEnemy.h"

//================================================================================================
// �Ԃ��G�N���X
class cEnmRed : public IEnemy
{
public:
	cEnmRed(IBaseObject* parent);
	~cEnmRed(void);

	// ������
	void Initialize(const cVector2& pos) override;

	// �X�V
	void Update(void) override;

	enum class ACTION_STATE
	{
		START,
		STOP,
		RESTART
	};

private:
	//--------------------------------------------------------------------------------------------
	// �萔

	// �\���D��x
	static const int	PRIORITY;

	// ��{�ړ���
	static const float	BASE_SPEED;

	// ���]���x
	static const float	ROTATE_SPEED;

	// ��~����
	static const float	STOP_DIST;

	// ��~�ɂ����鎞��
	static const float  STOP_TIME;

	// �Ďn���ɂ����鎞��
	static const float  RESTART_TIME;

	// �Ďn���ő呬�x
	static const float  RESTART_MAX_SPEED;

	//--------------------------------------------------------------------------------------------

	ACTION_STATE m_eActionState;

	void Start(void);
	void Stop(void);
	void Restart(void);

};
//================================================================================================