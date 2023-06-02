
#include <U8glib.h> //调用库

U8GLIB_SSD1306_128X64 u8g(13, 12, 11, 10); //oled使用的针脚


#include <OneWire.h> //调用库
#include <DallasTemperature.h> //调用库

#define ONE_WIRE_BUS 3   //定义传感器使用的针脚

OneWire oneWire(ONE_WIRE_BUS);        // 声明有这个传感器
DallasTemperature sensors(&oneWire);    // 将 oneWireh库的数据引用给 DallasTemperature库

int val; //设定全局变量


void setup(void) { //初始化屏幕
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // 显示白色
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // 最大亮度
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);        //黑白模式
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

  
  sensors.begin(); //初始化传感器
   Serial.begin(9600);  //串口通讯频率

}

void loop(void) {
  sensors.requestTemperatures(); // 发送命令获取温度
    Serial.print("实时温度为：");
  Serial.print(sensors.getTempCByIndex(0)); // 获取传感器摄氏温度数据，并串口输出
  Serial.println(" ℃\n");
  delay(500);

  
  val = sensors.getTempCByIndex(0); //将传感器数据转化为变量

  u8g.firstPage();  //刷新屏幕
  do {
    draw();
  } while( u8g.nextPage() );


}

void draw(void) {
  u8g.setFont(u8g_font_unifont); //设定
  u8g.drawStr( 15, 21, "temperature:"); //设定文字
  u8g.setFont(u8g_font_gdr14); //设定字体
  u8g.setPrintPos(30, 50);  // 设置光标位置
  u8g.print(val); // 显示传感器数据（变量）
  u8g.print(" 'C"); 

}

   
