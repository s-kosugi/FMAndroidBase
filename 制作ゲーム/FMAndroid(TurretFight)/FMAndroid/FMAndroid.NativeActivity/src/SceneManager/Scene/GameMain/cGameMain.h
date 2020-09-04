#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cGameMain.h													*/
/*  @brief		:	ゲームメインシーン											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// ゲームメインシーン
class cGameMain : public IBaseScene
{
public:
	enum STATE
	{
		START,		// 開始演出中
		PLAY,		// ゲームメイン中
		OVER,		// ゲームオーバー中
	};

	cGameMain(IBaseObject* parent);
	~cGameMain(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	inline const short GetDifficult(void) { return m_nDifficult; };
private:


	static const short MAX_DIFFICULT;		// 最大難易度
	static const float LEVELUP_TIME;		// ゲームレベルが上がる間隔

	short m_nDifficult;
	STATE m_eState;


	void ControlGameLevel(void);

	void Start(void);
	void Play(void);
	void Over(void);
};
//================================================================================================