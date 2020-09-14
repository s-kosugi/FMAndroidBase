#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	IButton.h													*/
/*  @brief		:	�^�b�`�{�^�����N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/17													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cSpriteObject.h"

// ���{�^���N���X
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
		NEUTRAL,		// ������Ă��Ȃ�
		TRIGGER,		// �������u��
		PRESSED,		// ������Ă����
		RELEASE,		// �������u��
	};
	virtual void Neutral(void) = 0;
	virtual void Trigger(void) = 0;
	virtual void Pressed(void) = 0;
	virtual void Release(void) = 0;

	BUTTON_STATE m_eButtonState;	// ���݂̃{�^�����

private:
	static const int PRIORITY = 100;
};
