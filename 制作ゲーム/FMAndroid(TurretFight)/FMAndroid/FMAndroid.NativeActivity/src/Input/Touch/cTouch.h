#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTouch.h													*/
/*  @brief		:	�^�b�`���̓N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/07/22													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseObject.h"
#include <DxLib.h>
#include <map>
#include "Utility/Vector/cVector2.h"

class cTouch : public IBaseObject
{
public:

	// �^�b�`���
	enum class TOUCH_STATE
	{
		NONE = -1,
		TRIGGER = 0,
		BUTTON,
		RELEASE
	};
	// �^�b�`�\����
	struct TOUCHPTEX
	{
		TOUCHINPUTPOINT pt;				// �^�b�`�\����
		TOUCH_STATE		state;			// ���݂̃^�b�`���
	};


	void Initialize(void);
	void Update(void);

	// ����ӏ��͈̔͂��^�b�`����Ă��邩���m�F����(�~����)
	// pos   : �w��|�C���g
	// state : ���ׂ����^�b�`���
	// range : �w��|�C���g���璲�ׂ����͈�
	// ret   : true �w��ӏ����Y���̏�Ԃ�����
	bool CheckHitCircle( const cVector2& pos, TOUCH_STATE state, float range);

	// ����ӏ��͈̔͂��^�b�`����Ă��邩���m�F����(��`����)
	// pos   : �w��|�C���g
	// state : ���ׂ����^�b�`���
	// range : �w��|�C���g���璲�ׂ����͈�
	// ret   : true �w��ӏ����Y���̏�Ԃ�����
	bool CheckHitBox( const cVector2& pos, TOUCH_STATE state, POINT range);

	// �^�b�`���z����擾����
	inline const std::map<int, TOUCHPTEX>& GetMapTouch(void) { return m_mapTouchPoint; };


	// �^�b�`���W�̎擾
	// touchID : �擾����^�b�`ID
	// pt      : �擾������W�̎Q��
	// state   : �^�b�`���
	// ret     : true �^�b�`��񂪑��݂��Ă����B false �^�b�`��񂪑��݂��Ă��Ȃ�
	bool GetTouchPos(int touchID, POINT& pt);
	bool GetTouchPos(int touchID, POINT & pt, TOUCH_STATE& state);

	// �^�b�`���擾
	int GetTouchNum(void);

private:
	std::map<int, TOUCHPTEX> m_mapTouchPoint;		// �^�b�`���A�z�z��@�L�[�l : �^�b�`ID

#ifdef DEBUG
	// �f�o�b�O���O�Ƀ^�b�`�̃��O��\������
	void DrawTouchDebugLog(void);					
#endif // DEBUG

	//-----------------------------------------------------------------------------------------------------
	// �V���O���g���p
private:
	cTouch(void) { };     //  ������̐������֎~
	cTouch(IBaseObject* parent) {  };
	cTouch(IBaseObject* parent, const std::string& name) { };
	~cTouch(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cTouch(const cTouch& t) {};       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cTouch& operator = (const cTouch& t) { return *this; };  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cTouch& GetInstance(void) {
		static cTouch instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
	//-----------------------------------------------------------------------------------------------------
};