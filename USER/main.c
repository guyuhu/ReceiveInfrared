/******************** (C) COPYRIGHT **************************
 * 本代码是作为红外定位装置的主模块来设计的，基于stm32，现描述下整个项目的编写思路，
 仅供参考；
   1、利用定时器timer2，作为测量收到的波形的计数点。由于我们的红外波形接收端收到的波形
   呈现起始符+数据+结束符。将5单位高电平作为起始符，其后的低电平时间最为之后1、0的参考时间。
   
   2、现说明定义的格式：起始符：5单位高电平，之后为1单位低电平
                        ；数据中0的定义：1单位高+1单位低电平；
                        数据中1的定义：1单位高+3单位低电平；
                        结束符：7单位高电平
   3、程序思路：在电平的变化点上，分别用一个变量来记录，分别为t1.....t68，这些只是作为波形变化点的timer2的计数值。
      根据经验：timer2，周期为10ms，发送整个数据帧时间为1.5ms左右。
      同时根据记录点来计算出各高低电平的持续时间为：h1,...h34;l1,,,,l33;
      
      在根据经验前提下，在主函数中，满足代码中写定的条件时，才写定数据；写定数据时，我在这里采用一个int变
      量通过移位来存储数据。
   4、在实测时，发现误码率很高，做了以下调整。
      利用定时器timer3设置周期为500us,作为在测量每个具体波段时的超时功能。在中断函数中设置
      标志位，在每个波形变化点测量时，做与条件，保证波形不超时。                     
**********************************************************************************/

#include "receiveInfared.h"
#include "stm32f10x_it.h"
#include "usart.h"

#define RGPIO GPIOA
#define RPIN GPIO_Pin_4
#define ReadInput() GPIO_ReadInputDataBit(RGPIO,RPIN)
#define ReadTimer() TIM_GetCounter(TIM2)
#define MODULE 9999

int ReceiveData=0;
u16 compareLow;
u16 tempLow;

u16 t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17;
u16 t18,t19,t20,t21,t22,t23,t24,t25,t26,t27,t28,t29,t30,t31,t32;
u16 t33,t34,t35,t36,t37,t38,t39,t40,t41,t42,t43,t44,t45,t46,t47,t48;
u16 t49,t50,t51,t52,t53,t54,t55,t56,t57,t58,t59,t60,t61,t62,t63,t64,t65,t66,t67,t68;

u16 h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,h11,h12,h13,h14,h15,h16;
u16 h17,h18,h19,h20,h21,h22,h23,h24,h25,h26,h27,h28,h29,h30,h31,h32,h33,h34;

u16 l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15,l16;
u16 l17,l18,l19,l20,l21,l22,l23,l24,l25,l26,l27,l28,l29,l30,l31,l32,l33; 

/* 
 * 函数名：detect
 * 描述  : 首先是检测出两波形，然后得到高低电平值。
 * 输入  ：无
 * 输出  : 无
 */
