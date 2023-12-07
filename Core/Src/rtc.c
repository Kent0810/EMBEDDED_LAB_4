/*
 * rtc.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Dell
 */

#include "rtc.h"
#include "lcd.h"
#include "software_timer.h"
#include "ds3231.h"
#include "button.h"

int CURRENT_MODE = 0;
int CURRENT_MODIFIER = 0;
int CURRENT_YEAR = 0;
int CURRENT_MONTH = 0;
int CURRENT_DATE = 0;
int CURRENT_DAY = 0;
int CURRENT_HOUR = 0;
int CURRENT_MINUTE = 0;
int CURRENT_SEC = 0;

int current_state = HOUR_MODIFER;

void updateCurrent(int year, int month, int date, int day, int hour, int minute, int sec){
	CURRENT_YEAR = year;
	CURRENT_MONTH = month;
	CURRENT_DATE = date;
	CURRENT_DAY = day;
	CURRENT_HOUR = hour;
	CURRENT_MINUTE = minute;
	CURRENT_SEC = sec;
}


void timeCounter(){
	if(flag_timer1 == 1){
		CURRENT_SEC++;
		setTimer1(1000);
		if(CURRENT_SEC==60){
			CURRENT_MINUTE++;
			CURRENT_SEC=0;
		}
		if(CURRENT_MINUTE == 60) {
			CURRENT_HOUR++;
			CURRENT_MINUTE = 0;
		}
		if(CURRENT_HOUR == 24) {
			CURRENT_DATE++;
			CURRENT_HOUR = 0;
		}
		if(CURRENT_DATE >= 30){
			CURRENT_MONTH++;
			CURRENT_DATE = 1;
		}
		if(CURRENT_MONTH >12){
			CURRENT_YEAR++;
		}
		if(CURRENT_YEAR > 99){
			CURRENT_YEAR = 0;
		}

	}
	ds3231_Write(ADDRESS_YEAR, CURRENT_YEAR);
	ds3231_Write(ADDRESS_MONTH, CURRENT_MONTH);
	ds3231_Write(ADDRESS_DATE, CURRENT_DATE);
	ds3231_Write(ADDRESS_HOUR, CURRENT_HOUR);
	ds3231_Write(ADDRESS_MIN, CURRENT_MINUTE);
	ds3231_Write(ADDRESS_SEC, CURRENT_SEC);

	ds3231_ReadTime();
}

void displayTime() {
	lcd_ShowIntNum(70, 100, ds3231_hours, 2, GREEN, BLACK, 24);
	lcd_ShowIntNum(110, 100, ds3231_min, 2, GREEN, BLACK, 24);
	lcd_ShowIntNum(150, 100, ds3231_sec, 2, GREEN, BLACK, 24);
	lcd_ShowIntNum(70, 130, ds3231_date, 2, YELLOW, BLACK, 24);
	lcd_ShowIntNum(110, 130, ds3231_month, 2, YELLOW, BLACK, 24);
	lcd_ShowIntNum(150, 130, ds3231_year, 2, YELLOW, BLACK, 24);
}
void turnOffNumber(int number) {
	if(number == HOUR_MODIFER){
		lcd_ShowIntNum(70, 100, ds3231_hours, 2, BLACK, BLACK, 24);
	}
	else if (number == MIN_MODIFER){
		lcd_ShowIntNum(110, 100, ds3231_min, 2, BLACK, BLACK, 24);
	}
	else if (number == SEC_MODIFER){
		lcd_ShowIntNum(150, 100, ds3231_sec, 2, BLACK, BLACK, 24);
	}
	else if (number == DATE_MODIFER){
		lcd_ShowIntNum(70, 130, ds3231_date, 2, BLACK, BLACK, 24);

	}
	else if(number == MONTH_MODIFER){
		lcd_ShowIntNum(110, 130, ds3231_month, 2, BLACK, BLACK, 24);
	}
	else if(number == YEAR_MODIFER){
		lcd_ShowIntNum(150, 130, ds3231_year, 2, BLACK, BLACK, 24);
	}
}
void turnOnNumber(int number) {
	if(number == HOUR_MODIFER){
		lcd_ShowIntNum(70, 100, ds3231_hours, 2, GREEN, BLACK, 24);
	}
	else if (number == MIN_MODIFER){
		lcd_ShowIntNum(110, 100, ds3231_min, 2, GREEN, BLACK, 24);
	}
	else if (number == SEC_MODIFER){
		lcd_ShowIntNum(150, 100, ds3231_sec, 2, GREEN, BLACK, 24);
	}
	else if (number == DATE_MODIFER){
		lcd_ShowIntNum(70, 130, ds3231_date, 2, YELLOW, BLACK, 24);

	}
	else if(number == MONTH_MODIFER){
		lcd_ShowIntNum(110, 130, ds3231_month, 2, YELLOW, BLACK, 24);
	}
	else if(number == YEAR_MODIFER){
		lcd_ShowIntNum(150, 130, ds3231_year, 2, YELLOW, BLACK, 24);
	}

}

