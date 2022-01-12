/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/*------------ ���ο����ö���------------*/
#define DISPJX_FRONT    0X59  //  59 ��ǰ��ɫ��ʾ���ο� 
#define DISPJX_BACK     0X69  //  69 �Ա���ɫ��ʾ���ο�
#define FILLJX_FRONT    0X5B  //  5B ��ǰ��ɫ�����ο�
#define FILLJX_BACK     0X5A  //  5A �Ա���ɫ�����ο�




/*-------------------- ȫ�ֱ������� -------------------*/
int returnvalue_down,returnvalue_up;
uint16_t touch_xh,touch_xl,touch_yh,touch_yl,touch_row,touch_lie;
uint16_t touch_x,touch_y;
uint32_t msTicks,page_count=0,page[100][50];
unsigned char m,n,comp[50],Eng_S,Bin_S,Hex_S;
uint16_t i,j,TEMP_LOC,FINAL_20,iStart,iEnd,Touch_Flag;
uint8_t width_kuang,high_kuang,high_kuang_wenzi,high_total;

uint16_t POS_3B,POS_48,POS_08,POS_6D;
uint16_t UART1_RCV_FLAG=0;//����3�������ݱ�־λ��
uint16_t UART5_RCV_FLAG=0;
uint16_t Line_Bottom_row;
uint16_t Line_Bottom_x;
uint16_t Line_Bottom_y;
uint16_t RCVDATA_x[2];//�������ݵ�X����洢 2λ
uint16_t RCVDATA_y[2];//�������ݵ�Y����洢 2λ
uint16_t DISPDATA_x;//�������ݵ�X����洢 1λ
uint16_t DISPDATA_y;//�������ݵ�Y����洢 1λ
uint16_t DISPDATA_row;//�������ݿ������
uint16_t Wenzi_count;
uint16_t DISPDATA_column;//�������ݿ������
uint16_t ROW_count;//�������ݿ���м��� ���յ�6D 0B 08 ����ռ��һ�С�
char TouchData=0,TouchBuf=0;
unsigned char RCVDATA_zimu[64];//�������ݵ���ĸ�洢

uint16_t ROW_flag=0;//�������ݿ�Ŀ�ʼ��־λ��

uint16_t blockNum = 0;  //һ֡���ݰ�������ô����ָ��
uint16_t blockIndex[1000][2] = {0}; //��¼��ָ�����ʼλ��
char blockBuf[4096];  //��UART3Buf�Ŀ�����Ϣת����blockBuf
uint32_t bufLength;

// ��¼�ϴδ���ʱ��

uint32_t nLastComTime = 0;
char flagComStart = 0;
/*------------------------*/
extern uint32_t UART1Count;
extern uint8_t UART1TransBuffer[64];
extern uint8_t UART1Buffer[4096];
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
////*********���ڽ������ݱ���������������������������
uint8_t aRxBuffer1;		// �������մ���1���͵��ַ�
uint8_t aRxBuffer5;		// �������մ���5���͵��ַ�
//uint8_t str1[24];//�ַ���
//uint8_t str5[24];//�ַ���
//uint32_t cnt1=0;//������1
//uint32_t cnt5=0;//������5

volatile uint32_t UART5Status, UART1Status;
volatile uint8_t UART5TxEmpty = 1, UART1TxEmpty = 1;
uint8_t  UART5Buffer[BUFSIZE], UART1Buffer[4096];
uint32_t UART5Count = 0, UART1Count = 0;
extern uint16_t UART1_RCV_FLAG;
extern uint16_t UART5_RCV_FLAG;

extern uint32_t nLastComTime;
extern char flagComStart;
extern uint32_t msTicks;
/* USER CODE END PV */
/*------------------------�Ӻ�������--------------------*/
void clear_3buffer(void);
void send_3buffer(void);
void clear_RCVDATA(void);
//void delay_us( int num );
void CtrlWrd_Monitor( void );
void Display_Monitor( void );
void touch_recognize(void);
void JianPan(void);
void JianPan_Sm(void);
void Key_Enter(char command);

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
	
	HAL_UART_Receive_IT(&huart1,(uint8_t *)&aRxBuffer1,1);			// Enable the USART1 Interrupt
	HAL_UART_Receive_IT(&huart5,(uint8_t *)&aRxBuffer5,1);			// Enable the UART5 Interrupt

  /* USER CODE BEGIN 2 */
// if(SysTick_Config(88473))
//  {
//    while(1);
//  }
//  
//  
//  set_DWIN_touch();
//  delay_us(550);
//  set_colour_back();
//  clear_DWIN();
//  //JianPan();
//  set_light_on(0x15); // set background light
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  while (1)
  {
    /* USER CODE END WHILE */
		

		if ( flagComStart == 1 )  //��ʶCom��ʼ��������
    {
      if ( (msTicks - nLastComTime)>10 )  //
      {
        CtrlWrd_Monitor();
        flagComStart = 0;
      }
    }
    Display_Monitor();

	
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable 
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_UART5;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UNUSED(huart);
	if(huart->Instance == USART1)	// �ж������ĸ����ڴ������ж�
	{
				//		HAL_UART_Transmit(&huart1,aRxBuffer1,1,100);	// ���յ���������ʹ�ô���1���ͳ�ȥ
						
//				HAL_UART_Transmit(&huart1, UART1Buffer, sizeof(UART1Buffer),0xffff);
				//		str1[cnt1++] = aRxBuffer1[0];
				//		if(cnt1==24)
				//		{
				//			cnt1=0;
				//		}
				
				if ( UART1Count >= 4096 )
				{
					UART1Count = 0;		/* buffer overflow */
				}
				else 
				{
					UART1Buffer[UART1Count] = aRxBuffer1;
					UART1Count++;
					UART1_RCV_FLAG=1;   //��������ʱ����־λ��1
					flagComStart = 1;
					nLastComTime = msTicks;
				}
				HAL_UART_Receive_IT(&huart1,(uint8_t *)&aRxBuffer1,1);		// ����ʹ�ܴ���1�����ж�
				
	}
	if(huart->Instance == UART5)
	{
		//		HAL_UART_Transmit(&huart5,aRxBuffer5,1,100);	// ���յ���������ʹ�ô���1���ͳ�ȥ
				
		//		str5[cnt5++] = aRxBuffer5[0];
		//		if(cnt5==24)
		//		{
		//			cnt5=0;
		//		}
				
				if ( UART5Count >= BUFSIZE )
					{
						UART5Count = 0;		/* buffer overflow */
					}
					else
					{
						UART5Buffer[UART5Count] = aRxBuffer5;
						UART5Count++;
					}
					HAL_UART_Receive_IT(&huart5,(uint8_t *)&aRxBuffer5,1);		// ����ʹ�ܴ���5�����ж�
	}
}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance == TIM3)		// �ж������ĸ���ʱ���������ж�
//	{
//		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_8);
//	}

//}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
/*------------------------�Ӻ������������3���棬��0��UART1Count֮����������---------------------*/
void clear_3buffer(void)
{
  for(int temp_3count=0;temp_3count<UART1Count;temp_3count++)
    UART1Buffer[temp_3count]=0;
    UART1Count=0;
}

///*------------------------�Ӻ�����ͨ������1���ʹ���3���ջ��棬��0��UART1Count֮������ݷ���---------------------*/
//void send_3buffer(void)
//{
//  for(int temp_3count=0;temp_3count<UART1Count;temp_3count++)
//    uart1sendbyte(UART1Buffer[temp_3count]);
//}

///*------------------------�Ӻ���������3�жϳ���---------------------*/
//void clear_RCVDATA(void)
//{
//  for(j=0;j<64;j++)
//  RCVDATA_zimu[j]=0;
//  POS_3B=0;
//  POS_48=0;
//  RCVDATA_x[0]=0;
//  RCVDATA_x[1]=0;
//  RCVDATA_y[0]=0;
//  RCVDATA_y[1]=0;
//}

/*------------------------�Ӻ�������ʱ---------------------*/
void delay_us( int num )
{
  uint32_t i,j;
   for(i = 0; i < num; i++)
    for(j = 0; j < 50000; j++);
}

/*------------------------ �Ӻ��������������� ������Ļ�ײ�������� ---------------------*/

