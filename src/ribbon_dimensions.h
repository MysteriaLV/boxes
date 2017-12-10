//
// Created by VermutMac on 2017-12-06.
//

#ifndef BOXES_RIBBON_DIMENSIONS_H
#define BOXES_RIBBON_DIMENSIONS_H

#ifndef SMALL_RIBBON
	#define Q1_START 0
	#define Q2_START 40
	#define Q3_START 85
	#define Q4_START 128
	#define Q5_START 160
	#define Q6_START 200
	#define Q7_START 240
#else
	#define Q1_START 0
	#define Q2_START 15
	#define Q3_START 30
	#define Q4_START 45
	#define Q5_START 70
	#define Q6_START 90
	#define Q7_START 110
	#define Q8_START 130
	#define Q_LAST_LED 143
#endif

#define BTN1_POSITION Q2_START
#define BTN2_POSITION Q3_START
#define BTN3_POSITION Q4_START
#define BTN4_POSITION Q5_START
#define BTN5_POSITION Q6_START
#define BTN6_POSITION Q7_START
#define BTN7_POSITION Q8_START

#endif //BOXES_RIBBON_DIMENSIONS_H
