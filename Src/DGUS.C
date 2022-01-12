#include  "main.h"
#include  <dgus.h>
#include  "usart.h"
#include "string.h"

#define uartport 0
#define bufsize 100

extern char ScreenStatus;
//extern int INIT_X0;
//extern int INIT_Y0;
//extern int INIT_X1;
//extern int INIT_Y1;
//默认uart0
//void uartsendbyte(char bytedata)
//{
//  while(!(((UART0 -> LSR) & 0X20) == 0X20)) ; 
//  UART0 -> THR =bytedata;
//}

//void uart1sendbyte(char bytedata)
//{
//  while(!(((UART1 -> LSR) & 0X20) == 0X20)) ; 
//  UART1 -> THR =bytedata;
//}
//void uart3sendbyte(char bytedata)
//{
//  while(!(((UART3 -> LSR) & 0X20) == 0X20)) ; 
//  UART3 -> THR =bytedata;
//}

//void uartsendstr(unsigned char *str,unsigned char length)
//{
//  int sendi=0;
//  while(*(str+sendi)!='\0'&&*(str+sendi)!=0x1b&&(length!=0))
//  {
//   while(!(((UART0 -> LSR) & 0X20) == 0X20)) ; 
//  UART0 -> THR =*(str+sendi);
//  sendi++; 
//  length--;
//  }

//}



void set_DWIN_display(void)
{
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0xE3);
    uartsendbyte(&huart5,0x55);
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x5A);
    uartsendbyte(&huart5,0xA5); 
    uartsendbyte(&huart5,0x00);
    uartsendbyte(&huart5,0x07);
    uartsendbyte(&huart5,0x00);
    uartsendbyte(&huart5,0xFF);    
    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
     
}

void set_DWIN_touch(void)
{
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0xE0);
    uartsendbyte(&huart5,0x55);
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x5A);
    uartsendbyte(&huart5,0xA5); 
    uartsendbyte(&huart5,0x00);
    uartsendbyte(&huart5,0x07);//115200
    uartsendbyte(&huart5,0x40);//01001011
    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
     
}


void clear_DWIN(void)
{
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x52);
    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
  disp_line(INIT_X0,INIT_Y0,INIT_X0,INIT_Y1);//  两点之间划线(x0,y0)  (x1,y1)  左
  disp_line(INIT_X0,INIT_Y0,INIT_X1,INIT_Y0); //上
  disp_line(INIT_X1,INIT_Y0,INIT_X1,INIT_Y1);//  右
  disp_line(INIT_X0,INIT_Y1,INIT_X1,INIT_Y1); //下
  
}


void set_light_on(int L_on)
{
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x5F);
    uartsendbyte(&huart5,L_on);
    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
     
}

void set_light(int V_ON,int V_OFF,int V_TIME)
{
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x5E);
    uartsendbyte(&huart5,0x55);
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x5A);
    uartsendbyte(&huart5,0xA5);
    uartsendbyte(&huart5,V_ON);
    uartsendbyte(&huart5,V_OFF);
    uartsendbyte(&huart5,V_TIME);
    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
     
}

void set_colour_back(void)
{
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x40);
    uartsendbyte(&huart5,0xff);//
    uartsendbyte(&huart5,0x82);//设置前景色 黄色
    uartsendbyte(&huart5,0x00);//
    uartsendbyte(&huart5,0x00); //设置背景色 黑色 
    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
     
}

//两点之间划线(x0,y0)  (x1,y1)  像素点 1024*768
void disp_line(int x0,int y0,int x1,int y1)
{
   int temp_x0,temp_y0,temp_x1,temp_y1; 

    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x56);
    
    temp_x0=x0/256;
    uartsendbyte(&huart5,temp_x0);//
    temp_x0=x0%256;//
    uartsendbyte(&huart5,temp_x0);//send x0
    
    temp_y0=y0/256;
    uartsendbyte(&huart5,temp_y0);//
    temp_y0=y0%256;//
    uartsendbyte(&huart5,temp_y0);//send y0
    
    temp_x1=x1/256;
    uartsendbyte(&huart5,temp_x1);//
    temp_x1=x1%256;//
    uartsendbyte(&huart5,temp_x1);//send x1
    
    temp_y1=y1/256;
    uartsendbyte(&huart5,temp_y1);//
    temp_y1=y1%256;//
    uartsendbyte(&huart5,temp_y1);//send y1

    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
     
}
//将行列转化为像素点画底划线
void disp_line_PX(int row,int lie0,int lie1)
{
   int temp_x0,temp_y0,temp_x1,temp_y1;
   int x0,y0,x1,y1;
    x0=INIT_X0+20+lie0*12;   //转化为左上角像素点坐标x0
    y0=INIT_Y0+9+row*24;   //转化为左上角像素点坐标y0
    x1=INIT_X0+20+(lie1-1)*12;  //转化为右下角像素点坐标x1
    y1=INIT_Y0+9+row*24;  //转化为右下角像素点坐标y1

   
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x56);
    
    temp_x0=x0/256;
    uartsendbyte(&huart5,temp_x0);//
    temp_x0=x0%256;//
    uartsendbyte(&huart5,temp_x0);//send x0
    
    temp_y0=y0/256;
    uartsendbyte(&huart5,temp_y0);//
    temp_y0=y0%256;//
    uartsendbyte(&huart5,temp_y0);//send y0
    
    temp_x1=x1/256;
    uartsendbyte(&huart5,temp_x1);//
    temp_x1=x1%256;//
    uartsendbyte(&huart5,temp_x1);//send x1
    
    temp_y1=y1/256;
    uartsendbyte(&huart5,temp_y1);//
    temp_y1=y1%256;//
    uartsendbyte(&huart5,temp_y1);//send y1

    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
    delay_us(15);
     
}