void CtrlWrd_Monitor( void )
{
  blockNum = 0;
  bufLength = UART1Count;
  UART1Count=0;
  //uint16_t blockNum = 0;  //һ֡���ݰ�������ô����ָ��
  //uint16_t blockIndex[300][2] = {0}; //��¼��ָ�����ʼλ��
  //                        [0]����ʼλ�ã�
  //                        [1]��ָ���
  //char blockBuf[2048];
  //ָ�����ʼλ�á����ȡ�������->blockIndex[x][0..1]��blockNum
  //ת�洮����Ϣ�� blockBuf[]��
  for( i=0; i<bufLength; i++ )//�����ݴ��뻺��֮��
  {
    blockBuf[i] = UART1Buffer[i];
    if ( (UART1Buffer[i]==0x1B)&&(UART1Buffer[i+1]==0x5B) ) //ʶ��ͷ
    {
      blockIndex[blockNum++][0] = i;  //��i��ָ�����ʼλ��,1B��λ�� 
    }
    
  }
  //1B 5B���ص�ָ����з�������
    for(i=1;i<blockNum;i++)
    blockIndex[i-1][1]=blockIndex[i][0]-blockIndex[i-1][0];
    if(blockNum>1)
    blockIndex[blockNum-1][1]=bufLength-blockIndex[blockNum-2][0]-blockIndex[blockNum-2][1];
    else if(blockNum==1)
    blockIndex[0][1]=bufLength;
  /*****************************************************/
    
    for( i=0; i<blockNum; i++ ) //��������ָ��
    {
      iStart = blockIndex[i][0]+2;  //��ȥ 1b 5b������ֽڿ�ʼ��
      iEnd = blockIndex[i][0]+blockIndex[i][1];//���һ���ֽ�λ��
      
      for( j=iStart; j<iEnd; j++ )
      {
        
        
        
     ////////////////////////////�ж�ҳ��/////////////////////////////////
    if((blockBuf[j]=='J')&&(blockBuf[j+1]=='c')
        &&(blockBuf[j+2]=='A')&&(blockBuf[j+3]=='I')&&(blockBuf[j+4]=='R'))
     page_count=0;
      else if((blockBuf[j]=='S')&&(blockBuf[j+1]=='E')
              &&(blockBuf[j+2]=='L')&&(blockBuf[j+3]=='E')
                &&(blockBuf[j+4]=='C')&&(blockBuf[j+5]=='T')
                  &&(blockBuf[j+7]=='M')&&(blockBuf[j+8]=='E')
                    &&(blockBuf[j+9]=='N')&&(blockBuf[j+10]=='U'))
     page_count=1;
      else if((blockBuf[j]=='C')&&(blockBuf[j+1]=='O')
              &&(blockBuf[j+2]=='N')&&(blockBuf[j+3]=='F')
                &&(blockBuf[j+4]=='I')&&(blockBuf[j+5]=='G')
                  &&(blockBuf[j+6]=='U')&&(blockBuf[j+7]=='R')
                    &&(blockBuf[j+8]=='E')&&(blockBuf[j+10]=='C')
                      &&(blockBuf[j+11]=='H')&&(blockBuf[j+12]=='A')
                        &&(blockBuf[j+13]=='N')&&(blockBuf[j+14]=='N')
                          &&(blockBuf[j+15]=='E')&&(blockBuf[j+16]=='L')
                            &&(blockBuf[j+17]=='S'))
     page_count=2;
     
    else if((blockBuf[j]==0x37)&&(blockBuf[j+1]==0x6d)
              &&(blockBuf[j+2]==0)&&(blockBuf[j+3]==0x20)
                &&(blockBuf[j+4]==0x4d)&&(blockBuf[j+5]==0x4f)
                  &&(blockBuf[j+6]==0x52)&&(blockBuf[j+7]==0x45)
                    &&(blockBuf[j+8]==0x1b)&&(blockBuf[j+9]==0x5b))//MORE WORDS
     page_count=3;
    
    else if((blockBuf[j]==0x6D)&&(blockBuf[j+1]==0x20)
              &&(blockBuf[j+2]==0X45)&&(blockBuf[j+3]==0x4E)
                &&(blockBuf[j+4]==0x54)&&(blockBuf[j+5]==0x45)
                  &&(blockBuf[j+6]==0x52)&&(blockBuf[j+7]==0x20)
                    &&(blockBuf[j+8]==0x4C)&&(blockBuf[j+9]==0x41)
                      &&(blockBuf[j+10]==0x42)&&(blockBuf[j+11]==0x45)
                        &&(blockBuf[j+12]==0x4C)&&(blockBuf[j+13]==0x20)
                      )//ENTER LABEL
     page_count=4;
       
   //*******************************************************************//   
        ///////////////�����������/////////////////////////////
      if((blockBuf[j]==0x3b&&blockBuf[j+3]==0x48&&blockBuf[j+4]==0x00)
           ||(blockBuf[j]==0x3b&&blockBuf[j+2]==0x48&&blockBuf[j+3]==0x00))
        {
            for(TEMP_LOC=j;TEMP_LOC<iEnd;TEMP_LOC++) //-----------------------ɨ������ͷ��3B ��48\00��λ��-------------------//
            {
              if(blockBuf[TEMP_LOC]==0x3B) 
              {
                POS_3B=TEMP_LOC; 
                
              }
              else if(blockBuf[TEMP_LOC]==0x48) 
              {
                POS_48=TEMP_LOC;
                break;
              }
              
            }
      
        
      if((blockBuf[POS_3B-1]>0x2f&&blockBuf[POS_3B-1]<0x3a)
         &&(blockBuf[POS_3B-2]<0x2f||blockBuf[POS_3B-2]>0x3a))//0x3bǰ��һ����Чλ
      {
          RCVDATA_x[1]=blockBuf[POS_3B-1]-0X30;//һλ
          DISPDATA_x=RCVDATA_x[1];  
      
      } 
      else if ((blockBuf[POS_3B-1]>0x2f&&blockBuf[POS_3B-1]<0x3a)
               &&(blockBuf[POS_3B-2]>0x2f&&blockBuf[POS_3B-2]<0x3a))//0x3bǰ��������Чλ
      {
          RCVDATA_x[0]=blockBuf[POS_3B-2]-0X30;//�� ת��Ϊ10����
          RCVDATA_x[1]=blockBuf[POS_3B-1]-0X30;//��
          DISPDATA_x=RCVDATA_x[1]+RCVDATA_x[0]*10; 
      }  
      
      if((blockBuf[POS_48-1]>0x2f&&blockBuf[POS_48-1]<0x3a)
         &&(blockBuf[POS_48-2]<0x2f||blockBuf[POS_48-2]>0x3a))//0x48ǰ��һ����Чλ
      {
          RCVDATA_y[1]=blockBuf[POS_48-1]-0X30;//һλ
          DISPDATA_y=RCVDATA_y[1];    
      
      } 
      else if((blockBuf[POS_48-1]>0x2f&&blockBuf[POS_48-1]<0x3a)
              &&(blockBuf[POS_48-2]>0x29&&blockBuf[POS_48-2]<0x3a))//0x48ǰ��������Чλ
      {
          RCVDATA_y[0]=blockBuf[POS_48-2]-0X30;//�� ת��Ϊ10����
          RCVDATA_y[1]=blockBuf[POS_48-1]-0X30;//��
          DISPDATA_y=RCVDATA_y[1]+RCVDATA_y[0]*10;
      } 
      
      
      }
      if(blockBuf[j]==0x43)//�ҵ���Ŀ��
      {
        if(((blockBuf[j-1]>0x2f)&&(blockBuf[j-1]<0x3a))
           &&((blockBuf[j-2]<0x2f)||(blockBuf[j-2]>0x3a))) //0x43 ǰһ���ֽ�Ϊ��Ч���
         width_kuang=blockBuf[j-1]-0x30;
        else if(((blockBuf[j-1]>0x2f)&&(blockBuf[j-1]<0x3a))
                &&((blockBuf[j-2]>0x2f)&&(blockBuf[j-2]<0x3a))) //0x43 ǰ�����ֽ�Ϊ��Ч���
         width_kuang=(blockBuf[j-1]-0x30)+(blockBuf[j-2]-0x30)*10;
      
      
      }
      if((blockBuf[j]==0x6d)&&(blockBuf[j+1]==0x0b)&&(blockBuf[j+2]==0x08))//�ҵ���ĸ߶�
      {
        high_kuang++;//�����ϱ���ռ����
      }
      
        
        //���е�һ������
      //if((blockBuf[j]==0x37)&&(blockBuf[j+1]==0x6d)&&(blockBuf[j+2]==0x00))//--���е�һ������-(ON��������)-----------//)
     if((blockBuf[j]==0x6d)&&(blockBuf[j+1]==0x00)&&(blockBuf[j+2]==0x0b)||
        (blockBuf[j]==0x6d)&&(blockBuf[j+1]==0x00)&&(blockBuf[j+2]==0x20))//--���е�һ������-(ON��������)-----------//)
      {
        
        for(TEMP_LOC=j+2;TEMP_LOC<iEnd;TEMP_LOC++)
         {
            if(blockBuf[TEMP_LOC]==0x20)
            {
             FINAL_20=TEMP_LOC;   //�ҳ�0x20���ַ����е�λ��
             break;
            }
           
         }
        if(width_kuang>15)
        {
       disp_zimu_row(DISPDATA_x+1,DISPDATA_y+1,(blockBuf+FINAL_20),(iEnd-FINAL_20));//�����ַ���ʼ�볤�Ƚ�����ʾ
       
        }
        else
        {
       disp_zimu_row(DISPDATA_x,DISPDATA_y+1,(blockBuf+FINAL_20),(iEnd-FINAL_20));
        }
        
       
      }
      //���зǵ�һ��������ʾ
       else if((blockBuf[j]==0x44)&&(blockBuf[j+1]==0x0b)&&(blockBuf[j+2]==0x00)&&(blockBuf[j+3]==0x20))
        {
          high_kuang_wenzi++;
        for(TEMP_LOC=j+3;TEMP_LOC<iEnd;TEMP_LOC++)
         {
            if(blockBuf[TEMP_LOC]==0x20)
            {
             FINAL_20=TEMP_LOC; 
             break;
            }
              
         }
        if(width_kuang>15)  
       disp_zimu_row(DISPDATA_x+high_kuang_wenzi+1,DISPDATA_y+1,(blockBuf+FINAL_20),(iEnd-FINAL_20));
        else 
       disp_zimu_row(DISPDATA_x+high_kuang_wenzi,DISPDATA_y+1,(blockBuf+FINAL_20),(iEnd-FINAL_20));

        }
        else if((blockBuf[j]==0x44)&&(blockBuf[j+1]==0x0b)&&(blockBuf[j+2]==0x00)&&(blockBuf[j+3]==0x00))//������ֹ��־
        {
         high_total=high_kuang+1;
         if(DISPDATA_x!=16&&DISPDATA_y!=0)
         disp_juxing_row(DISPJX_FRONT,DISPDATA_x,DISPDATA_y+1,high_total,width_kuang-1);//����
         high_total=0;
         high_kuang=0;
         high_kuang_wenzi=0;
         
        }
       
      
       ///////////////////////********************�ǿ���������ʾ**********************//
        if((blockBuf[j]==0x3b&&blockBuf[j+3]==0x48&&blockBuf[j+4]!=0x1b&&blockBuf[j+4]!=0x00)  //48�������ֽ� δ����
           ||(blockBuf[j]==0x3b&&blockBuf[j+2]==0x48&&blockBuf[j+3]!=0x1b&&blockBuf[j+3]!=0x00))
       {
         for(TEMP_LOC=j;TEMP_LOC<iEnd;TEMP_LOC++) //-----------------------ɨ������ͷ��3B ��48 ��λ��-------------------//
        {
          if(blockBuf[TEMP_LOC]==0x3B) 
          {
            POS_3B=TEMP_LOC; 
            //break;
          }
          else if(blockBuf[TEMP_LOC]==0x48) 
          {
            POS_48=TEMP_LOC;
            break;
          }
          
        }
        for(TEMP_LOC=POS_48;TEMP_LOC<iEnd;TEMP_LOC++)//:ʶ��
        {
          if((blockBuf[TEMP_LOC]==0x20)&&(blockBuf[TEMP_LOC+1]==0x08)) 
          {
             blockBuf[TEMP_LOC]=0x3a;
             blockBuf[TEMP_LOC+1]=0x00;
                       
            
           
          }
          
          
        }
      if((blockBuf[POS_3B-1]>0x2f&&blockBuf[POS_3B-1]<0x3a)
         &&(blockBuf[POS_3B-2]<0x2f||blockBuf[POS_3B-2]>0x3a))//0x3bǰ��һ����Чλ
      {
          RCVDATA_x[1]=blockBuf[POS_3B-1]-0X30;//һλ
          DISPDATA_x=RCVDATA_x[1];  
      
      } 
      else if ((blockBuf[POS_3B-1]>0x2f&&blockBuf[POS_3B-1]<0x3a)
               &&(blockBuf[POS_3B-2]>0x2f&&blockBuf[POS_3B-2]<0x3a))//0x3bǰ��������Чλ
      {
          RCVDATA_x[0]=blockBuf[POS_3B-2]-0X30;//�� ת��Ϊ10����
          RCVDATA_x[1]=blockBuf[POS_3B-1]-0X30;//��
          DISPDATA_x=RCVDATA_x[1]+RCVDATA_x[0]*10; 
      }  
      
      if((blockBuf[POS_48-1]>0x2f&&blockBuf[POS_48-1]<0x3a)
         &&(blockBuf[POS_48-2]<0x2f||blockBuf[POS_48-2]>0x3a))//0x48ǰ��һ����Чλ
      {
          RCVDATA_y[1]=blockBuf[POS_48-1]-0X30;//һλ
          DISPDATA_y=RCVDATA_y[1];    
      
      } 
      else if((blockBuf[POS_48-1]>0x2f&&blockBuf[POS_48-1]<0x3a)
              &&(blockBuf[POS_48-2]>0x2f&&blockBuf[POS_48-2]<0x3a))//0x48ǰ��������Чλ
      {
          RCVDATA_y[0]=blockBuf[POS_48-2]-0X30;//�� ת��Ϊ10����
          RCVDATA_y[1]=blockBuf[POS_48-1]-0X30;//��
          DISPDATA_y=RCVDATA_y[1]+RCVDATA_y[0]*10;
      }
         
      if(blockBuf[POS_48+1]!=0x08)  //48 ���治��08�Ļ�   ��08�Ļ�ֻ���� x yλ����Ϣ
     disp_zimu_row(DISPDATA_x,DISPDATA_y,(blockBuf+POS_48+1),(iEnd-(POS_48+1)));//�ǿ�������
   
     }
   
    /* ֻҪ48�������ֽڣ������ǲ���08������ν λ����Ϣ���Ѿ���ȡ����ش������
     �ڱ��������*/
   if((blockBuf[j-2]==0x1b)&&(blockBuf[j-1]==0x5b)&&(blockBuf[j]==0x6d)&&(blockBuf[j+1]!=0x1b)&&(blockBuf[j+1]!=0x0b))
   {
      POS_6D=j;
     disp_zimu_row(DISPDATA_x,DISPDATA_y,(blockBuf+POS_6D+1),(iEnd-(POS_6D+1)));//�ǿ�������
   
   }
   if((blockBuf[j-3]==0x2a)&&(blockBuf[j-2]==0x1b)&&(blockBuf[j-1]==0x5b)&&(blockBuf[j]==0x31)&&(blockBuf[j+1]==0x6d)&&(blockBuf[j+2]!=0x1b)
     &&(page_count==4))
  // PAGE 4ҳ��LABEL����ʾ
   {
      POS_6D=j+1;
      disp_zimu_row(DISPDATA_x,DISPDATA_y+1,(blockBuf+POS_6D+1),(iEnd-(POS_6D+1)));//�ǿ�������
   
   }
   //***********************************ON/OFF   ENG  BIN HEX����********************************/
   //0x48�������ֽڣ���ʼ����һ֡���ݽ��д���,�õ�������Ϣ
   if((blockBuf[j]==0x3b&&blockBuf[j+3]==0x48&&blockBuf[j+4]==0x1b&&blockBuf[j+5]==0x5b)
      ||(blockBuf[j]==0x3b&&blockBuf[j+2]==0x48&&blockBuf[j+3]==0x1b&&blockBuf[j+4]==0x5b))
   {
     
     for(TEMP_LOC=j;TEMP_LOC<iEnd;TEMP_LOC++) //-----------------------ɨ������ͷ��3B ��48 ��λ��-------------------//
        {
          if(blockBuf[TEMP_LOC]==0x3B) 
          {
            POS_3B=TEMP_LOC; 
            //break;
          }
          else if(blockBuf[TEMP_LOC]==0x48) 
          {
            POS_48=TEMP_LOC;
            break;
          }
          
        }
        for(TEMP_LOC=POS_48;TEMP_LOC<iEnd;TEMP_LOC++)//:ʶ��
        {
          if((blockBuf[TEMP_LOC]==0x20)&&(blockBuf[TEMP_LOC+1]==0x08)) 
          {
             blockBuf[TEMP_LOC]=0x3a;
             blockBuf[TEMP_LOC+1]=0x00;
                       
            
           
          }
          
          
        }
      if((blockBuf[POS_3B-1]>0x2f&&blockBuf[POS_3B-1]<0x3a)
         &&(blockBuf[POS_3B-2]<0x2f||blockBuf[POS_3B-2]>0x3a))//0x3bǰ��һ����Чλ
      {
          RCVDATA_x[1]=blockBuf[POS_3B-1]-0X30;//һλ
          DISPDATA_x=RCVDATA_x[1];  
      
      } 
      else if ((blockBuf[POS_3B-1]>0x2f&&blockBuf[POS_3B-1]<0x3a)
               &&(blockBuf[POS_3B-2]>0x2f&&blockBuf[POS_3B-2]<0x3a))//0x3bǰ��������Чλ
      {
          RCVDATA_x[0]=blockBuf[POS_3B-2]-0X30;//�� ת��Ϊ10����
          RCVDATA_x[1]=blockBuf[POS_3B-1]-0X30;//��
          DISPDATA_x=RCVDATA_x[1]+RCVDATA_x[0]*10; 
      }  
      
      if((blockBuf[POS_48-1]>0x2f&&blockBuf[POS_48-1]<0x3a)
         &&(blockBuf[POS_48-2]<0x2f||blockBuf[POS_48-2]>0x3a))//0x48ǰ��һ����Чλ
      {
          RCVDATA_y[1]=blockBuf[POS_48-1]-0X30;//һλ
          DISPDATA_y=RCVDATA_y[1];    
      
      } 
      else if((blockBuf[POS_48-1]>0x2f&&blockBuf[POS_48-1]<0x3a)
              &&(blockBuf[POS_48-2]>0x2f&&blockBuf[POS_48-2]<0x3a))//0x48ǰ��������Чλ
      {
          RCVDATA_y[0]=blockBuf[POS_48-2]-0X30;//�� ת��Ϊ10����
          RCVDATA_y[1]=blockBuf[POS_48-1]-0X30;//��
          DISPDATA_y=RCVDATA_y[1]+RCVDATA_y[0]*10;
      }
      /********************0X48�������ֽڣ���صĴ�������ڱ��������***********/
    
     //if()
     if(DISPDATA_x==13&&DISPDATA_y==39&&page_count==2) //ENG
     {
          Eng_S++;
         if(Eng_S==2)
        {
           Eng_S=0;
           Bin_S=0;
           Hex_S=0;
           disp_juxing_row(FILLJX_FRONT,DISPDATA_x,DISPDATA_y+1,2,5); //ENG
           disp_zimu_toggle(DISPDATA_x,DISPDATA_y+1," ENG ",100);
           
           
           disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y+7,2,5);
           disp_zimu_row(DISPDATA_x,DISPDATA_y+7," BIN ",100);
           disp_juxing_row(DISPJX_FRONT,DISPDATA_x,DISPDATA_y+7,2,5);   //BIN
           
           disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y+13,2,5);
           disp_zimu_row(DISPDATA_x,DISPDATA_y+13," HEX ",100);
           disp_juxing_row(DISPJX_FRONT,DISPDATA_x,DISPDATA_y+13,2,5);  //HEX
           
           
        }
       
     
     }
     else if(DISPDATA_x==13&&DISPDATA_y==45&&page_count==2) //BIN
     {
          Bin_S++;
         if(Bin_S==2)
        {
           Eng_S=0;
           Bin_S=0;
           Hex_S=0;
           disp_juxing_row(FILLJX_FRONT,DISPDATA_x,DISPDATA_y+1,2,5); //BIN
           disp_zimu_toggle(DISPDATA_x,DISPDATA_y+1," BIN ",100);
           
           
           disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y-5,2,5);
           disp_zimu_row(DISPDATA_x,DISPDATA_y-5," ENG ",100);
           disp_juxing_row(DISPJX_FRONT,DISPDATA_x,DISPDATA_y-5,2,5);   //ENG
          
           
           disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y+7,2,5);
           disp_zimu_row(DISPDATA_x,DISPDATA_y+7," HEX ",100);
           disp_juxing_row(DISPJX_FRONT,DISPDATA_x,DISPDATA_y+7,2,5);  //HEX
           
       
        }
       
     
     }
      else if(DISPDATA_x==13&&DISPDATA_y==51&&page_count==2) //HEX
     {
          Hex_S++;
         if(Hex_S==2)
        {
           Eng_S=0;
           Bin_S=0;
           Hex_S=0;
           disp_juxing_row(FILLJX_FRONT,DISPDATA_x,DISPDATA_y+1,2,5); //HEX
           disp_zimu_toggle(DISPDATA_x,DISPDATA_y+1," HEX ",100);
           
           
           disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y-5,2,5);
           disp_zimu_row(DISPDATA_x,DISPDATA_y-5," BIN ",100);
           disp_juxing_row(DISPJX_FRONT,DISPDATA_x,DISPDATA_y-5,2,5);   //ENG
           
           disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y-11,2,5);
           disp_zimu_row(DISPDATA_x,DISPDATA_y-11," ENG ",100);
           disp_juxing_row(DISPJX_FRONT,DISPDATA_x,DISPDATA_y-11,2,5);  //BIN
        }
       
     
     }
     
     //label  �� ��������
     
     if(blockBuf[POS_48+1]==0x1b&&blockBuf[POS_48+2]==0x5b&&blockBuf[POS_48+3]==0x37
        &&blockBuf[POS_48+4]==0x6d&&blockBuf[POS_48+5]!=0x0B&&blockBuf[POS_48+6]!=0x08)
     {
        POS_6D=POS_48+4;
        //disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y,1,(iEnd-POS_6D+2 ));
        disp_zimu_row(DISPDATA_x,DISPDATA_y,(blockBuf+POS_6D+1),(iEnd-(POS_6D+1)));
     
     }
     
   
   }
   
   if(blockBuf[j]==0x33&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x35
        &&blockBuf[j+3]==0x48&&blockBuf[j+4]==0x1b&&blockBuf[j+5]==0x5b
         &&blockBuf[j+6]==0x4b&&blockBuf[j+7]==0x1b&&blockBuf[j+8]==0x5b 
           &&blockBuf[j+9]==0x31&&blockBuf[j+10]==0x36&&blockBuf[j+11]==0x3b
             &&blockBuf[j+12]==0x30&&blockBuf[j+13]==0x48&&blockBuf[j+14]==0x00
               &&page_count==3)//���LABEL��Ϣ��һ��ָ�� 3
     {
       
       
         disp_juxing_row(FILLJX_BACK,3,5,1,75);
       
     
     }
     
     
     else if(blockBuf[j]==0x35&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x35
        &&blockBuf[j+3]==0x48&&blockBuf[j+4]==0x1b&&blockBuf[j+5]==0x5b
         &&blockBuf[j+6]==0x4b&&blockBuf[j+7]==0x1b&&blockBuf[j+8]==0x5b 
           &&blockBuf[j+9]==0x31&&blockBuf[j+10]==0x36&&blockBuf[j+11]==0x3b
             &&blockBuf[j+12]==0x30&&blockBuf[j+13]==0x48&&blockBuf[j+14]==0x00
               &&page_count==3)//���LABEL��Ϣ��һ��ָ�� 5
     {
       
       
         disp_juxing_row(FILLJX_BACK,5,5,1,75);
       
     
     }
     
    if(blockBuf[j]==0x33&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x36
        &&blockBuf[j+3]==0x35&&blockBuf[j+4]==0x48&&blockBuf[j+5]==0x1b
         &&blockBuf[j+6]==0x5b&&blockBuf[j+7]==0x37&&blockBuf[j+8]==0x6d 
          &&page_count==3)// ���RATE 3
    {
      
       disp_juxing_row(FILLJX_BACK,3,65,1,15);
       
    
    }
    else if(blockBuf[j]==0x35&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x36
        &&blockBuf[j+3]==0x35&&blockBuf[j+4]==0x48&&blockBuf[j+5]==0x1b
         &&blockBuf[j+6]==0x5b&&blockBuf[j+7]==0x37&&blockBuf[j+8]==0x6d 
          &&page_count==3)// ���RATE 5
    { 
      
       disp_juxing_row(FILLJX_BACK,5,65,1,15);
       
    
    }
    if(blockBuf[j]==0x33&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x33
        &&blockBuf[j+3]==0x36&&blockBuf[j+4]==0x48&&blockBuf[j+5]==0x1b
         &&blockBuf[j+6]==0x5b&&blockBuf[j+7]==0x37&&blockBuf[j+8]==0x6d 
          &&page_count==3)// ���SDI 3
    {
      
       disp_juxing_row(FILLJX_BACK,3,36,1,5);
    
    }
    else if(blockBuf[j]==0x35&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x33
        &&blockBuf[j+3]==0x36&&blockBuf[j+4]==0x48&&blockBuf[j+5]==0x1b
         &&blockBuf[j+6]==0x5b&&blockBuf[j+7]==0x37&&blockBuf[j+8]==0x6d 
          &&page_count==3)// ���SDI 5
    { 
      
       disp_juxing_row(FILLJX_BACK,5,36,1,5);
    
    }
    if(blockBuf[j]==0x33&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x35
        &&blockBuf[j+3]==0x34&&blockBuf[j+4]==0x48&&blockBuf[j+5]==0x1b
         &&blockBuf[j+6]==0x5b&&blockBuf[j+7]==0x37&&blockBuf[j+8]==0x6d 
          &&page_count==3)// ���SSM 3
    {
      
       disp_juxing_row(FILLJX_BACK,3,54,1,5);
    
    }
    else if(blockBuf[j]==0x35&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x35
        &&blockBuf[j+3]==0x34&&blockBuf[j+4]==0x48&&blockBuf[j+5]==0x1b
         &&blockBuf[j+6]==0x5b&&blockBuf[j+7]==0x37&&blockBuf[j+8]==0x6d 
          &&page_count==3)// ���SSM 5
    {
      
       disp_juxing_row(FILLJX_BACK,5,54,1,5);
    
    }
    if(blockBuf[j]==0x33&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x34
        &&blockBuf[j+3]>=0x31&&blockBuf[j+4]==0x48&&blockBuf[j+5]==0x1b
         &&blockBuf[j+6]==0x5b&&blockBuf[j+7]==0x37&&blockBuf[j+8]==0x6d 
          &&page_count==3)// ���PAD 3
    {
      
       disp_juxing_row(FILLJX_BACK,3,42,1,10);
    
    }
    else if(blockBuf[j]==0x35&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x34
        &&blockBuf[j+3]>=0x31&&blockBuf[j+4]==0x48&&blockBuf[j+5]==0x1b
         &&blockBuf[j+6]==0x5b&&blockBuf[j+7]==0x37&&blockBuf[j+8]==0x6d 
          &&page_count==3)// ���PAD 5
    {
      
       disp_juxing_row(FILLJX_BACK,5,42,1,10);
    
    }
    
    if((blockBuf[j]==0x33)&&(blockBuf[j+1]==0x3b)&&(blockBuf[j+2]==0x32)
        &&(blockBuf[j+3]>=0x31)&&(blockBuf[j+3]<0x3A)&&(blockBuf[j+4]==0x48)&&(blockBuf[j+5]==0x1b)
         &&(blockBuf[j+6]==0x5b)&&(blockBuf[j+7]==0x37)&&(blockBuf[j+8]==0x6d) 
          &&(page_count==3))// ���data 3
    {
      
       disp_juxing_row(FILLJX_BACK,3,22,1,iEnd-3);
    
    }
    else if((blockBuf[j]==0x35)&&(blockBuf[j+1]==0x3b)&&(blockBuf[j+2]==0x32)
        &&(blockBuf[j+3]>=0x31)&&(blockBuf[j+3]<0x3A)&&(blockBuf[j+4]==0x48)&&(blockBuf[j+5]==0x1b)
         &&(blockBuf[j+6]==0x5b)&&(blockBuf[j+7]==0x37)&&(blockBuf[j+8]==0x6d) 
          &&(page_count==3))// ���data 5
    {
      
       disp_juxing_row(FILLJX_BACK,5,22,1,iEnd-3);
    
    }
    
    
   
   //1B 5B 37 3B 34 6D 0B 08 
