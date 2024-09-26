/**
 * @author BlackTeaChan
 * @since 2024-07-08
 */
#include <Wire.h>
#include "OledFont.h"

// RES
#define RES_PIN A3
// 64x48屏
#define SCREEN1_I2C_ADDRESS 0x3C
// 128x64屏
#define SCREEN2_I2C_ADDRESS 0x3D

//RES
#define OLED_RES_Clr() digitalWrite(RES_PIN, LOW)
#define OLED_RES_Set() digitalWrite(RES_PIN, HIGH)
//写命令
#define OLED_CMD 0
//写数据
#define OLED_DATA 1

void setup() {
  Serial.begin(9600);
  pinMode(RES_PIN, OUTPUT);

  // 初始化屏幕
  Wire.begin();
  OLED_Init(SCREEN1_I2C_ADDRESS);
  OLED_Init(SCREEN2_I2C_ADDRESS);

  // 绘制铭牌
  OLED_Clear(SCREEN2_I2C_ADDRESS);
  OLED_DrawBMP(SCREEN2_I2C_ADDRESS, 0, 0, 128, 64, ROG_BMP);
  
}

void loop() {
  // 档位/信息切换
  OLED_Clear(SCREEN1_I2C_ADDRESS);
  OLED_DrawBMP(SCREEN1_I2C_ADDRESS, 0, 0, 64, 48, GEAR_BMP);

  delay(2000);

  OLED_Clear(SCREEN1_I2C_ADDRESS);
  OLED_ShowString(SCREEN1_I2C_ADDRESS, 0, 0, " HONDA", 16);
  OLED_ShowString(SCREEN1_I2C_ADDRESS, 0, 2, "CIVIC FK7", 8);
  OLED_ShowString(SCREEN1_I2C_ADDRESS, 0, 4, "BlackTea", 16);

  // OLED_Clear(SCREEN2_I2C_ADDRESS);
  // OLED_ShowString(SCREEN2_I2C_ADDRESS, 0, 0, "Screen 2", 16);
  // OLED_ShowString(SCREEN2_I2C_ADDRESS, 0, 2, "Display", 8);
  // OLED_ShowString(SCREEN2_I2C_ADDRESS, 0, 4, "Message", 16);

  delay(2000);
}

// *************************** OLED屏用 ***************************
// *************************** OLED屏用 ***************************
// *************************** OLED屏用 ***************************

