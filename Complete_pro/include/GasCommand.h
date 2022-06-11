#ifndef GASCOMMAND_H_INCLUDE
#define GASCOMMAND_H_INCLUDE

#include <WiFiClientSecure.h>

//Google Apps Scriptと橋渡しを行うクラス
class GasCommand
{
private:
    void postValues(String exec_url , String values);

    /* data */
public:
    GasCommand();
    ~GasCommand();
    
    void sendMail(String exec_url,String cDate,String cTime,String sensVal);
    void writess(String exec_url,String cDate,String cTime,String sensVal);
    String connectingWIFI(const char* ssid ,const char* password);
};



#endif