//1B 5B 37 3B 34 3B 31 6D 0B 08   OFF
  if(blockBuf[j]==0x34&&blockBuf[j+1]==0x6d&&blockBuf[j+2]==0x0b&&blockBuf[j+3]==0x08
     &&blockBuf[j+4]==0x1b&&blockBuf[j+5]==0x5b&&blockBuf[j+6]==0x37&&blockBuf[j+7]==0x3b
       &&blockBuf[j+8]==0x34&&blockBuf[j+9]==0x3b&&page_count==2)  
  {
         disp_juxing_row(FILLJX_FRONT,DISPDATA_x+1,DISPDATA_y+1,1,5);
         disp_zimu_toggle(DISPDATA_x+1,DISPDATA_y+1," OFF ",100);
         disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y+1,1,5);
         disp_zimu_row(DISPDATA_x,DISPDATA_y+1," ON ",100);
         disp_juxing_row(DISPJX_FRONT,DISPDATA_x,DISPDATA_y+1,1,5);
         
  
  }
   //1B 5B 37 3B 34 6D 0B 08 
//1B 5B 37 3B 34 3B 31 6D 0B 08   TX RX
 else if(blockBuf[j]==0x34&&blockBuf[j+1]==0x6d&&blockBuf[j+2]==0x0b&&blockBuf[j+3]==0x08
     &&blockBuf[j+4]==0x1b&&blockBuf[j+5]==0x5b&&blockBuf[j+6]==0x37&&blockBuf[j+7]==0x3b
       &&blockBuf[j+8]==0x34&&blockBuf[j+9]==0x3b&&DISPDATA_x==13&&DISPDATA_y==49&&page_count==3)  
  {
         disp_juxing_row(FILLJX_FRONT,DISPDATA_x+1,DISPDATA_y+1,1,6);
         disp_zimu_toggle(DISPDATA_x+1,DISPDATA_y+1,"  RX ",100);
         disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y+1,1,6);
         disp_zimu_row(DISPDATA_x,DISPDATA_y+1,"  TX ",100);
         disp_juxing_row(DISPJX_FRONT,DISPDATA_x,DISPDATA_y+1,1,6);
         
  
  }
  //INC DEC
  else if(blockBuf[j]==0x34&&blockBuf[j+1]==0x6d&&blockBuf[j+2]==0x0b&&blockBuf[j+3]==0x08
     &&blockBuf[j+4]==0x1b&&blockBuf[j+5]==0x5b&&blockBuf[j+6]==0x37&&blockBuf[j+7]==0x3b
       &&blockBuf[j+8]==0x34&&blockBuf[j+9]==0x3b&&DISPDATA_x==13&&DISPDATA_y==31&&page_count==3)  
  {
         disp_juxing_row(FILLJX_FRONT,DISPDATA_x+1,DISPDATA_y+1,1,6);
         disp_zimu_toggle(DISPDATA_x+1,DISPDATA_y+1," DECR ",100);
         disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y+1,1,6);
         disp_zimu_row(DISPDATA_x,DISPDATA_y+1," INC. ",100);
         disp_juxing_row(DISPJX_FRONT,DISPDATA_x,DISPDATA_y+1,1,6);
         
  
  }
  //1B 5B 37 3B 34 3B 31 6D 0B 08 
   //1B 5B 37 3B 34 6D 0B 08   ON
  if(blockBuf[j]==0x34&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x31&&blockBuf[j+3]==0x6d
     &&blockBuf[j+4]==0x0b&&blockBuf[j+5]==0x08&&blockBuf[j+6]==0x1b&&blockBuf[j+7]==0x5b
       &&blockBuf[j+8]==0x37&&blockBuf[j+9]==0x3b&&page_count==2)  
  {
         disp_juxing_row(FILLJX_FRONT,DISPDATA_x,DISPDATA_y+1,1,5);
         disp_zimu_toggle(DISPDATA_x,DISPDATA_y+1," ON ",100);
         disp_juxing_row(FILLJX_BACK,DISPDATA_x+1,DISPDATA_y+1,1,5);
         disp_zimu_row(DISPDATA_x+1,DISPDATA_y+1," OFF ",100);
         disp_juxing_row(DISPJX_FRONT,DISPDATA_x+1,DISPDATA_y+1,1,5);
        
         
  
  }
  //TX RX
   else if(blockBuf[j]==0x34&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x31&&blockBuf[j+3]==0x6d
     &&blockBuf[j+4]==0x0b&&blockBuf[j+5]==0x08&&blockBuf[j+6]==0x1b&&blockBuf[j+7]==0x5b
       &&blockBuf[j+8]==0x37&&blockBuf[j+9]==0x3b&&DISPDATA_x==13&&DISPDATA_y==49&&page_count==3)  
  {
         disp_juxing_row(FILLJX_FRONT,DISPDATA_x,DISPDATA_y+1,1,6);
         disp_zimu_toggle(DISPDATA_x,DISPDATA_y+1,"  TX ",100);
         disp_juxing_row(FILLJX_BACK,DISPDATA_x+1,DISPDATA_y+1,1,6);
         disp_zimu_row(DISPDATA_x+1,DISPDATA_y+1,"  RX ",100);
         disp_juxing_row(DISPJX_FRONT,DISPDATA_x+1,DISPDATA_y+1,1,6);
        
         
  
  }
  //INC DEC
   else if(blockBuf[j]==0x34&&blockBuf[j+1]==0x3b&&blockBuf[j+2]==0x31&&blockBuf[j+3]==0x6d
     &&blockBuf[j+4]==0x0b&&blockBuf[j+5]==0x08&&blockBuf[j+6]==0x1b&&blockBuf[j+7]==0x5b
       &&blockBuf[j+8]==0x37&&blockBuf[j+9]==0x3b&&DISPDATA_x==13&&DISPDATA_y==31&&page_count==3)  
  {
         disp_juxing_row(FILLJX_FRONT,DISPDATA_x,DISPDATA_y+1,1,6);
         disp_zimu_toggle(DISPDATA_x,DISPDATA_y+1," INC. ",100);
         disp_juxing_row(FILLJX_BACK,DISPDATA_x+1,DISPDATA_y+1,1,6);
         disp_zimu_row(DISPDATA_x+1,DISPDATA_y+1," DECR ",100);
         disp_juxing_row(DISPJX_FRONT,DISPDATA_x+1,DISPDATA_y+1,1,6);
        
         
  
  }
   
   
  
    
 //*******************************************************************//
     //100 12.5KPS  �ɴ��ص�λ��  3b 48 1b 5b 6d
    
      if((blockBuf[j]==0x3b&&blockBuf[j+3]==0x48&&blockBuf[j+4]==0x1b
          &&blockBuf[j+5]==0x5b&&blockBuf[j+6]==0x6d)||(blockBuf[j]==0x3b
   &&blockBuf[j+2]==0x48&&blockBuf[j+3]==0x1b&&blockBuf[j+4]==0x5b&&blockBuf[j+5]==0x6d 
    ))
        { 
          
           
            for(TEMP_LOC=j;TEMP_LOC<iEnd;TEMP_LOC++) //-----------------------ɨ������ͷ��3B ��48 ��λ��-------------------//
            {
              if(blockBuf[TEMP_LOC]==0x3B) 
              {
                POS_3B=TEMP_LOC; 
                
              }
              else if(blockBuf[TEMP_LOC]==0x48) 
              {
                POS_48=TEMP_LOC;
                break;
              }
              
            }
      
        
      if((blockBuf[POS_3B-1]>0x2f&&blockBuf[POS_3B-1]<0x3a)
         &&(blockBuf[POS_3B-2]<0x2f||blockBuf[POS_3B-2]>0x3a))//0x3ǰ��һ����Чλ
      {
          RCVDATA_x[1]=blockBuf[POS_3B-1]-0X30;//һλ
          DISPDATA_x=RCVDATA_x[1];  
      
      } 
      else if ((blockBuf[POS_3B-1]>0x2f&&blockBuf[POS_3B-1]<0x3a)
               &&(blockBuf[POS_3B-2]>0x2f&&blockBuf[POS_3B-2]<0x3a))//0x3ǰ��������Чλ
      {
          RCVDATA_x[0]=blockBuf[POS_3B-2]-0X30;//�� ת��Ϊ10����
          RCVDATA_x[1]=blockBuf[POS_3B-1]-0X30;//��
          DISPDATA_x=RCVDATA_x[1]+RCVDATA_x[0]*10; 
      }  
      
      if((blockBuf[POS_48-1]>0x2f&&blockBuf[POS_48-1]<0x3a)
         &&(blockBuf[POS_48-2]<0x2f||blockBuf[POS_48-2]>0x3a))//0x3ǰ��һ����Чλ
      {
          RCVDATA_y[1]=blockBuf[POS_48-1]-0X30;//һλ
          DISPDATA_y=RCVDATA_y[1];    
      
      } 
      else if((blockBuf[POS_48-1]>0x2f&&blockBuf[POS_48-1]< 0x3a)
              &&(blockBuf[POS_48-2]>0x29&&blockBuf[POS_48-2]<0x3a))//0x3ǰ��������Чλ
      {
          RCVDATA_y[0]=blockBuf[POS_48-2]-0X30;//�� ת��Ϊ10����
          RCVDATA_y[1]=blockBuf[POS_48-1]-0X30;//��
          DISPDATA_y=RCVDATA_y[1]+RCVDATA_y[0]*10;
      } 
      
      if((blockBuf[j+6]==0x6d)&&(blockBuf[j+7]!=0x0b))
    {
     disp_zimu_row(DISPDATA_x,DISPDATA_y,(blockBuf+j+7),(iEnd-j-7));
    } 
    else if((blockBuf[j+6]==0x6d)&&(blockBuf[j+7]==0x0b))
    {
     disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y,1,5);
      disp_juxing_row(FILLJX_BACK,DISPDATA_x+1,DISPDATA_y,1,5);
      // disp_juxing_row(FILLJX_BACK,5,5,1,75);
    }
     else if((blockBuf[j+5]==0x6d)&&(blockBuf[j+6]!=0x0b))
    {
     disp_zimu_row(DISPDATA_x,DISPDATA_y,(blockBuf+j+6),(iEnd-j-6));
    } 
    else if((blockBuf[j+5]==0x6d)&&(blockBuf[j+6]==0x0b))
    {
    
      disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y,1,5);
      disp_juxing_row(FILLJX_BACK,DISPDATA_x+1,DISPDATA_y,1,5);
      // disp_juxing_row(FILLJX_BACK,5,5,1,75);
    }   
      
    }
   
    
    /*******************����LABEL��Ϣ*****************************/
    //35  44 1b 4d 00 ��һ��
    if(blockBuf[j]==0x35&&blockBuf[j+1]==0x44&&blockBuf[j+2]==0x1b
          &&blockBuf[j+3]==0x4d&&blockBuf[j+4]==0x00&&blockBuf[j+5]!=0x0B&&blockBuf[j+5]!=0x08)
    {
       disp_zimu_row(DISPDATA_x,DISPDATA_y+1,(blockBuf+j+5),(iEnd-j-5));
  
    }
    // 35 44 1b 4d 00 0b //OFF
    else if(blockBuf[j]==0x35&&blockBuf[j+1]==0x44&&blockBuf[j+2]==0x1b
          &&blockBuf[j+3]==0x4d&&blockBuf[j+4]==0x00&&blockBuf[j+5]==0x0B)
    {
      disp_juxing_row(FILLJX_BACK,DISPDATA_x,DISPDATA_y+1,1,6);
      disp_zimu_row(DISPDATA_x,DISPDATA_y+1,(blockBuf+j+6),(iEnd-j-6));  
      disp_juxing_row(FILLJX_BACK,DISPDATA_x+1,DISPDATA_y+1,1,6);
      
    }
    
    /*******************************************************************/
     //RX  ���յ���LABEL�� 31 6d 1b 4d  00
    if((blockBuf[j]==0x31)&&(blockBuf[j+1]==0x6d)&&(blockBuf[j+2]==0x1b)&&(blockBuf[j+3]==0x4d)
       &&(blockBuf[j+4]==0x00)&&(page_count==3))
    {
       disp_zimu_row(DISPDATA_x,DISPDATA_y+1,(blockBuf+j+5),(iEnd-j-5));
   
    }
    
    //���ս����յ�1b 5b 6d 31 30 ʱ�����ʾ��Ϣ 
    if((blockBuf[j]==0x6d)&&(blockBuf[j+1]==0x31)&&(blockBuf[j+2]==0x30)&&page_count==4)
    {
    
      disp_juxing_row(FILLJX_BACK,3,5,1,75);
    
    
    }  
  //���ս����յ�1b 5b 31 6d 00ʱ�����ʾ��Ϣ
    if((blockBuf[j]==0x31)&&(blockBuf[j+1]==0x6d)&&(blockBuf[j+2]==0x00)&&page_count==4)
    {
    
      disp_juxing_row(FILLJX_BACK,3,5,1,75);
    
    
    } 
   /* else if((blockBuf[j]==0x31)&&(blockBuf[j+1]==0x6d)&&(blockBuf[j+2]==0x00)&&page_count==3)
    {
     
       disp_juxing_row(FILLJX_BACK,5,5,1,75);
    
    }
      */ 
       
       
       //����ָ��
      else  if((blockBuf[j]==0x32)&&(blockBuf[j+1]==0x4a))
       {
          clear_DWIN();//����ʱ�رգ����������´�  ���������
          disp_juxing_row(0X5A,1,0,16,80);
          //disp_line_PX(16,1,80);
          set_light_on(0x15); // set background light
          high_total=0;
          high_kuang=0;
          high_kuang_wenzi=0;
         
       
       }
      
      }
  
   } //forѭ��������   ���е�ָ�����ȫ���ⲿ���д���
      

}

