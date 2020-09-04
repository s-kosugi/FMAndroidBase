#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmBlue.h													*/
/*  @brief		:	���G�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "..\IEnemy.h"

//================================================================================================
// ���G�N���X
class cEnmBlue : public IEnemy
{
public:
	cEnmBlue(IBaseObject* parent);
	~cEnmBlue(void);

	// ������
	void Initialize(const cVector2& pos) override;

	// �X�V
	void Update(void) override;

	// �ʏ���
	void Normal(void) override;

protected:
	void AreaOutAllProc(void) override;

private:
	//--------------------------------------------------------------------------------------------
	// �萔

	// �\���D��x
	static const int	PRIORITY;

	// ���]���x
	static const float	ROTATE_SPEED;
	
	// �����
	static const int	BASE_DIST;

	// �ŏ����B����
	static const int	MIN_TIME;
	
	// �ő哞�B����
	static const int	MAX_TIME;
	//--------------------------------------------------------------------------------------------

};
//================================================================================================