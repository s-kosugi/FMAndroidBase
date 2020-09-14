#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cSensor.h													*/
/*  @brief		:	センサークラス												*/
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

	void Initialize(void) override;

	// 加速度センサー値の取得
	inline cVector3 GetAccele( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_ACCELEROMETER); return cVector3(v.x, v.y, v.z);};
	// 磁界センサー値の取得
	inline cVector3 GetMagnet( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_MAGNETIC_FIELD); return cVector3(v.x, v.y, v.z);};
	// ジャイロセンサー値の取得
	inline cVector3 GetGyro( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_GYROSCOPE); return cVector3(v.x, v.y, v.z);};
	// 照度センサー値の取得
	inline cVector3 GetLight( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_LIGHT); return cVector3(v.x, v.y, v.z);};
	// 近接センサー値の取得
	inline cVector3 GetProximity( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_PROXIMITY); return cVector3(v.x, v.y, v.z);};
	// 加圧センサー値の取得
	inline cVector3 GetPressure( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_PRESSURE); return cVector3(v.x, v.y, v.z);};
	// 温度センサー値の取得
	inline cVector3 GetTemperature( void ) { VECTOR v = GetAndroidSensorVector(DX_ANDROID_SENSOR_AMBIENT_TEMPERATURE); return cVector3(v.x, v.y, v.z);};

	
private:
	
	


	//-----------------------------------------------------------------------------------------------------
	// シングルトン用
private:
	cSensor(void) { };     //  他からの生成を禁止
	cSensor(IBaseObject* parent) {  };
	cSensor(IBaseObject* parent, const std::string& name) { };
	~cSensor(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cSensor(const cSensor& t) {};       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cSensor& operator = (const cSensor& t) { return *this; };  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	IBaseObject* Finalize(void) override { IBaseObject::Finalize(); return nullptr; };

	static cSensor& GetInstance(void) {
		static cSensor instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
	//-----------------------------------------------------------------------------------------------------
};