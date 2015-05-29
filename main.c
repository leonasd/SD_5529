#include <msp430.h>
#include <SD_SPI.h>
#include <BCSplus_init.h>
//#include <SD_HardWare.h>
#define SD_SECTOR_ADDR  52360
#define SD_SECTOR_FIRST 0
#define SD_SECTOR_NUM   128

unsigned char DATA[128] = {0};

void My_Write_Data();
void My_Read_Data();

/*
 * main.c
 */

/**************************************************************************
 *名      称：int main()
 *功      能：主函数
 *入口参数：无
 *出口参数：无
 *说      明：程序入口
 *范      例：无
 *************************************************************************/
int main(void)
{
    unsigned char temp = 0;
	BCSplus_graceInit();
    //SD卡   DAC芯片   单片机SPI初始化
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    SPI_init();
    //USCI_A0_init();

    do
    {
    	temp = SD_Init();
    }while(temp == 0);

    My_Write_Data();
    My_Read_Data();

    P1OUT |= BIT0;
	return 0;
}

void My_Write_Data()
{
    unsigned char i = 0, temp = 0;
    unsigned char Temp[128] = {0};

    for(i=0; i<128; i++)
    {
    	Temp[i] = i;
    }
    Temp[127] = 99;
    do
    {
    	temp = SD_Write_Sector(SD_SECTOR_ADDR, Temp, SD_SECTOR_FIRST, SD_SECTOR_NUM);
    }while(temp == 0);
}

void My_Read_Data()
{
    unsigned char i = 0, temp = 0;

    for(i=0; i<128; i++)
    {
    	DATA[i] = 0;
    }

    do
    {
    	temp = SD_Read_Sector(SD_SECTOR_ADDR, DATA, SD_SECTOR_FIRST, SD_SECTOR_NUM);
    }while(temp == 0);
}