//设置矩形框。 parajx 设置参数，显示还是填充矩形区域。 给定左上角和右下角的坐标。（x0 y0）  (x1 y1) 像素点 1024*768
void disp_juxing_dot(int parajx,int x0,int y0,int x1,int y1)
{
   
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,parajx);
  
    uartsendbyte(&huart5,x0/256);//
    uartsendbyte(&huart5,x0%256);//send x0
   
    uartsendbyte(&huart5,y0/256);//
    uartsendbyte(&huart5,y0%256);//send y0
   
    uartsendbyte(&huart5,x1/256);//
    uartsendbyte(&huart5,x1%256);//send x1

    uartsendbyte(&huart5,y1/256);//
    uartsendbyte(&huart5,y1%256);//send y1

    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
    delay_us(15);
     
}

//设置矩形框。 parajx 设置参数，显示还是填充矩形区域。 起始的行列坐标和所占行数列数。num_x0  num_y0   num_row 占多少行  num_column 占多少列  行列方式 80列 25行 字体 12*24
void disp_juxing_row(int parajx,int num_x0,int num_y0,int num_row,int num_column)
{
    int temp_x0,temp_y0,temp_x1,temp_y1; 
    temp_x0=INIT_X0+20+(num_y0-1)*12;   //转化为左上角像素点坐标x0
    temp_y0=INIT_Y0+9+(num_x0-1)*24;   //转化为左上角像素点坐标y0
    temp_x1=temp_x0+(num_column*12);  //转化为右下角像素点坐标x1
    temp_y1=temp_y0+(num_row*24);  //转化为右下角像素点坐标y1
       
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,parajx);
    
    //temp_x0/=256;
    uartsendbyte(&huart5,temp_x0/256);//
    //temp_x0%=256;//
    uartsendbyte(&huart5,temp_x0%256);//send x0
    
    //temp_y0/=256;
    uartsendbyte(&huart5,temp_y0/256);//
   // temp_y0%=256;//
    uartsendbyte(&huart5,temp_y0%256);//send y0
    
    //temp_x1/=256;
    uartsendbyte(&huart5,temp_x1/256);//
    //temp_x1%=256;//
    uartsendbyte(&huart5,temp_x1%256);//send x1
    
    //temp_y1/=256;
    uartsendbyte(&huart5,temp_y1/256);//
    //temp_y1%=256;//
    uartsendbyte(&huart5,temp_y1%256);//send y1

    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
    delay_us(15);
     
}



//显示字母。 给定左上角和右下角的坐标。（x0 y0） 开始显示字符串 像素点 1024*768
void disp_zimu_dot(int x0,int y0,unsigned char *string,unsigned char length)
{

    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x98);
    uartsendbyte(&huart5,x0/256);//
    uartsendbyte(&huart5,x0%256);//send x0
    uartsendbyte(&huart5,y0/256);//
    uartsendbyte(&huart5,y0%256);//send y0
    uartsendbyte(&huart5,0x00);  // 字库位置
    uartsendbyte(&huart5,0xC1);  // 显示模式   
    uartsendbyte(&huart5,0x02);  // 字符大小  12*24 
    uartsendbyte(&huart5,0xFF);//设置前景色 黄色FF 82
    uartsendbyte(&huart5,0x82);//
    uartsendbyte(&huart5,0x00); //设置背景色 黑色 00 00
    uartsendbyte(&huart5,0x00);// 
//    uartsendstr(string,length);
	  HAL_UART_Transmit_IT(&huart5, string, length);
    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
    delay_us(15);
     
}

