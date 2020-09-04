#pragma once

#include "..\IButton.h"

class cStartButton : public IButton
{
public:
	cStartButton(IBaseObject* parent);

	void Initialize(void);

private:
	void Neutral(void);
	void Trigger(void);
	void Pressed(void);
	void Release(void);

	// �\���D��x
	static const int	PRIORITY;

	// ������Ă����Ԃ��痣�ꂽ��ԂɂȂ������̊m�F�t���O
	bool m_bPressed;
};
