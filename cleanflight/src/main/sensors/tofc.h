
#pragma once

#include "drivers/gpio.h"


#define TOFC_DEVICE_COUNT 5
#define TOFC_DEVICE_START_ADDR 0x30

//tof = Laser Range Finder

typedef enum {
	TOFC_DEFAULT = 0,
	TOFC_NONE = 1,
	tofc_vl53l0x = 2,
	TOFC_FAKE
} tofcSensor_e;

typedef void(*tofcOpFuncPtr)(void);    // task operation

typedef enum {
	//CW:抖皐
	//TOFC_ALIGN_DEFAULT,   // driver-provided alignment
	TOFC_ALIGN_FRONT = 0,
	TOFC_ALIGN_RIGHT,
	TOFC_ALIGN_BACK,
	TOFC_ALIGN_LEFT,
	TOFC_ALIGN_BOTTOM
	//TOFC_ALIGN_Z_CW0_DEG = 1,
	//TOFC_ALIGN_Z_CW90_DEG = 2,
	//TOFC_ALIGN_Z_CW180_DEG = 3,
	//TOFC_ALIGN_Z_CW270_DEG = 4,
	//TOFC_ALIGN_Z_CW0_DEG_X_CW90_DEG = 5
} TOFC_align_e;



typedef struct tofDevice_s {
	GPIO_TypeDef* i2cXsdnGpioType; //﹍てㄏノXsdn pin type
	gpio_config_t i2cXsdnGpioCfg; //﹍てㄏノXsdn pin Config
	uint8_t i2cAddr;
	//tofcOpFuncPtr init; //砞﹚禯瞒秖代家Α
} tofDevice_t;
typedef struct tofData_s {
	uint16_t range;

	uint16_t valid_range_min;
	uint16_t valid_range_max;
	// -------- VL53L0X --------
	uint8_t rangeStatus;
	uint8_t deviceError;
	uint16_t ambientRate;
	uint32_t signalRate;
	uint16_t effectiveSpadRtnCount;
	// -------------------------
} tofcData_t;
typedef struct tofConfig_s {
	uint32_t validRangeWaitLimit;


} tofcConfig_t;

typedef struct TOFC_s {
	//int tofDeviceCount;
	bool enable; //琌币ノ
	tofDevice_t device;
	tofcData_t data;
	
	uint16_t lastValidRange;
	uint32_t lastValidRangeDaltaTime;

	
	// ----- i2c -----
	//tofcOpFuncPtr setRangeingMode; //砞﹚禯瞒秖代家Α
	//tofcOpFuncPtr rangingMeasurement; //device秨﹍秖代(single shot mode)
	//tofcOpFuncPtr getRangingMeasurementData; //device眔秖代挡狦
} tofc_t;

extern int16_t TOFC_angle[ANGLE_INDEX_COUNT];
extern tofc_t tofc[TOFC_DEVICE_COUNT];
extern bool tofc_debug_avoidanceMode;

void tofcInit(void);
void tofcUpdate(void);
void updateTofcStateForAvoidanceMode(void);

bool isAltitudeTofcEnable(void);
int32_t tofcCalculateAltitude(void);

//void resetDistanceTrims(distanceTrims_t *distanceTrims);
//void updateLaserRangeFinderReadings(distanceTrims_t *distanceTrims);
//void setLaserRangeFinderTrims(flightDynamicsTrims_t *laserRangeFinderTrimsToUse);



