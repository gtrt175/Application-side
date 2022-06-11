#ifndef SENSORCONTROL_H_INCLUDE
#define SENSORCONTROL_H_INCLUDE

class SensorControl
{
private:
    int sensorLevel;    //グローブの感度格納用

public:
    SensorControl(int setVal);
    ~SensorControl();
    void setSensorLevel(int writeVal);
    int getSensorLevel();

};


#endif