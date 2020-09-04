#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IButton.h													*/
/*  @brief		:	タッチボタン基底クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/17													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cSpriteObject.h"
// ボタンクラス
class IButton : public cSpriteObject
{
public:
	IButton(IBaseObject* parent, std::string objectname, std::string filename);
	~IButton(void);

	virtual void Initialize(void);
	virtual void Initialize(const cVector2& pos);
	virtual void Update(void);
	virtual IBaseObject* Finalize(void);
protected:
	enum class BUTTON_STATE
	{
		NEUTRAL,		// 押されていない
		TRIGGER,		// 押した瞬間
		PRESSED,		// 押されている間
		RELEASE,		// 離した瞬間
	};
	virtual void Neutral(void) = 0;
	virtual void Trigger(void) = 0;
	virtual void Pressed(void) = 0;
	virtual void Release(void) = 0;

	BUTTON_STATE m_eButtonState;	// 現在のボタン状態

private:
	static const int PRIORITY = 100;
};