void Display_Monitor( void )
{
  touch();
 if(page_count==0)
  {
    
    //11 13 17   STANDARD  MODE
  if((returnvalue_down==1)&&(touch_row>10&&touch_row<15)&&(touch_lie>12&&touch_lie<30))
  {
    disp_juxing_row(FILLJX_FRONT,11,14,4,16);
    disp_zimu_toggle(12,14,"    STANDARD  ",100);
    disp_zimu_toggle(13,14,"      MODE  ",100);
    returnvalue_down=0;
    //delay_us(100);
    Key_Enter(0xa9);
   // page_count=1;
    
  }
   // CFDS MODE
  else if((returnvalue_down==1)&&(touch_row>10&&touch_row<15)&&(touch_lie>34&&touch_lie<50))
  {
    disp_juxing_row(FILLJX_FRONT,11,34,4,16);
    disp_zimu_toggle(12,34,"      CFDS  ",100);
    disp_zimu_toggle(13,34,"      MODE  ",100);
    returnvalue_down=0;
    //delay_us(100);
    Key_Enter(0xAC);
   // page_count=1;
    
  }
  //CMC MODE
  else if((returnvalue_down==1)&&(touch_row>10&&touch_row<15)&&(touch_lie>54&&touch_lie<70))
  {
     disp_juxing_row(FILLJX_FRONT,11,54,4,16);
    disp_zimu_toggle(12,54,"      CMC  ",100);
    disp_zimu_toggle(13,54,"      MODE  ",100);
    returnvalue_down=0;
    //delay_us(100);
    Key_Enter(0xAE);
    //page_count=1;
      
    
  }
   }
 
 /***********************************��1��ҳ��******************************/
   else if(page_count==1)
   {
      //6 17 19 5  USER CONFIGURE MENU
      if((returnvalue_down==1)&&(touch_row>5&&touch_row<12)&&(touch_lie>18&&touch_lie<36))
      {
        disp_juxing_row(FILLJX_FRONT,6,18,5,18);
        disp_zimu_toggle(7,18,"       USER  ",100);
        disp_zimu_toggle(8,18,"    CONFIGURE  ",100);
        disp_zimu_toggle(9,18,"       MENU  ",100);
        returnvalue_down=0;
       // delay_us(100);
        Key_Enter(0x96);
        //page_count=2;
        
      }
      //6 47 19 5  AVIONICS LRU MENU
      if((returnvalue_down==1)&&(touch_row>5&&touch_row<12)&&(touch_lie>46&&touch_lie<66))
      {
        disp_juxing_row(FILLJX_FRONT,6,48,5,18);
        disp_zimu_toggle(7,48,"     AVIONICS  ",100);
        disp_zimu_toggle(8,48,"       LRU  ",100);
        disp_zimu_toggle(9,48,"       MENU  ",100);
        returnvalue_down=0;
        //delay_us(100);
        Key_Enter(0x9b);//
      //  page_count=11;
        
      }
    
   }
 /**********************************�ڶ���ҳ��******************************/
   else if(page_count==2)
   {
     //3 7 13 2 KPS
      if((returnvalue_down==1)&&(touch_row>2&&touch_row<6)&&(touch_lie>8&&touch_lie<22))
      {
        returnvalue_down=0;
       // delay_us(100);
        Key_Enter(0x81);
       
        
      }
      //3  23 
       if((returnvalue_down==1)&&(touch_row>2&&touch_row<6)&&(touch_lie>23&&touch_lie<37))
      {
        returnvalue_down=0;
        //delay_us(100);
        Key_Enter(0x83);
  
      }
      
       //3  39 
       if((returnvalue_down==1)&&(touch_row>2&&touch_row<6)&&(touch_lie>38&&touch_lie<52))
      {
        returnvalue_down=0;
        //delay_us(100);
        Key_Enter(0x85);
  
      }
      
      //3  55
       if((returnvalue_down==1)&&(touch_row>2&&touch_row<6)&&(touch_lie>53&&touch_lie<67))
      {
        returnvalue_down=0;
        //delay_us(100);
        Key_Enter(0x88);
  
      }
     
     //6 9 13 2 RX-A
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<13)&&(touch_lie>8&&touch_lie<22))
      {
        disp_juxing_row(FILLJX_FRONT,9,10,2,12);
        disp_zimu_toggle(9,10,"    RX-A  ",100);
        returnvalue_down=0;
        //delay_us(100);
        Key_Enter(0x9e);
       // page_count=7;
        
      }
      //6 25 13 2 RX-B
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<13)&&(touch_lie>24&&touch_lie<38))
      {
        disp_juxing_row(FILLJX_FRONT,9,26,2,12);
        disp_zimu_toggle(9,26,"    RX-B  ",100);
        returnvalue_down=0;
        //delay_us(100);
        Key_Enter(0xa1);
       // page_count=8;
        
      }
      
      //6 41 13 2 RX-C
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<13)&&(touch_lie>40&&touch_lie<54))
      {
        disp_juxing_row(FILLJX_FRONT,9,42,2,12);
        disp_zimu_toggle(9,42,"    RX-C  ",100);
        returnvalue_down=0;
       // delay_us(100);
        Key_Enter(0xa4);
       // page_count=9;
        
      }
      
      //6 57 13 2 RX-D
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<13)&&(touch_lie>56&&touch_lie<70))
      {
        disp_juxing_row(FILLJX_FRONT,9,58,2,12);
        disp_zimu_toggle(9,58,"    RX-D  ",100);
        returnvalue_down=0;
       // delay_us(100);
        Key_Enter(0xa6);
       // page_count=10;
        
      }
      
      /*****************************TX CHANNAL**************************************/
      //6 9 13 2 TX-A
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<10)&&(touch_lie>8&&touch_lie<22))
      {
        disp_juxing_row(FILLJX_FRONT,6,10,2,12);
        disp_zimu_toggle(6,10,"    TX-A  ",100);
        returnvalue_down=0;
        //delay_us(100);
        Key_Enter(0x8b);
       // page_count=3;
        
      }
      //6 25 13 2 TX-B
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<10)&&(touch_lie>24&&touch_lie<38))
      {
        disp_juxing_row(FILLJX_FRONT,6,26,2,12);
        disp_zimu_toggle(6,26,"    TX-B  ",100);
        returnvalue_down=0;
       // delay_us(100);
        Key_Enter(0x8d);
        //page_count=3;
       // 
      }
      
      //6 41 13 2 TX-C
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<10)&&(touch_lie>40&&touch_lie<54))
      {
        disp_juxing_row(FILLJX_FRONT,6,42,2,12);
        disp_zimu_toggle(6,42,"    TX-C  ",100);
        returnvalue_down=0;
        //delay_us(100);
        Key_Enter(0x8f);
        //page_count=3;
        
      }
      
      //6 57 13 2 TX-D
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<10)&&(touch_lie>56&&touch_lie<70))
      {
        disp_juxing_row(FILLJX_FRONT,6,58,2,12);
        disp_zimu_toggle(6,58,"    TX-D  ",100);
        returnvalue_down=0;
        //delay_us(100);
        Key_Enter(0x92);
       // page_count=3;
        
      }
      
       //13 9 1 6 ��һ��ON/OFF
      if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>9&&touch_lie<15))
      {
        returnvalue_down=0;
         Key_Enter(0xB2);
        
      }
       //13 15 1 6 ��ON����ON/OFF
      if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>15&&touch_lie<21))
      {
        returnvalue_down=0;
         Key_Enter(0xB3);
        
      }
       //13 21 1 6 ������ON/OFF
      if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>21&&touch_lie<27))
      {
        returnvalue_down=0;
         Key_Enter(0xB4);
        
      }
       //13 27 1 6 ���ĸ�ON/OFF
      if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>27&&touch_lie<33))
      {
        returnvalue_down=0;
         Key_Enter(0xB5);
        
      }
      
       //13 39 2 6 ENG
      if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>39&&touch_lie<45))
      {
        returnvalue_down=0;
         Key_Enter(0xB7);
        
      }
      
       //13 45 2 6 BIN
      if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>45&&touch_lie<51))
      {
        returnvalue_down=0;
        Key_Enter(0xB8);
        
      }
      //13 51 2 6 HEX
       if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>51&&touch_lie<57))
      {
        returnvalue_down=0;
         Key_Enter(0xB9);
        
      }
      
      //13 58 2 12 DISPLAY
       if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>57&&touch_lie<69))
      {
        returnvalue_down=0;
        disp_juxing_row(FILLJX_FRONT,13,59,2,11);
        disp_zimu_toggle(13,59,"  DISPLAY  ",100);
        Key_Enter(0xBA);
        
      }
   
   }
   else if(page_count==3)
   {
     //7 10 2 5
     //��һ��OFF
     if((returnvalue_down==1)&&(touch_row>6&&touch_row<9)&&(touch_lie>10&&touch_lie<16))
     {
        returnvalue_down=0;
        Key_Enter(0x94);
     
     }
     //7 16 2 5
     //�ڶ���OFF
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<9)&&(touch_lie>16&&touch_lie<22))
     {
        returnvalue_down=0;
        Key_Enter(0x95);
     
     }
     
     //7 22 2 5
     //������OFF
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<9)&&(touch_lie>22&&touch_lie<28))
     {
        returnvalue_down=0;
        Key_Enter(0x96);
     
     }
     
     //7 28 2 5
     //���ĸ�OFF
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<9)&&(touch_lie>28&&touch_lie<34))
     {
        returnvalue_down=0;
        Key_Enter(0x97);
     
     }
     //7 34 2 5
     //�����OFF
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<9)&&(touch_lie>34&&touch_lie<40))
     {
        returnvalue_down=0;
        Key_Enter(0x98);
     
     }
     //7 40 2 5
     //������OFF
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<9)&&(touch_lie>40&&touch_lie<46))
     {
        returnvalue_down=0;
        Key_Enter(0x99);
     
     }
     //7 46 2 5
     //���߸�OFF
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<9)&&(touch_lie>46&&touch_lie<52))
     {
        returnvalue_down=0;
        Key_Enter(0x9a);
     
     }
     //7 52 2 5
     //�ڰ˸�OFF
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<9)&&(touch_lie>52&&touch_lie<58))
     {
        returnvalue_down=0;
        Key_Enter(0x9b);
     
     }
     //7 58 2 5
     //�ھŸ�OFF
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<9)&&(touch_lie>58&&touch_lie<64))
     {
        returnvalue_down=0;
        Key_Enter(0x9c);
     
     }
     //7 64 2 5
     //��ʮ��OFF
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<9)&&(touch_lie>64&&touch_lie<70))
     {
        returnvalue_down=0;
        Key_Enter(0x9d);
     
     }
     
     
     //rx��һ��lab
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<12)&&(touch_lie>10&&touch_lie<16))
     {
        returnvalue_down=0;
        Key_Enter(0x9e);
     
     }
     
     //rx��2��lab
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<12)&&(touch_lie>16&&touch_lie<22))
     {
        returnvalue_down=0;
        Key_Enter(0x9f);
     
     }
     //rx��3��lab
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<12)&&(touch_lie>22&&touch_lie<28))
     {
        returnvalue_down=0;
        Key_Enter(0xa0);
     
     }
     //rx��4��lab
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<12)&&(touch_lie>28&&touch_lie<34))
     {
        returnvalue_down=0;
        Key_Enter(0xa1);
     
     }
     
     //rx��5��lab
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<12)&&(touch_lie>34&&touch_lie<40))
     {
        returnvalue_down=0;
        Key_Enter(0xa2);
     
     }
     
     //rx��6��lab
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<12)&&(touch_lie>40&&touch_lie<46))
     {
        returnvalue_down=0;
        Key_Enter(0xa3);
     
     }
     //rx��7��lab
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<12)&&(touch_lie>46&&touch_lie<52))
     {
        returnvalue_down=0;
        Key_Enter(0xa4);
     
     }
     //rx��8��lab
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<12)&&(touch_lie>52&&touch_lie<58))
     {
        returnvalue_down=0;
        Key_Enter(0xa5);
     
     }
     //rx��9��lab
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<12)&&(touch_lie>58&&touch_lie<64))
     {
        returnvalue_down=0;
        Key_Enter(0xa6);
     
     }
     //rx��10��lab
      if((returnvalue_down==1)&&(touch_row>9&&touch_row<12)&&(touch_lie>64&&touch_lie<70))
     {
        returnvalue_down=0;
        Key_Enter(0xa7);
     
     }
     
     //LABEL ����
     if((returnvalue_down==1)&&(touch_row>1&&touch_row<4)&&(touch_lie>17&&touch_lie<21))
     {
        returnvalue_down=0;
        Key_Enter(0x80);
     
     }
     //LABEL ����
     
     if((returnvalue_down==1)&&(touch_row>4&&touch_row<6)&&(touch_lie>17&&touch_lie<21))
     {
        returnvalue_down=0;
        Key_Enter(0x8A);
     
     }
     
     
     //RATE ����
      if((returnvalue_down==1)&&(touch_row>1&&touch_row<4)&&(touch_lie>65&&touch_lie<71))
     {
        returnvalue_down=0;
        Key_Enter(0x89);
     
     }
     
     //RATE ����
      if((returnvalue_down==1)&&(touch_row>4&&touch_row<6)&&(touch_lie>65&&touch_lie<71))
     {
        returnvalue_down=0;
        Key_Enter(0x93);
     
     }
     
     //PAR ����
      if((returnvalue_down==1)&&(touch_row>1&&touch_row<4)&&(touch_lie>60&&touch_lie<65))
     {
        returnvalue_down=0;
        Key_Enter(0x88);
     
     }
     
     //PAR ����
      if((returnvalue_down==1)&&(touch_row>4&&touch_row<6)&&(touch_lie>60&&touch_lie<65))
     {
        returnvalue_down=0;
        Key_Enter(0x92);
     
     }
     
     //PAD����
      if((returnvalue_down==1)&&(touch_row>1&&touch_row<4)&&(touch_lie>41&&touch_lie<52))
     {
        returnvalue_down=0;
        Key_Enter(0x85);
     
     }
     //PAD����
      if((returnvalue_down==1)&&(touch_row>4&&touch_row<6)&&(touch_lie>41&&touch_lie<52))
     {
        returnvalue_down=0;
        Key_Enter(0x8f);
     
     }
     
     //SSM����
      if((returnvalue_down==1)&&(touch_row>1&&touch_row<4)&&(touch_lie>54&&touch_lie<60))
     {
        returnvalue_down=0;
        Key_Enter(0x87);
     
     }
     //SSM����
      if((returnvalue_down==1)&&(touch_row>4&&touch_row<6)&&(touch_lie>54&&touch_lie<60))
     {
        returnvalue_down=0;
        Key_Enter(0x91);
     
     }
     
     //SDI����
      if((returnvalue_down==1)&&(touch_row>1&&touch_row<4)&&(touch_lie>35&&touch_lie<41))
     {
        returnvalue_down=0;
        Key_Enter(0x84);
     
     }
      //SDI����
      if((returnvalue_down==1)&&(touch_row>4&&touch_row<6)&&(touch_lie>35&&touch_lie<41))
     {
        returnvalue_down=0;
        Key_Enter(0x8e);
     
     }
   //DATA ����
      if((returnvalue_down==1)&&(touch_row>1&&touch_row<4)&&(touch_lie>22&&touch_lie<28))
     {
        returnvalue_down=0;
        Key_Enter(0x83);
     
     }
     //DATA ����
      if((returnvalue_down==1)&&(touch_row>4&&touch_row<6)&&(touch_lie>22&&touch_lie<28))
     {
        returnvalue_down=0;
        Key_Enter(0x8c);
     
     }
      //TX RX
      if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>49&&touch_lie<55))
     {
        returnvalue_down=0;
        Key_Enter(0xB9);
     
     }
     //LN1
      if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>55&&touch_lie<64))
     {
        returnvalue_down=0;
        Key_Enter(0xBA);
     
     }
     //LN2
      if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>64&&touch_lie<70))
     {
        returnvalue_down=0;
        Key_Enter(0xBB);
     
     }
     
     //INC DECR
      if((returnvalue_down==1)&&(touch_row>12&&touch_row<15)&&(touch_lie>31&&touch_lie<37))
     {
        returnvalue_down=0;
        Key_Enter(0xB6);
     
     }
     
     
   
   }
   else if(page_count==4)
   {
      if((returnvalue_down==1)&&(touch_row>6&&touch_row<10)&&(touch_lie>59&&touch_lie<74))
     {
        returnvalue_down=0;
        Key_Enter(0x9d);
     
     }
     
      if((returnvalue_down==1)&&(touch_row>10&&touch_row<14)&&(touch_lie>60&&touch_lie<73))
     {
        returnvalue_down=0;
        Key_Enter(0xBB);
     
     }
   
   
   
   
   
   }
  

}