void detect()
{
   TIM_SetCounter(TIM2,0);
   
   //TIM_SetCounter(TIM3,0);   
//    do
//    {
//       t1=ReadTimer();
//    }
//    while((ReadInput()==0)&& (timeoutFlag==FALSE));
   t1=0;
   
   
   do
   {
      t2=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t3=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t4=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
   do
   {
      t5=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t6=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t7=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t8=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t9=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t10=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t11=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t12=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
   do
   {
      t13=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t14=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t15=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t16=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
   do
   {
      t17=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t18=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t19=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t20=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
   do
   {
      t21=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t22=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t23=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t24=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t25=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t26=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t27=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t28=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
   do
   {
      t29=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t30=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t31=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t32=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
   do
   {
      t33=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t34=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t35=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t36=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
   do
   {
      t37=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t38=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t39=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t40=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t41=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t42=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t43=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t44=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
   do
   {
      t45=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t46=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t47=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t48=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
   do
   {
      t49=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t50=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t51=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t52=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
   do
   {
      t53=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t54=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t55=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t56=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t57=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t58=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t59=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t60=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
   do
   {
      t61=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t62=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t63=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t64=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));

   TIM_SetCounter(TIM3,0);
    do
   {
      t65=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t66=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t67=ReadTimer();
   }
   while((ReadInput()==0)&& (timeoutFlag==FALSE));
   
   TIM_SetCounter(TIM3,0);
   do
   {
      t68=ReadTimer();
   }
   while((ReadInput()==1)&& (timeoutFlag==FALSE));
   
   timeoutFlag=FALSE;//状态清理，设置为
}

/* 
 * 函数名：compute
 * 描述  : 当符合条件时，则计算出电平时间
 * 输入  ：无
 * 输出  : 无
 */
void compute()
{
	h1=t2-t1;
	h2=t4-t3;
	h3=t6-t5;
	h4=t8-t7;
	h5=t10-t9;
	h6=t12-t11;
	h7=t14-t13;
	h8=t16-t15;
	h9=t18-t17;
	h10=t20-t19;
	h11=t22-t21;
	h12=t24-t23;
	h13=t26-t25;
	h14=t28-t27;
	h15=t30-t29;
	h16=t32-t31;
	h17=t34-t33;
	h18=t36-t35;
	h19=t38-t37;
	h20=t40-t39;
	h21=t42-t41;
	h22=t44-t43;
	h23=t46-t45;
	h24=t48-t47;
	h25=t50-t49;
	h26=t52-t51;
	h27=t54-t53;
	h28=t56-t55;
	h29=t58-t57;
	h30=t60-t59;
	h31=t62-t61;
	h32=t64-t63;
	h33=t66-t65;
	h34=t68-t67;
	
	l1=t3-t2;
	l2=t5-t4;
	l3=t7-t6;
	l4=t9-t8;
	l5=t11-t10;
	l6=t13-t12;
	l7=t15-t14;
	l8=t17-t16;
	l9=t19-t18;
	l10=t21-t20;
	l11=t23-t22;
	l12=t25-t24;
	l13=t27-t26;
	l14=t29-t28;
	l15=t31-t30;
	l16=t33-t32;
	l17=t35-t34;
	l18=t37-t36;
	l19=t39-t38;
	l20=t41-t40;
	l21=t43-t42;
	l22=t45-t44;
	l23=t47-t46;
	l24=t49-t48;
	l25=t51-t50;
	l26=t53-t52;
	l27=t55-t54;
	l28=t57-t56;
	l29=t59-t58;
	l30=t61-t60;
	l31=t63-t62;
	l32=t65-t64;
	l33=t67-t66;	
}

/* 
 * 函数名：compute
 * 描述  : 将信号存储起来
 * 输入  ：无
 * 输出  : 无
 */
void write(u16 low)
{ 
   if(low<tempLow)
   {
      ReceiveData=(ReceiveData & 0xFFFFFFFE)<<1;//写0
   }
   else
   {
      ReceiveData=(ReceiveData | 0x00000001)<<1;//写1
   }    
}

void writeEnd(u16 low)
{                                //结果右移 
  if(low<tempLow)
   {
      ReceiveData=(ReceiveData & 0xFFFFFFFE);//写0
   }
   else
   {
      ReceiveData=(ReceiveData | 0x00000001);//写1
   }
}

void writeAll()
{
	write(l2);
	write(l3);
	write(l4);
	write(l5);
	write(l6);
	write(l7);
	write(l8);
	write(l9);
	write(l10);
	write(l11);
	write(l12);
	write(l13);
	write(l14);
	write(l15);
	write(l16);
	write(l17);
	write(l18);
	write(l19);
	write(l20);
	write(l21);
	write(l22);
	write(l23);
	write(l24);
	write(l25);
	write(l26);
	write(l27);
	write(l28);
	write(l29);
	write(l30);
	write(l31);
	write(l32);

	writeEnd(l33);
}

/* 
 * 函数名：main
 * 描述  : 主函数
 * 输入  ：无
 * 输出  : 无
 */
int  main(void)
{   
   GPIO_Configuration();
   TIM_NVIC_Configuration();   
   TIM_Configuration();
   TIM3_NVIC_Configuration();
   TIM3_Configuration();
   
   USART1_Config();  
   while(1)
   {
      ReceiveData=0;
      timeoutFlag=FALSE;
      
      if(ReadInput()==0)
      {
         TIM_SetCounter(TIM3,0);
      }
      else
      {         
         detect();
         compute();
         if((h1>50)&&(h1<75)&&(h34>75))		//这一段用来将数据存储起来
         {
            compareLow=l1;
            tempLow=1.5*compareLow;
            writeAll();
            printf("this is the data: %d",ReceiveData);
         }
      }  
   }
}