void timerModifier(){
	switch(CURRENT_MODIFIER) {
	case INIT:
		setTimer3(250);
		CURRENT_MODIFIER = WAIT;
		break;
	case WAIT:
		turnOffNumber(current_state);
		if(flag_timer3 == 1){
			setTimer3(250);
			CURRENT_MODIFIER = current_state; // wait FOR 250ms then change state
		}
		break;
	case HOUR_MODIFER:
		turnOnNumber(HOUR_MODIFER);
		current_state = HOUR_MODIFER;
		if(flag_timer3 == 1){
			setTimer3(250);//change state HOUR -> MIN
			CURRENT_MODIFIER = WAIT;
		}
		break;
	case MIN_MODIFER:
		turnOnNumber(MIN_MODIFER);
		current_state = MIN_MODIFER;
		if(flag_timer3 == 1){
			setTimer3(250);//change state HOUR -> MIN
			CURRENT_MODIFIER = WAIT;
		}
		break;

	case SEC_MODIFER:
		turnOnNumber(SEC_MODIFER);
		current_state = SEC_MODIFER;
		if(flag_timer3 == 1){
			setTimer3(250);//change state HOUR -> MIN
			CURRENT_MODIFIER = WAIT;
		}
		break;
	case DATE_MODIFER:
		turnOnNumber(DATE_MODIFER);
		current_state = DATE_MODIFER;
		if(flag_timer3 == 1){
			setTimer3(250);//change state HOUR -> MIN
			CURRENT_MODIFIER = WAIT;
		}
		break;
	case MONTH_MODIFER:
		turnOnNumber(MONTH_MODIFER);
		current_state = MONTH_MODIFER;
		if(flag_timer3 == 1){
			setTimer3(250);//change state HOUR -> MIN
			CURRENT_MODIFIER = WAIT;
		}
		break;

	case YEAR_MODIFER:
		turnOnNumber(MONTH_MODIFER);
		current_state = MONTH_MODIFER;
		if(flag_timer3 == 1){
			setTimer3(250);//change state HOUR -> MIN
			CURRENT_MODIFIER = WAIT;
		}
		break;
	}
}


void timerCountDown(){
	if(flag_timer1 == 1){
		CURRENT_SEC--;
		setTimer1(1000);
		if(CURRENT_SEC== 0){
			CURRENT_MINUTE++;
			CURRENT_SEC= 59;
		}
		if(CURRENT_MINUTE == 0) {
			CURRENT_HOUR++;
			CURRENT_MINUTE = 59;
		}
		if(CURRENT_HOUR == 0) {
			CURRENT_DATE++;
			CURRENT_HOUR = 23;
		}
		if(CURRENT_DATE == 0){
			CURRENT_MONTH++;
			CURRENT_DATE = 31;
		}
		if(CURRENT_MONTH == 0){
			CURRENT_YEAR--;
		}
	}
	ds3231_Write(ADDRESS_YEAR, CURRENT_YEAR);
	ds3231_Write(ADDRESS_MONTH, CURRENT_MONTH);
	ds3231_Write(ADDRESS_DATE, CURRENT_DATE);
	ds3231_Write(ADDRESS_HOUR, CURRENT_HOUR);
	ds3231_Write(ADDRESS_MIN, CURRENT_MINUTE);
	ds3231_Write(ADDRESS_SEC, CURRENT_SEC);

	ds3231_ReadTime();

	if(CURRENT_SEC + CURRENT_MINUTE + CURRENT_HOUR + CURRENT_DATE + CURRENT_MONTH + CURRENT_YEAR == 0){
		for(int i = 0; i< 10;i++){
			lcd_Clear(RED);
			lcd_Clear(WHITE);
		}
		lcd_StrCenter(0, 0, "TIME OVER!!!!!!!!", WHITE, BLACK, 24, 1);
		lcd_Clear(BLACK);
	}
}

void TimerStateMachine() {
	displayTime();
	switch(CURRENT_MODE){
		case 0:
			timeCounter();
			break;
		case 1:
			timerModifier();
			break;
		case 2:
			timerCountDown();
			break;
		default:
			break;
	}
}
void displayCurrentMode(){
	lcd_displayCurrentMode();
}


