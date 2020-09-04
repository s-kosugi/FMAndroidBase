#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmYellow.h												*/
/*  @brief		:	���F���G�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "..\IEnemy.h"

//================================================================================================
// ���F���G�N���X
class cEnmYellow : public IEnemy
{
public:
	cEnmYellow(IBaseObject* parent);
	~cEnmYellow(void);

	// ������
	void Initialize(const cVector2& pos) override;

	// �X�V
	void Update(void) override;

private:
	//--------------------------------------------------------------------------------------------
	// �萔

	// �\���D��x
	static const int	PRIORITY;

	// ��{�ړ���
	static const float	BASE_SPEED;

	// ���]���x
	static const float	ROTATE_SPEED;

	//--------------------------------------------------------------------------------------------

	// �o������
	IEnemy::DIRECTION m_ePopDirection;
};
//================================================================================================