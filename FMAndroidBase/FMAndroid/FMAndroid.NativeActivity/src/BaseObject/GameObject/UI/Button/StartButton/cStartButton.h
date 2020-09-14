#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cStartButton.h												*/
/*  @brief		:	スタートボタンクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/17													*/
/*																				*/
/*==============================================================================*/
#include "..\IButton.h"

// スタートボタンクラス
class cStartButton : public IButton
{
public:
	cStartButton(IBaseObject* parent);

	void Initialize(void) override;

private:
	void Neutral(void) override;
	void Trigger(void) override;
	void Pressed(void) override;
	void Release(void) override;

	// 表示優先度
	static const int	PRIORITY;

	// 押されている状態から離れた状態になったかの確認フラグ
	bool m_bPressed;
};
