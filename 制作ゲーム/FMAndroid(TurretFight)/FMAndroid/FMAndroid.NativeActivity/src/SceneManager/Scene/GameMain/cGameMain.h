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
	enum STATE
	{
		START,		// �J�n���o��
		PLAY,		// �Q�[�����C����
		OVER,		// �Q�[���I�[�o�[��
	};

	cGameMain(IBaseObject* parent);
	~cGameMain(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	inline const short GetDifficult(void) { return m_nDifficult; };
private:


	static const short MAX_DIFFICULT;		// �ő��Փx
	static const float LEVELUP_TIME;		// �Q�[�����x�����オ��Ԋu

	short m_nDifficult;
	STATE m_eState;


	void ControlGameLevel(void);

	void Start(void);
	void Play(void);
	void Over(void);
};
//================================================================================================