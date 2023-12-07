/*
 * rtc.h
 *
 *  Created on: Nov 23, 2023
 *      Author: Dell
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#define INIT 0
#define HOUR_MODIFER 1
#define MIN_MODIFER 2
#define SEC_MODIFER 3
#define DATE_MODIFER 4
#define MONTH_MODIFER 5
#define YEAR_MODIFER 6
#define WAIT 7

extern int current_state;
extern int CURRENT_MODE;
extern int CURRENT_COUNTDOWN_MODE;
extern int CURRENT_MODIFIER;

extern int CURRENT_YEAR;
extern int CURRENT_MONTH;
extern int CURRENT_DATE;
extern int CURRENT_DAY;
extern int CURRENT_HOUR;
extern int CURRENT_MINUTE;
extern int CURRENT_SEC;

void updateCurrent(int year, int month, int date, int day, int hour, int minute, int sec);
void displayCurrentMode();
void TimerStateMachine();
void timeCounter();
#endif /* INC_RTC_H_ */
