#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.h													*/
/*  @brief		:	�Q�[�����C���V�[��											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// �Q�[�����C���V�[��
class cGameMain : public IBaseScene
{
public:
	cGameMain(IBaseObject* parent);
	~cGameMain(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	int GetOverTimeMinute(void);
	int GetOverTimeSecond(void);

	// �Q�[�����C�����
	enum class STATE {
		START,
		MAIN,
		CLEAR,
		OVER,
	};

private:
	static const float TIME_OVER_LIMIT;
	static const float GOAL_TIME;
	static const float DEAD_TIME;
	static const float START_TIME;

	// �Q�[�����C�����
	STATE m_eState;


	// ��ԕʏ���
	// �J�n
	void Start(void);
	// ���C��
	void Main(void);
	// �N���A
	void Clear(void);
	// �Q�[���I�[�o�[
	void Over(void);
};
//================================================================================================