// 初始化OLED显示屏函数
void OLED_Init(uint8_t i2cAddress) {
  OLED_RES_Clr();
  delay(200);
  OLED_RES_Set();
  if (i2cAddress == 0x3C) {
    OLED_WR_Byte(i2cAddress, 0xAE, OLED_CMD); /*display off*/
    OLED_WR_Byte(i2cAddress, 0x00, OLED_CMD); /*set lower column address*/
    OLED_WR_Byte(i2cAddress, 0x12, OLED_CMD); /*set higher column address*/
    OLED_WR_Byte(i2cAddress, 0x40, OLED_CMD); /*set display start line*/
    OLED_WR_Byte(i2cAddress, 0xB0, OLED_CMD); /*set page address*/
    OLED_WR_Byte(i2cAddress, 0x81, OLED_CMD); /*contract control*/
    OLED_WR_Byte(i2cAddress, 0xff, OLED_CMD); /*128*/
    OLED_WR_Byte(i2cAddress, 0xA1, OLED_CMD); /*set segment remap*/
    OLED_WR_Byte(i2cAddress, 0xA6, OLED_CMD); /*normal / reverse*/
    OLED_WR_Byte(i2cAddress, 0xA8, OLED_CMD); /*multiplex ratio*/
    OLED_WR_Byte(i2cAddress, 0x2F, OLED_CMD); /*duty = 1/48*/
    OLED_WR_Byte(i2cAddress, 0xC8, OLED_CMD); /*Com scan direction*/
    OLED_WR_Byte(i2cAddress, 0xD3, OLED_CMD); /*set display offset*/
    OLED_WR_Byte(i2cAddress, 0x00, OLED_CMD);
    OLED_WR_Byte(i2cAddress, 0xD5, OLED_CMD); /*set osc division*/
    OLED_WR_Byte(i2cAddress, 0x80, OLED_CMD);
    OLED_WR_Byte(i2cAddress, 0xD9, OLED_CMD); /*set pre-charge period*/
    OLED_WR_Byte(i2cAddress, 0x21, OLED_CMD);
    OLED_WR_Byte(i2cAddress, 0xDA, OLED_CMD); /*set COM pins*/
    OLED_WR_Byte(i2cAddress, 0x12, OLED_CMD);
    OLED_WR_Byte(i2cAddress, 0xdb, OLED_CMD); /*set vcomh*/
    OLED_WR_Byte(i2cAddress, 0x40, OLED_CMD);
    OLED_WR_Byte(i2cAddress, 0x8d, OLED_CMD); /*set charge pump enable*/
    OLED_WR_Byte(i2cAddress, 0x14, OLED_CMD);
    OLED_Clear(i2cAddress);
    OLED_WR_Byte(i2cAddress, 0xAF, OLED_CMD); /*display ON*/
  } else {
    OLED_WR_Byte(i2cAddress, 0xAE, OLED_CMD); /*display off*/
    OLED_WR_Byte(i2cAddress, 0x00, OLED_CMD); /*set lower column address*/
    OLED_WR_Byte(i2cAddress, 0x10, OLED_CMD); /*set higher column address*/
    OLED_WR_Byte(i2cAddress, 0xB0, OLED_CMD); /*set page address*/
    OLED_WR_Byte(i2cAddress, 0x40, OLED_CMD); /*set display start lines*/
    OLED_WR_Byte(i2cAddress, 0x81, OLED_CMD); /*contract control*/
    OLED_WR_Byte(i2cAddress, 0x88, OLED_CMD); /*4d*/
    OLED_WR_Byte(i2cAddress, 0x82, OLED_CMD); /* iref resistor set and adjust ISEG*/
    OLED_WR_Byte(i2cAddress, 0x00, OLED_CMD);
    OLED_WR_Byte(i2cAddress, 0xA1, OLED_CMD); /*set segment remap 0xA0*/
    OLED_WR_Byte(i2cAddress, 0xA2, OLED_CMD); /*set seg pads hardware configuration*/
    OLED_WR_Byte(i2cAddress, 0xA4, OLED_CMD); /*Disable Entire Display On (0xA4/0xA5)*/
    OLED_WR_Byte(i2cAddress, 0xA6, OLED_CMD); /*normal / reverse*/
    OLED_WR_Byte(i2cAddress, 0xA8, OLED_CMD); /*multiplex ratio*/
    OLED_WR_Byte(i2cAddress, 0x3F, OLED_CMD); /*duty = 1/64*/
    OLED_WR_Byte(i2cAddress, 0xC8, OLED_CMD); /*Com scan direction 0XC0*/
    OLED_WR_Byte(i2cAddress, 0xD3, OLED_CMD); /*set display offset*/
    OLED_WR_Byte(i2cAddress, 0x00, OLED_CMD); /* */
    OLED_WR_Byte(i2cAddress, 0xD5, OLED_CMD); /*set osc division*/
    OLED_WR_Byte(i2cAddress, 0xa0, OLED_CMD);
    OLED_WR_Byte(i2cAddress, 0xD9, OLED_CMD); /*set pre-charge period*/
    OLED_WR_Byte(i2cAddress, 0x22, OLED_CMD);
    OLED_WR_Byte(i2cAddress, 0xdb, OLED_CMD); /*set vcomh*/
    OLED_WR_Byte(i2cAddress, 0x40, OLED_CMD);
    OLED_WR_Byte(i2cAddress, 0x31, OLED_CMD); /* Set pump 7.4v */
    OLED_WR_Byte(i2cAddress, 0xad, OLED_CMD); /*set charge pump enable*/
    OLED_WR_Byte(i2cAddress, 0x8b, OLED_CMD); /*Set DC-DC enable (0x8a=disable; 0x8b=enable) */
    OLED_Clear(i2cAddress);
    OLED_WR_Byte(i2cAddress, 0xAF, OLED_CMD);
  }
}