void JianPan(void)
{
disp_zimu_row(18,2,"  A6  ",10);
disp_zimu_row(18,8,"  B9  ",10);
disp_zimu_row(18,14,"  82  ",10);
disp_zimu_row(18,20,"  83  ",10);
disp_zimu_row(18,26,"  84  ",10);
disp_zimu_row(18,32,"  85  ",10);
disp_zimu_row(18,38,"  86  ",10);
disp_zimu_row(18,44,"  87  ",10);
disp_zimu_row(18,50,"  88  ",10);
disp_zimu_row(18,56,"  89  ",10);
disp_zimu_row(18,62,"  8A  ",10);
disp_zimu_row(18,68,"  8B  ",10);
disp_zimu_row(18,74,"  8C  ",10);

disp_zimu_row(21,2,"  8D  ",10);
disp_zimu_row(21,8,"  8E  ",10);
disp_zimu_row(21,14,"  8F  ",10);
disp_zimu_row(21,20,"  90  ",10);
disp_zimu_row(21,26,"  91  ",10);
disp_zimu_row(21,32,"  92  ",10);
disp_zimu_row(21,38,"  93  ",10);
disp_zimu_row(21,44,"  94  ",10);
disp_zimu_row(21,50,"  95  ",10);
disp_zimu_row(21,56,"  96  ",10);
disp_zimu_row(21,62,"  97  ",10);
disp_zimu_row(21,68,"  98  ",10);
disp_zimu_row(21,74,"  99  ",10);

disp_zimu_row(24,2,"  BA  ",10);
disp_zimu_row(24,8,"  BB  ",10);
disp_zimu_row(24,14,"  9C  ",10);
disp_zimu_row(24,20,"  9D  ",10);
disp_zimu_row(24,26,"  9E  ",10);
disp_zimu_row(24,32,"  9F  ",10);
disp_zimu_row(24,38,"  B2  ",10);
disp_zimu_row(24,44,"  B3  ",10);
disp_zimu_row(24,50,"  B4  ",10);
disp_zimu_row(24,56,"  B5  ",10);
disp_zimu_row(24,62,"  B6  ",10);
disp_zimu_row(24,68,"  B7  ",10);
disp_zimu_row(24,74,"  B8  ",10);

disp_juxing_row(DISPJX_FRONT,17,2,9,78);
disp_juxing_row(DISPJX_FRONT,17,2,3,78);
disp_juxing_row(DISPJX_FRONT,17,2,6,78);
disp_juxing_row(DISPJX_FRONT,17,2,9,6);
disp_juxing_row(DISPJX_FRONT,17,2,9,12);
disp_juxing_row(DISPJX_FRONT,17,2,9,18);
disp_juxing_row(DISPJX_FRONT,17,2,9,24);
disp_juxing_row(DISPJX_FRONT,17,2,9,30);
disp_juxing_row(DISPJX_FRONT,17,2,9,36);
disp_juxing_row(DISPJX_FRONT,17,2,9,42);
disp_juxing_row(DISPJX_FRONT,17,2,9,48);
disp_juxing_row(DISPJX_FRONT,17,2,9,54);
disp_juxing_row(DISPJX_FRONT,17,2,9,60);
disp_juxing_row(DISPJX_FRONT,17,2,9,66);
disp_juxing_row(DISPJX_FRONT,17,2,9,72);



}


