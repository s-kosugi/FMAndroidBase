#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSensor.h													*/
/*  @brief		:	�Z���T�[�N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/07/27													*/
/*																				*/
/*==============================================================================*/

#include "BaseObject\IBaseObject.h"
#include <DxLib.h>
#include "Utility/Vector/cVector3.h"

class cSensor : public IBaseObject
{
public:

	void Initialize(void);

	// �����x�Z���T�[�l�̎擾
	inline cVector3 GetAccele( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_ACCELEROMETER); return cVector3(v.x, v.y, v.z);};
	// ���E�Z���T�[�l�̎擾
	inline cVector3 GetMagnet( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_MAGNETIC_FIELD); return cVector3(v.x, v.y, v.z);};
	// �W���C���Z���T�[�l�̎擾
	inline cVector3 GetGyro( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_GYROSCOPE); return cVector3(v.x, v.y, v.z);};
	// �Ɠx�Z���T�[�l�̎擾
	inline cVector3 GetLight( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_LIGHT); return cVector3(v.x, v.y, v.z);};
	// �ߐڃZ���T�[�l�̎擾
	inline cVector3 GetProximity( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_PROXIMITY); return cVector3(v.x, v.y, v.z);};
	// �����Z���T�[�l�̎擾
	inline cVector3 GetPressure( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_PRESSURE); return cVector3(v.x, v.y, v.z);};
	// ���x�Z���T�[�l�̎擾
	inline cVector3 GetTemperature( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_AMBIENT_TEMPERATURE); return cVector3(v.x, v.y, v.z);};

	
private:
	
	


	//-----------------------------------------------------------------------------------------------------
	// �V���O���g���p
private:
	cSensor(void) { };     //  ������̐������֎~
	cSensor(IBaseObject* parent) {  };
	cSensor(IBaseObject* parent, const std::string& name) { };
	~cSensor(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cSensor(const cSensor& t) {};       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cSensor& operator = (const cSensor& t) { return *this; };  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cSensor& GetInstance(void) {
		static cSensor instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
	//-----------------------------------------------------------------------------------------------------
};