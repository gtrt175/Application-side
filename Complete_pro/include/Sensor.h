#ifndef SENSOR_H_INCLUDE
#define SENSOR_H_INCLUDE

class Sensor
{
private:
    int sensorLevel;
    /* data */
public:
    Sensor(/* args */);
    ~Sensor();
    void setSensorLevel(int val);
    int getSensorLevel();
};

Sensor::Sensor()
{
    sensorLevel = 1; //とりあえず1に初期化しておくコンストラクタ
}

Sensor::~Sensor()
{
}

//セーブ値を受け取ってsensorValueを更新する関数
void Sensor::setSensorLevel(int val) 
{
    sensorLevel = val; //センサの値を引数で上書き
}

//センサ値を安全に受け取るための関数　アクセサ
int Sensor::getSensorLevel()
{
    return sensorLevel; //sensorValueを返す
}


#endif