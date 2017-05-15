#define DEBUG       0      //串口调试功能  打开/关闭.
#define PIN_LED     12     //彩灯引脚
#define LED_NUM     2      //彩灯的数量
#define PIN_LINEA    A0      //灰度传感器A引脚.
#define PIN_LINEB    A2      //灰度传感器B引脚.
#define PIN_KEY      6       //碰撞开关引脚.
#define PIN_BUZZER   10      //蜂鸣器引脚.

#define BRIGHT_MAX  255    //LED彩灯显示的最大亮度。最大亮度是255，最小亮度是0
#define DOCK_MAX    700     //灰度传感器的最小触发值。增大该值后，意味着你需要颜色更深的物体去触发灰度传感器
