#ifndef __DGUS_H__
#define __DGUS_H__

//640*400  8*16 80*25
//迪文屏 1024*768   12*24
 
//宽   1006
//高   619
//字体 12*24
//14
//53
//1019
//671

//0点位置



/*------------ 矩形外框坐标定义------------*/  
#define INIT_X0    10        //  液晶屏外框 左上角X0 位置。(14,53)起始点位置 
#define INIT_Y0    53        //  液晶屏外框 左上角Y0 位置。 
#define INIT_X1    1019       //  液晶屏外框 右下角X0 位置。（1019，671）终点位置
#define INIT_Y1    675       //  液晶屏外框 右下角Y0 位置。 

//用于文本框显示
/*
#define chart0 0x0100
#define chart1 0x0200
#define chart2 0x0300
#define chart3 0x0400
#define chart4 0x0500
*/

/************发送帧头AACC********************/
void head(void);
/************指定地址发送文字********************
显示区域(20,40)to(628,440)
chart：chart1 -- chart5   5个显示文本框
row：0-4，num：0-78 为偶数
************************************************/
void sendstring(int chart,int row,int num,unsigned char *sendstr);
void set_DWIN_touch(void);
void set_DWIN_display(void);
void set_light(int V_ON,int V_OFF,int V_TIME);
void set_colour_back(void);
void clear_DWIN(void);
void set_light_on(int L_on);
void disp_line(int x0,int y0,int x1,int y1);
void disp_juxing_dot(int parajx,int x0,int y0,int x1,int y1);
void disp_juxing_row(int parajx,int num_x0,int num_y0,int num_row,int num_column);
void disp_zimu_dot(int x0,int y0,unsigned char *string,unsigned char length);
void disp_zimu_row(int num_x0,int num_y0, char *string,unsigned char length);
//void uartsendbyte(char bytedata);
//void uartsendstr(unsigned char *str,unsigned char length);
//void uart3sendbyte(char bytedata);
//void uart1sendbyte(char bytedata);
void disp_line_PX(int row,int lie0,int lie1);
void disp_zimu_toggle(int num_x0,int num_y0,unsigned char *string,unsigned char length);
void disp_zimu_rowk(int num_x0,int num_y0,unsigned char *string,unsigned char length);

//void disp_zimu(int x0,int y0,unsigned char *string);
#endif

