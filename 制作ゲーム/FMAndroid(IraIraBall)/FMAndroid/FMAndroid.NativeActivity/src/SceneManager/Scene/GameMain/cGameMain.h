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
	cGameMain(IBaseObject* parent);
	~cGameMain(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	int GetOverTimeMinute(void);
	int GetOverTimeSecond(void);

	// ゲームメイン状態
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

	// ゲームメイン状態
	STATE m_eState;


	// 状態別処理
	// 開始
	void Start(void);
	// メイン
	void Main(void);
	// クリア
	void Clear(void);
	// ゲームオーバー
	void Over(void);
};
//================================================================================================