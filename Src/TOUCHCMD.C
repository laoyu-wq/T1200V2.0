#include  <main.h>
#include  <dgus.h>
#include  <touchcmd.h>
#include  "usart.h"
#include  "string.h"

#define chartadress  0x0100
extern uint8_t touch_xh,touch_xl,touch_yh,touch_yl,touch_row,touch_lie;
extern uint16_t touch_x,touch_y;
extern uint8_t  UART5Buffer[BUFSIZE],UART1Buffer[BUFSIZE];
extern uint32_t UART5Count,UART1Count;
int Password;//regnum为表格信息数量
extern int returnvalue_down,returnvalue_up;
/*
int touch(void)
{
  int i=0;
  if( UART5Count >8)
  {
    
    
    for( i = 0; i < UART5Count; i++ )
    {
      if(( UART5Buffer[i] == 0xAA )&&( UART5Buffer[i+1] == 0x73))//按压时
      {
        returnvalue_down=1;
        touch_xh=UART5Buffer[i+2];
        touch_xl=UART5Buffer[i+3];
        touch_yh=UART5Buffer[i+4];
        touch_yl=UART5Buffer[i+5];
        touch_x=touch_xh*256+touch_xl;
        touch_y=touch_yh*256+touch_yl;
        touch_lie=(touch_x-34)/12+1;
        touch_row=(touch_y-62)/24+1;
        
      
      }
      
      if(( UART5Buffer[i] == 0xAA )&&( UART5Buffer[i+1] == 0x72))//抬起时
      {
        returnvalue_up=1; 
        touch_xh=UART5Buffer[i+2];
        touch_xl=UART5Buffer[i+3];
        touch_yh=UART5Buffer[i+4];
        touch_yl=UART5Buffer[i+5];
        touch_x=touch_xh*256+touch_xl+1;
        touch_y=touch_yh*256+touch_yl+1;
        touch_lie=(touch_x-34)/12;
        touch_row=(touch_y-62)/24;
        
      
      }
         
    }
    UART5Count = 0;
  }
  //return returnvalue;
}

*/
int touch(void)
{
  int i=0;
  int returnvalue=0;
  if ( UART5Buffer[0] != 0xAA )
  {
    UART5Count = 0;
  }
  else if( UART5Count > 8 )
  {
    if( UART5Buffer[1] == 0x73 )//按下时
    {
        
        returnvalue_down=1;
        touch_xh=UART5Buffer[i+2];
        touch_xl=UART5Buffer[i+3];
        touch_yh=UART5Buffer[i+4];
        touch_yl=UART5Buffer[i+5];
        touch_x=touch_xh*256+touch_xl;  //像素点
        touch_y=touch_yh*256+touch_yl;
        touch_lie=(touch_x-34)/12+1;    //行列
        touch_row=(touch_y-62)/24+1;
        UART5Count = 0;
        UART5Buffer[0] = 0;
       
      
        
      
    }
    /*
    else if(UART5Buffer[1] == 0x72)  //抬起时
    {
        
        returnvalue_up=1;
        touch_xh=UART5Buffer[i+2];
        touch_xl=UART5Buffer[i+3];
        touch_yh=UART5Buffer[i+4];
        touch_yl=UART5Buffer[i+5];
        touch_x=touch_xh*256+touch_xl+1;
        touch_y=touch_yh*256+touch_yl+1;
        touch_lie=(touch_x-34)/12;
        touch_row=(touch_y-62)/24;
        UART5Count = 0;
        UART5Buffer[0] = 0;
       
       
    
    }*/
    else
    {
      UART5Count = 0;
      UART5Buffer[0] = 0;
      returnvalue_down=0;
       touch_xh=0;
       touch_xl=0;
       touch_row=0;
       touch_lie=0;
        
    }
  }
  return returnvalue;
  
}
