#include "ds1307.h"

//uncomment for use Softwer I2C for STM32
//#define USE_SOFT_I2C			

//include I2C Lib
#ifdef USE_SOFT_I2C
	#include "i2c_sw.h"
#else
	#include <i2c.h>
#endif



void ds1307_init()
{
#ifdef USE_SOFT_I2C
	SW_I2C_initial();
	i2c_port_initial(SW_I2C1);
	set_ds1307_sqw(0,0,0);
#else
	i2c_init();
#endif
}

void write_i2c(uint8_t reg,uint8_t data)
{
#ifdef USE_SOFT_I2C
	SW_I2C_WriteControl_8Bit(SW_I2C1,0xd0,reg,data);
#else
	i2c_start();
	i2c_write(0xd0);
	i2c_write(reg);
	i2c_write(data);
	i2c_stop();
#endif
}

uint8_t read_i2c(uint8_t reg)
{
#ifdef USE_SOFT_I2C
	return SW_I2C_ReadControl_8Bit(SW_I2C1,0xd0,reg);
#else
	uint8_t data;
	i2c_start();   
	i2c_write(0xd0);
	i2c_write(reg);
	i2c_start();
	i2c_write(0xd0| 1);
	data=i2c_read(0);
	i2c_stop(); 
	return data;
#endif
}

void get_ds1307_time(uint8_t *h,uint8_t *m,uint8_t *s)
{
*h=read_i2c(0x02);
*m=read_i2c(0x01);
*s=read_i2c(0x00);

*h=((*h>>4)*10)+(*h&0x0f);
*m=((*m>>4)*10)+(*m&0x0f);
*s=((*s>>4)*10)+(*s&0x0f);
} 

void get_ds1307_date(uint8_t *year,uint8_t *month,uint8_t *date,uint8_t *day)
{

*year=read_i2c(0x06);
*month=read_i2c(0x05);
*date=read_i2c(0x04);
*day=read_i2c(0x03);

*year=((*year>>4)*10)+(*year&0x0f);
*month=((*month>>4)*10)+(*month&0x0f);
*date=((*date>>4)*10)+(*date&0x0f);
*day=((*day>>4)*10)+(*day&0x0f);
}

void set_ds1307_time(uint8_t h,uint8_t m,uint8_t s)
{
h=(h%10)|((h/10)<<4);
m=(m%10)|((m/10)<<4);
s=(s%10)|((s/10)<<4);
write_i2c(0x02,h);
write_i2c(0x01,m);
write_i2c(0x00,s);
} 


void set_ds1307_date(uint8_t year,uint8_t month,uint8_t date,uint8_t day)
{
year=(year%10)|((year/10)<<4);
month=(month%10)|((month/10)<<4);
date=(date%10)|((date/10)<<4);
day=(day%10)|((day/10)<<4);

write_i2c(0x06,year);
write_i2c(0x05,month);
write_i2c(0x04,date);
write_i2c(0x03,day);
}

void set_ds1307_out(uint8_t set1or0)
{
if(set1or0==1)
 { 
 write_i2c(0x07,0x80);
 }
else
 { 
 write_i2c(0x07,0x00);
 }
}

void set_ds1307_sqw(uint8_t en,uint8_t rs1,uint8_t rs0)
{
// EN  RS1 RS0     SQW Out Freq
// 1  0   0       1       Hz
// 1  0   1       4.096   KHz
// 1  1   0       8.192   KHz
// 1  1   1       32.768  KHz
write_i2c(0x07,(en<<4)|(rs1<<1)|(rs0<<0));
}

