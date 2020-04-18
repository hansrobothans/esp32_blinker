#define BLINKER_WIFI
#define BLINKER_PRINT Serial
#define LED_BUILTIN 12
#include <Blinker.h>
 

char auth[] = "3b20d5f70223";
char ssid[] = "HANS";
char pswd[] = "yong990511";

 
// 新建组件对象
BlinkerButton Button1("btn-abc");
 
// 按下按键即会执行该函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    if (state=="on") {
        digitalWrite(LED_BUILTIN, LOW);
        // 反馈开关状态
        Button1.print("on");
    } else if(state=="off"){
        digitalWrite(LED_BUILTIN, HIGH);
        // 反馈开关状态
        Button1.print("off");
    }
}
 
void setup() {
    // 初始化串口，并开启调试信息
    Serial.begin(115200);   
     
    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif
    
    // 初始化有LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);
}
 
void loop() {
    Blinker.run();
}
