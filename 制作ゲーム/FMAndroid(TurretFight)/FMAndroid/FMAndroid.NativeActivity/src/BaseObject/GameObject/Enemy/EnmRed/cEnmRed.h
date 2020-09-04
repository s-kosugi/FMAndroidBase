#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEnmRed.h													*/
/*  @brief		:	赤い敵クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "..\IEnemy.h"

//================================================================================================
// 赤い敵クラス
class cEnmRed : public IEnemy
{
public:
	cEnmRed(IBaseObject* parent);
	~cEnmRed(void);

	// 初期化
	void Initialize(const cVector2& pos) override;

	// 更新
	void Update(void) override;

	enum class ACTION_STATE
	{
		START,
		STOP,
		RESTART
	};

private:
	//--------------------------------------------------------------------------------------------
	// 定数

	// 表示優先度
	static const int	PRIORITY;

	// 基本移動力
	static const float	BASE_SPEED;

	// 自転速度
	static const float	ROTATE_SPEED;

	// 停止距離
	static const float	STOP_DIST;

	// 停止にかかる時間
	static const float  STOP_TIME;

	// 再始動にかかる時間
	static const float  RESTART_TIME;

	// 再始動最大速度
	static const float  RESTART_MAX_SPEED;

	//--------------------------------------------------------------------------------------------

	ACTION_STATE m_eActionState;

	void Start(void);
	void Stop(void);
	void Restart(void);

};
//================================================================================================