#include "SensorControl.h"
#include <M5Stack.h>

SensorControl::SensorControl(int setVal)
{
    sensorLevel = setVal; //グローブ感度初期化
}

SensorControl::~SensorControl()
{
}

//値を受け取ってグローブ感度を上書きする関数
void SensorControl::setSensorLevel(int writeVal) 
{
    sensorLevel = writeVal; 
}

//グローブ感度値を返す関数
int SensorControl::getSensorLevel()
{
    return sensorLevel; 
}