//�������

void JianPan_Sm(void)
{ 
  touch();
  //a0---------------------ac
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>2&&touch_lie<8))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,2,3,6);//��ǰ��ɫ���
    disp_zimu_toggle(18,2,"  A6 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,2,3,6);//�Ա���ɫ���
    disp_zimu_row(18,2,"  A6  ",100);
    disp_juxing_row(DISPJX_FRONT,17,2,3,6);//��ǰ��ɫ����
    Key_Enter(0xa6);
 
  }
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>8&&touch_lie<14))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,8,3,6);
    disp_zimu_toggle(18,8,"  B9 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,8,3,6);
    disp_zimu_row(18,8,"  A5  ",100);
    disp_juxing_row(DISPJX_FRONT,17,8,3,6);
    Key_Enter(0xb9);
 
  }
   if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>14&&touch_lie<20))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,14,3,6);
    disp_zimu_toggle(18,14,"  82 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,14,3,6);
    disp_zimu_row(18,14,"  82 ",100);
    disp_juxing_row(DISPJX_FRONT,17,14,3,6);
    Key_Enter(0x82);
 
  }
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>20&&touch_lie<26))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,20,3,6);
    disp_zimu_toggle(18,20,"  83 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,20,3,6);
    disp_zimu_row(18,20,"  83 ",100);
    disp_juxing_row(DISPJX_FRONT,17,20,3,6);
    Key_Enter(0x83);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>26&&touch_lie<32))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,26,3,6);
    disp_zimu_toggle(18,26,"  84 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,26,3,6);
    disp_zimu_row(18,26,"  84 ",100);
    disp_juxing_row(DISPJX_FRONT,17,26,3,6);
    Key_Enter(0x84);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>32&&touch_lie<38))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,32,3,6);
    disp_zimu_toggle(18,32,"  85 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,32,3,6);
    disp_zimu_row(18,32,"  85 ",100);
    disp_juxing_row(DISPJX_FRONT,17,32,3,6);
    Key_Enter(0x85);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>38&&touch_lie<44))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,38,3,6);
    disp_zimu_toggle(18,38,"  86 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,38,3,6);
    disp_zimu_row(18,38,"  86 ",100);
    disp_juxing_row(DISPJX_FRONT,17,38,3,6);
    Key_Enter(0x86);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>44&&touch_lie<50))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,44,3,6);
    disp_zimu_toggle(18,44,"  87 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,44,3,6);
    disp_zimu_row(18,44,"  87 ",100);
    disp_juxing_row(DISPJX_FRONT,17,44,3,6);
    Key_Enter(0x87);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>50&&touch_lie<56))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,50,3,6);
    disp_zimu_toggle(18,50,"  88 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,50,3,6);
    disp_zimu_row(18,50,"  88 ",100);
    disp_juxing_row(DISPJX_FRONT,17,50,3,6);
    Key_Enter(0x88);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>56&&touch_lie<62))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,56,3,6);
    disp_zimu_toggle(18,56,"  89 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,56,3,6);
    disp_zimu_row(18,56,"  89 ",100);
    disp_juxing_row(DISPJX_FRONT,17,56,3,6);
    Key_Enter(0x89);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>62&&touch_lie<68))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,62,3,6);
    disp_zimu_toggle(18,62,"  8A ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,62,3,6);
    disp_zimu_row(18,62,"  8A ",100);
    disp_juxing_row(DISPJX_FRONT,17,62,3,6);
    Key_Enter(0x8a);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>68&&touch_lie<74))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,68,3,6);
    disp_zimu_toggle(18,68,"  8B ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,68,3,6);
    disp_zimu_row(18,68,"  8B ",100);
    disp_juxing_row(DISPJX_FRONT,17,68,3,6);
    Key_Enter(0x8b);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>17&&touch_row<20)&&(touch_lie>74&&touch_lie<80))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,17,74,3,6);
    disp_zimu_toggle(18,74,"  8C ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,17,74,3,6);
    disp_zimu_row(18,74,"  8C ",100);
    disp_juxing_row(DISPJX_FRONT,17,74,3,6);
    Key_Enter(0x8c);
 
  }
  
   //b0---------------------bc
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>2&&touch_lie<8))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,2,3,6);
    disp_zimu_toggle(21,2,"  8D ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,2,3,6);
    disp_zimu_row(21,2,"  8D ",100);
    disp_juxing_row(DISPJX_FRONT,20,2,3,6);
    Key_Enter(0x8d);
 
  }
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>8&&touch_lie<14))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,8,3,6);
    disp_zimu_toggle(21,8,"  8E ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,8,3,6);
    disp_zimu_row(21,8,"  8E ",100);
    disp_juxing_row(DISPJX_FRONT,20,8,3,6);
    Key_Enter(0x8e);
 
  }
   if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>14&&touch_lie<20))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,14,3,6);
    disp_zimu_toggle(21,14,"  8F ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,14,3,6);
    disp_zimu_row(21,14,"  8F ",100);
    disp_juxing_row(DISPJX_FRONT,20,14,3,6);
    Key_Enter(0x8f);
 
  }
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>20&&touch_lie<26))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,20,3,6);
    disp_zimu_toggle(21,20,"  90 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,20,3,6);
    disp_zimu_row(21,20,"  90 ",100);
    disp_juxing_row(DISPJX_FRONT,20,20,3,6);
    Key_Enter(0x90);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>26&&touch_lie<32))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,26,3,6);
    disp_zimu_toggle(21,26,"  91 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,26,3,6);
    disp_zimu_row(21,26,"  91 ",100);
    disp_juxing_row(DISPJX_FRONT,20,26,3,6);
    Key_Enter(0x91);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>32&&touch_lie<38))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,32,3,6);
    disp_zimu_toggle(21,32,"  92 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,32,3,6);
    disp_zimu_row(21,32,"  92 ",100);
    disp_juxing_row(DISPJX_FRONT,20,32,3,6);
    Key_Enter(0x92);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>38&&touch_lie<44))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,38,3,6);
    disp_zimu_toggle(21,38,"  93 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,38,3,6);
    disp_zimu_row(21,38,"  93 ",100);
    disp_juxing_row(DISPJX_FRONT,20,38,3,6);
    Key_Enter(0x93);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>44&&touch_lie<50))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,44,3,6);
    disp_zimu_toggle(21,44,"  94 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,44,3,6);
    disp_zimu_row(21,44,"  94 ",100);
    disp_juxing_row(DISPJX_FRONT,20,44,3,6);
    Key_Enter(0x94);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>50&&touch_lie<56))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,50,3,6);
    disp_zimu_toggle(21,50,"  95 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,50,3,6);
    disp_zimu_row(21,50,"  95 ",100);
    disp_juxing_row(DISPJX_FRONT,20,50,3,6);
    Key_Enter(0x95);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>56&&touch_lie<62))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,56,3,6);
    disp_zimu_toggle(21,56,"  96 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,56,3,6);
    disp_zimu_row(21,56,"  96 ",100);
    disp_juxing_row(DISPJX_FRONT,20,56,3,6);
    Key_Enter(0x96);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>62&&touch_lie<68))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,62,3,6);
    disp_zimu_toggle(21,62,"  97 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,62,3,6);
    disp_zimu_row(21,62,"  97 ",100);
    disp_juxing_row(DISPJX_FRONT,20,62,3,6);
    Key_Enter(0x97);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>68&&touch_lie<74))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,68,3,6);
    disp_zimu_toggle(21,68,"  98 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,68,3,6);
    disp_zimu_row(21,68,"  98 ",100);
    disp_juxing_row(DISPJX_FRONT,20,68,3,6);
    Key_Enter(0x98);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>20&&touch_row<23)&&(touch_lie>74&&touch_lie<80))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,20,74,3,6);
    disp_zimu_toggle(21,74,"  99 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,20,74,3,6);
    disp_zimu_row(21,74,"  99 ",100);
    disp_juxing_row(DISPJX_FRONT,20,74,3,6);
    Key_Enter(0x99);
 
  }
  
  
   //c0---------------------cc
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>2&&touch_lie<8))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,2,3,6);
    disp_zimu_toggle(24,2,"  BA ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,2,3,6);
    disp_zimu_row(24,2,"  BA ",100);
    disp_juxing_row(DISPJX_FRONT,23,2,3,6);
    Key_Enter(0xba); 
 
  }
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>8&&touch_lie<14))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,8,3,6);
    disp_zimu_toggle(24,8,"  BB ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,8,3,6);
    disp_zimu_row(24,8,"  BB ",100);
    disp_juxing_row(DISPJX_FRONT,23,8,3,6);
    Key_Enter(0xbb);
 
  }
   if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>14&&touch_lie<20))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,14,3,6);
    disp_zimu_toggle(24,14,"  9C ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,14,3,6);
    disp_zimu_row(24,14,"  9C ",100);
    disp_juxing_row(DISPJX_FRONT,23,14,3,6);
    Key_Enter(0x9c);
 
  }
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>20&&touch_lie<26))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,20,3,6);
    disp_zimu_toggle(24,20,"  9D ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,20,3,6);
    disp_zimu_row(24,20,"  9D ",100);
    disp_juxing_row(DISPJX_FRONT,23,20,3,6);
    Key_Enter(0x9d);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>26&&touch_lie<32))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,26,3,6);
    disp_zimu_toggle(24,26,"  9E ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,26,3,6);
    disp_zimu_row(24,26,"  9E ",100);
    disp_juxing_row(DISPJX_FRONT,23,26,3,6);
    Key_Enter(0x9e);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>32&&touch_lie<38))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,32,3,6);
    disp_zimu_toggle(24,32,"  9F ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,32,3,6);
    disp_zimu_row(24,32,"  9F ",100);
    disp_juxing_row(DISPJX_FRONT,23,32,3,6);
    Key_Enter(0x9f);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>38&&touch_lie<44))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,38,3,6);
    disp_zimu_toggle(24,38,"  B2 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,38,3,6);
    disp_zimu_row(24,38,"  B2 ",100);
    disp_juxing_row(DISPJX_FRONT,23,38,3,6);
    Key_Enter(0xb2);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>44&&touch_lie<50))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,44,3,6);
    disp_zimu_toggle(24,44,"  B3 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,44,3,6);
    disp_zimu_row(24,44,"  B3 ",100);
    disp_juxing_row(DISPJX_FRONT,23,44,3,6);
    Key_Enter(0xb3);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>50&&touch_lie<56))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,50,3,6);
    disp_zimu_toggle(24,50,"  B4 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,50,3,6);
    disp_zimu_row(24,50,"  B4 ",100);
    disp_juxing_row(DISPJX_FRONT,23,50,3,6);
    Key_Enter(0xb4);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>56&&touch_lie<62))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,56,3,6);
    disp_zimu_toggle(24,56,"  B5 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,56,3,6);
    disp_zimu_row(24,56,"  B5 ",100);
    disp_juxing_row(DISPJX_FRONT,23,56,3,6);
    Key_Enter(0xb5);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>62&&touch_lie<68))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,62,3,6);
    disp_zimu_toggle(24,62,"  B6 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,62,3,6);
    disp_zimu_row(24,62,"  B6 ",100);
    disp_juxing_row(DISPJX_FRONT,23,62,3,6);
    Key_Enter(0xb6);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>68&&touch_lie<74))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,68,3,6);
    disp_zimu_toggle(24,68,"  B7 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,68,3,6);
    disp_zimu_row(24,68,"  B7 ",100);
    disp_juxing_row(DISPJX_FRONT,23,68,3,6);
    Key_Enter(0xb7);
 
  }
  
  if((returnvalue_down==1)&&(touch_row>23&&touch_row<26)&&(touch_lie>74&&touch_lie<80))
  {
    returnvalue_down=0;
    disp_juxing_row(FILLJX_FRONT,23,74,3,6);
    disp_zimu_toggle(24,74,"  B8 ",100);
    delay_us(100);
    disp_juxing_row(FILLJX_BACK,23,74,3,6);
    disp_zimu_row(24,74,"  B8 ",100);
    disp_juxing_row(DISPJX_FRONT,23,74,3,6);
    Key_Enter(0xb8);
 
  }
  
  
}
  
void Key_Enter(char command)
{
  uartsendbyte(&huart1,0x1B);
  uartsendbyte(&huart1,0x5B);
  uartsendbyte(&huart1,command);
  uartsendbyte(&huart1,0x7a);
  uartsendbyte(&huart1,0x0d);


}