//显示字母。 给定左上角和右下角的坐标。（num_x0 num_y0） 开始显示字符串 行列形式显示字符串
void disp_zimu_row(int num_x0,int num_y0, char *string,unsigned char length)
{
    int temp_x0,temp_y0; 
    temp_x0=INIT_X0+20+(num_y0-1)*12;   //转化为左上角像素点坐标x0
    temp_y0=INIT_Y0+9+(num_x0-1)*24;   //转化为左上角像素点坐标y0
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x98);
    uartsendbyte(&huart5,temp_x0/256);//
    uartsendbyte(&huart5,temp_x0%256);//send num_x0
    uartsendbyte(&huart5,temp_y0/256);//
    uartsendbyte(&huart5,temp_y0%256);//send num_y0
    uartsendbyte(&huart5,0x00);  // 字库位置
    uartsendbyte(&huart5,0xC1);  // 显示模式  1100  0001 
    uartsendbyte(&huart5,0x02);  // 字符大小  12*24 
    
    uartsendbyte(&huart5,0xFF);//设置前景色 黄色FF 82
    uartsendbyte(&huart5,0x82);//
    uartsendbyte(&huart5,0x00);
    uartsendbyte(&huart5,0x00); //设置背景色 黑色 00 00
    HAL_UART_Transmit_IT(&huart5, string, length);
//    uartsendstr(string,length);
    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
     delay_us(15);
     
}


//显示框中字母。 给定左上角和右下角的坐标。（num_x0 num_y0） 开始显示字符串 行列形式显示字符串
void disp_zimu_rowk(int num_x0,int num_y0,unsigned char *string,unsigned char length)
{
    int temp_x0,temp_y0; 
    temp_x0=INIT_X0+20+(num_y0-1)*12;   //转化为左上角像素点坐标x0
    temp_y0=INIT_Y0+9+(num_x0-1)*24;   //转化为左上角像素点坐标y0
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x98);
    uartsendbyte(&huart5,temp_x0/256);//
    uartsendbyte(&huart5,temp_x0%256);//send num_x0
    uartsendbyte(&huart5,temp_y0/256);//
    uartsendbyte(&huart5,temp_y0%256);//send num_y0
    uartsendbyte(&huart5,0x00);  // 字库位置
    uartsendbyte(&huart5,0xC1);  // 显示模式  1100  0001 
    uartsendbyte(&huart5,0x02);  // 字符大小  12*24 
    uartsendbyte(&huart5,0x00); //设置前景色 黄色FF 82
    
    uartsendbyte(&huart5,0x00);//
    uartsendbyte(&huart5,0x07);
    uartsendbyte(&huart5,0xff); //设置背景色 黑色 00 00
    
    //uartsendbyte(&huart5,0xFF);//设置前景色 黄色FF 82
   // uartsendbyte(&huart5,0x82);//
//    uartsendstr(string,length);
		HAL_UART_Transmit_IT(&huart5, string, length);
    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
     delay_us(15);
     
}




//显示字母。前景与背景颜色反转  给定左上角和右下角的坐标。（num_x0 num_y0） 开始显示字符串 行列形式显示字符串
void disp_zimu_toggle(int num_x0,int num_y0,unsigned char *string,unsigned char length)
{
    int temp_x0,temp_y0; 
    temp_x0=INIT_X0+20+(num_y0-1)*12;   //转化为左上角像素点坐标x0
    temp_y0=INIT_Y0+9+(num_x0-1)*24;   //转化为左上角像素点坐标y0
    uartsendbyte(&huart5,0xAA);
    uartsendbyte(&huart5,0x98);
    uartsendbyte(&huart5,temp_x0/256);//
    uartsendbyte(&huart5,temp_x0%256);//send num_x0
    uartsendbyte(&huart5,temp_y0/256);//
    uartsendbyte(&huart5,temp_y0%256);//send num_y0
    uartsendbyte(&huart5,0x00);  // 字库位置
    uartsendbyte(&huart5,0xC1);  // 显示模式  1100  0001 
    uartsendbyte(&huart5,0x02);  // 字符大小  12*24 
    
    uartsendbyte(&huart5,0x00);
    uartsendbyte(&huart5,0x00);//设置背景色 黑色 00 00
    uartsendbyte(&huart5,0xFF);//设置前景色 黄色FF 82
    
    uartsendbyte(&huart5,0x82);//
    //uartsendbyte(&huart5,0xFF);//设置前景色 黄色FF 82
   // uartsendbyte(&huart5,0x82);//
	HAL_UART_Transmit_IT(&huart5, string, length);
//    uartsendstr(string,length);
    uartsendbyte(&huart5,0xCC);
    uartsendbyte(&huart5,0x33);
    uartsendbyte(&huart5,0xC3);
    uartsendbyte(&huart5,0x3C);
    delay_us(15);
     
}