// 发送一个字节
// mode:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(uint8_t i2cAddress, uint8_t dat, uint8_t mode) {
  Wire.beginTransmission(i2cAddress);
  if (mode) {
    Wire.write(0x40);
  } else {
    Wire.write(0x00);
  }
  Wire.write(dat);         // 发送一个字节
  Wire.endTransmission();  // 停止传输
}

// 清屏函数
void OLED_Clear(uint8_t i2cAddress) {
  uint8_t i, n;
  if (i2cAddress == 0x3C) {
    for (i = 0; i < 6; i++) {
      // 设置页地址（0~7）
      OLED_WR_Byte(i2cAddress, 0xb0 + i, OLED_CMD);
      // 设置显示位置—列低地址
      OLED_WR_Byte(i2cAddress, 0x00, OLED_CMD);
      // 设置显示位置—列高地址
      OLED_WR_Byte(i2cAddress, 0x12, OLED_CMD);
      for (n = 0; n < 64; n++) {
        OLED_WR_Byte(i2cAddress, 0, OLED_DATA);
      }
    }
  } else {
    for (i = 0; i < 8; i++) {
      //设置页地址（0~7）
      OLED_WR_Byte(i2cAddress, 0xb0 + i, OLED_CMD);
      //设置显示位置—列低地址
      OLED_WR_Byte(i2cAddress, 0x00, OLED_CMD);
      //设置显示位置—列高地址
      OLED_WR_Byte(i2cAddress, 0x10, OLED_CMD);
      for (n = 0; n < 128; n++) {
        OLED_WR_Byte(i2cAddress, 0, OLED_DATA);
      }
    }
  }
}

// 在指定位置显示一个字符
// x:0~127
// y:0~63
// sizey:选择字体 6x8  8x16
void OLED_ShowChar(uint8_t i2cAddress, uint8_t x, uint8_t y, const uint8_t chr, uint8_t sizey) {
  uint8_t c = 0, sizex = sizey / 2, temp;
  uint16_t i = 0, size1;
  if (sizey == 8) size1 = 6;
  else size1 = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * (sizey / 2);
  c = chr - ' ';  // 得到偏移后的值
  OLED_Set_Pos(i2cAddress, x, y);
  for (i = 0; i < size1; i++) {
    if (i % sizex == 0 && sizey != 8) OLED_Set_Pos(i2cAddress, x, y++);
    if (sizey == 8) {
      temp = pgm_read_byte(&asc2_0806[c][i]);
      OLED_WR_Byte(i2cAddress, temp, OLED_DATA);  // 6X8字号
    } else if (sizey == 16) {
      temp = pgm_read_byte(&asc2_1608[c][i]);
      OLED_WR_Byte(i2cAddress, temp, OLED_DATA);  // 8x16字号
    } else return;
  }
}

// 设置坐标
void OLED_Set_Pos(uint8_t i2cAddress, uint8_t x, uint8_t y) {
  if (i2cAddress == 0x3C) {
    x += 32;
  }
  OLED_WR_Byte(i2cAddress, 0xb0 + y, OLED_CMD);
  OLED_WR_Byte(i2cAddress, ((x & 0xf0) >> 4) | 0x10, OLED_CMD);
  OLED_WR_Byte(i2cAddress, (x & 0x0f), OLED_CMD);
}

// 显示字符号串
void OLED_ShowString(uint8_t i2cAddress, uint8_t x, uint8_t y, const char *chr, uint8_t sizey) {
  uint8_t j = 0;
  while (chr[j] != '\0') {
    OLED_ShowChar(i2cAddress, x, y, chr[j++], sizey);
    if (sizey == 8) x += 6;
    else x += sizey / 2;
  }
}

// 显示图片
// x,y显示坐标
// sizex,sizey,图片长宽
// BMP：要显示的图片
void OLED_DrawBMP(uint8_t i2cAddress, uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, const uint8_t BMP[]) {
  uint16_t j = 0;
  uint8_t i, m, temp;
  sizey = sizey / 8 + ((sizey % 8) ? 1 : 0);
  for (i = 0; i < sizey; i++) {
    OLED_Set_Pos(i2cAddress, x, i + y);
    for (m = 0; m < sizex; m++) {
      temp = pgm_read_byte(&BMP[j++]);
      OLED_WR_Byte(i2cAddress, temp, OLED_DATA);
    }
  }
}
