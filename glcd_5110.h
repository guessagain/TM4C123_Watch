#ifndef _GLCD_H
#define _GLCD_H
#include "stdint.h"


typedef struct {
	uint8_t x_min;
	uint8_t y_min;
	uint8_t x_max;
	uint8_t y_max;
} glcd_BoundingBox_t;





void glcd_update_bbox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax);


void glcd_reset_bbox();

void glcd_set_pixel(uint8_t x, uint8_t y, uint8_t color);

void glcd_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);

void DrawLine(int x1, int y1, int x2, int y2);
void ClearLine(int x1, int y1, int x2, int y2);
void DrawPixel(int x, int y);
void ClearPixel(int x, int y);
void DrawCircle(unsigned int xpos, unsigned char ypos, unsigned int R, unsigned int color);

void Plot8(unsigned char x,unsigned char y,unsigned char dx,unsigned char dy, unsigned int color);

void Clock_second(unsigned int angle);

void Clock_dial();

void Clock_minutes(unsigned int angle);

void Clock_hours(unsigned int angle);

void Digital_second(unsigned int second);

void Digital_minutes(unsigned int minutes);

void Digital_hours(unsigned int hours);

#endif