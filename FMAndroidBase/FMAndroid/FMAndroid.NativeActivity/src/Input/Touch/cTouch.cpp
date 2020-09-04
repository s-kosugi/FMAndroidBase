/*==============================================================================*/
/*																				*/
/*	@file title	:	cTouch.cpp													*/
/*  @brief		:	�^�b�`���̓N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/07/22													*/
/*																				*/
/*==============================================================================*/

#include "cTouch.h"
#include "Utility/Vector/cVector2.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#include <sstream>
#endif

//==========================================================================================
// ������
//==========================================================================================
void cTouch::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "Touch";

	m_mapTouchPoint.clear();

	IBaseObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cTouch::Update(void)
{
	//--------------------------------------------------------------------------------------
	// �^�b�`���擾�O�X�V
	int touchNum = GetTouchInputNum();
	// �^�b�`����Ȃ�������Ԃ𔻒肷�邽�߂Ɉ�U�^�b�`��Ԃ��_�~�[�ɂ���
	if (!m_mapTouchPoint.empty())
	{
		for (auto it = m_mapTouchPoint.begin(); it != m_mapTouchPoint.end(); it++)
		{
			if ((*it).second.state != TOUCH_STATE::RELEASE)
			{
				(*it).second.state = TOUCH_STATE::NONE;
			}
			else
			{
				// �O�t���[����RELEASE��Ԃ̃^�b�`�͍폜����
				it = m_mapTouchPoint.erase(it);
				if (it == m_mapTouchPoint.end()) break;
			}
		}
	}

	//--------------------------------------------------------------------------------------
	// �^�b�`���X�V
	for (int i = 0; i < touchNum; i++)
	{
		int x, y, id, dev;
		GetTouchInput(i, &x, &y, &id, &dev);

#ifdef DEBUG
		// �^�b�`�̃|�C���g��\������
		cDebugFunc::GetInstance().RegistDrawCircle({ (float)x,(float)y }, 3.0f, 0x77ffffff);
#endif

		auto it = m_mapTouchPoint.find(id);
		// �v�f���o�^����Ă��Ȃ��ꍇ�͐V�K�^�b�`��o�^����
		if (it == m_mapTouchPoint.end())
		{
			TOUCHPTEX data;
			data.pt.Device = dev;
			data.pt.ID = id;
			data.pt.PositionX = x;
			data.pt.PositionY = y;
			data.state = TOUCH_STATE::TRIGGER;

			// �A�z�z��Ƀf�[�^��ǉ�����
			//m_mapTouchPoint.insert(std::make_pair(id,data)); // insert�֐����g�����@
			m_mapTouchPoint[id] = data;		// �v�f�ԍ�(�L�[)���w�肷����@
		}
		else
			// ���ɂ���^�b�`�̏ꍇ�͘A�z�z��̍��W���X�V����
		{
			(*it).second.pt.PositionX = x;
			(*it).second.pt.PositionY = y;
			(*it).second.state = TOUCH_STATE::BUTTON;
		}
	}

	//--------------------------------------------------------------------------------------
	// �^�b�`���擾���ԍX�V
	// �^�b�`����ĂȂ�������^�b�`�����ꂽ����ɂ���
	for (auto it = m_mapTouchPoint.begin(); it != m_mapTouchPoint.end(); it++)
	{
		if ((*it).second.state == TOUCH_STATE::NONE) (*it).second.state = TOUCH_STATE::RELEASE;
	}
	IBaseObject::Update();
}

//==========================================================================================
// ����ӏ��͈̔͂��^�b�`����Ă��邩���m�F����(�~����)
// pos   : �w��|�C���g
// state : ���ׂ����^�b�`���
// range : �w��|�C���g���璲�ׂ����͈�
// ret : true �w��ӏ����Y���̏�Ԃ�����
//==========================================================================================
bool cTouch::CheckHitCircle(const cVector2& pos, TOUCH_STATE state, float range)
{
	if (m_mapTouchPoint.empty()) return false;

	for (auto it : m_mapTouchPoint)
	{
		if (it.second.state != state) continue;

		cVector2 touch((float)it.second.pt.PositionX, (float)it.second.pt.PositionY);
		// �^�b�`���w��͈͓��ɂ�����
		if (range >= touch.CalcTwoPointDist(pos)) return true;
	}

	return false;
}

//==========================================================================================
// ����ӏ��͈̔͂��^�b�`����Ă��邩���m�F����(��`����)
// pos   : �w��|�C���g�̒��S�_
// state : ���ׂ����^�b�`���
// range : �w��|�C���g���璲�ׂ����͈�
// ret : true �w��ӏ����Y���̏�Ԃ�����
//==========================================================================================
bool cTouch::CheckHitBox(const cVector2 & pos, TOUCH_STATE state, POINT range)
{
	if (m_mapTouchPoint.empty()) return false;

	for (auto it : m_mapTouchPoint)
	{
		if (it.second.state != state) continue;

		cVector2 touch((float)it.second.pt.PositionX, (float)it.second.pt.PositionY);
		// �^�b�`���w��͈͓��ɂ�����
		if (pos.x - range.x / 2 <= touch.x &&
			pos.x + range.x / 2 >= touch.x &&
			pos.y - range.y / 2 <= touch.y &&
			pos.y + range.y / 2 >= touch.y
			)
		{
			return true;
		}
	}

	return false;
}

//==========================================================================================
// �^�b�`���W�̎擾
// touchID : �擾����^�b�`ID
// pt      : �擾������W�̎Q��
// ret     : true �^�b�`��񂪑��݂��Ă����B false �^�b�`��񂪑��݂��Ă��Ȃ�
//==========================================================================================
bool cTouch::GetTouchPos(int touchID, POINT & pt)
{
	if (m_mapTouchPoint.empty()) return false;

	auto it = m_mapTouchPoint.find(touchID);

	if (it == m_mapTouchPoint.end()) return false;

	pt.x = (*it).second.pt.PositionX;
	pt.y = (*it).second.pt.PositionY;

	return true;
}
//==========================================================================================
// �^�b�`���W�̎擾
// touchID : �擾����^�b�`ID
// pt      : �擾������W�̎Q��
// ret     : true �^�b�`��񂪑��݂��Ă����B false �^�b�`��񂪑��݂��Ă��Ȃ�
//==========================================================================================
bool cTouch::GetTouchPos(int touchID, POINT & pt, cTouch::TOUCH_STATE& state)
{
	if (m_mapTouchPoint.empty()) return false;

	auto it = m_mapTouchPoint.find(touchID);

	if (it != m_mapTouchPoint.end())
	{
		pt.x = it->second.pt.PositionX;
		pt.y = it->second.pt.PositionY;
		state = it->second.state;
		return true;
	}

	return false;
}
//==========================================================================================
// �^�b�`���擾
//==========================================================================================
int cTouch::GetTouchNum(void)
{
	return GetTouchInputNum();
}

#ifdef DEBUG
//==========================================================================================
// �f�o�b�O���O�Ƀ^�b�`�̃��O��\������
//==========================================================================================
void cTouch::DrawTouchDebugLog(void)
{
	// �^�b�`����Ă�����W���f�o�b�O���O�ŕ\������
	for (auto it : m_mapTouchPoint)
	{
		std::ostringstream oss;
		oss << "Touch" << it.first << "::X : " << it.second.pt.PositionX << " Y :" << it.second.pt.PositionY;
		cDebugFunc::GetInstance().PushDebugLog(oss.str().c_str());
	}
}
#endif // DEBUG
