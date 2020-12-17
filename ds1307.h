/*
 By Liyanboy74
 https://github.com/liyanboy74
*/

#ifndef __DS1307_H
#define __DS1307_H

#include "stdio.h"
#include "main.h"

void ds1307_init(void);
void write_i2c(uint8_t reg,uint8_t data);
uint8_t read_i2c(uint8_t reg);
void get_ds1307_time(uint8_t *h,uint8_t *m,uint8_t *s);
void get_ds1307_date(uint8_t *year,uint8_t *month,uint8_t *date,uint8_t *day);
void set_ds1307_time(uint8_t h,uint8_t m,uint8_t s);
void set_ds1307_date(uint8_t year,uint8_t month,uint8_t date,uint8_t day);
void set_ds1307_out(uint8_t set1or0);
void set_ds1307_sqw(uint8_t en,uint8_t rs1,uint8_t rs0);

#endif
