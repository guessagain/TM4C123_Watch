

#include "stdint.h"
#include "glcd_5110.h"
#include "Nokia5110.h"
#include "math.h"

#define PI 3.14
#define DIAL_S 15
#define DIAL_M 12
#define DIAL_H 9
#define DIAL_CLOCK 16
unsigned int clock_x[150]={0},clock_y[150]={0},i,j;
unsigned int pix_data[64][5]={0};


void DrawLine(int x1, int y1, int x2, int y2)
{
int i, deltax, deltay, numpixels;
int d, dinc1, dinc2;
int x, xinc1, xinc2;
int y, yinc1, yinc2;
//calculate deltaX and deltaY
deltax = abs(x2 - x1);
deltay = abs(y2 - y1);
//initialize
if(deltax >= deltay)
{
//If x is independent variable
numpixels = deltax + 1;
d = (2 * deltay) - deltax;
dinc1 = deltay << 1;
dinc2 = (deltay - deltax) << 1;
xinc1 = 1;
xinc2 = 1;
yinc1 = 0;
yinc2 = 1;
}
else
{
//if y is independent variable
numpixels = deltay + 1;
d = (2 * deltax) - deltay;
dinc1 = deltax << 1;
dinc2 = (deltax - deltay) << 1;
xinc1 = 0;
xinc2 = 1;
yinc1 = 1;
yinc2 = 1;
}
//move the right direction
if(x1 > x2)
{
xinc1 = -xinc1;
xinc2 = -xinc2;
}
if(y1 > y2)
{
yinc1 = -yinc1;
yinc2 = -yinc2;
}
x = x1;
y = y1;
//draw the pixels
for(i = 1; i < numpixels; i++)
{
DrawPixel(x, y);
if(d < 0)
{d = d + dinc1;
x = x + xinc1;
y = y + yinc1;
}
else
{
d = d + dinc2;
x = x + xinc2;
y = y + yinc2;
}
}
}

void ClearLine(int x1, int y1, int x2, int y2)
{
int i, deltax, deltay, numpixels;
int d, dinc1, dinc2;
int x, xinc1, xinc2;
int y, yinc1, yinc2;
//calculate deltaX and deltaY
deltax = abs(x2 - x1);
deltay = abs(y2 - y1);
//initialize
if(deltax >= deltay)
{
//If x is independent variable
numpixels = deltax + 1;
d = (2 * deltay) - deltax;
dinc1 = deltay << 1;
dinc2 = (deltay - deltax) << 1;
xinc1 = 1;
xinc2 = 1;
yinc1 = 0;
yinc2 = 1;
}
else
{
//if y is independent variable
numpixels = deltay + 1;
d = (2 * deltax) - deltay;
dinc1 = deltax << 1;
dinc2 = (deltax - deltay) << 1;
xinc1 = 0;
xinc2 = 1;
yinc1 = 1;
yinc2 = 1;
}
//move the right direction
if(x1 > x2)
{
xinc1 = -xinc1;
xinc2 = -xinc2;
}
if(y1 > y2)
{
yinc1 = -yinc1;
yinc2 = -yinc2;
}
x = x1;
y = y1;
//draw the pixels
for(i = 1; i < numpixels; i++)
{
ClearPixel(x, y);
if(d < 0)
{d = d + dinc1;
x = x + xinc1;
y = y + yinc1;
}
else
{
d = d + dinc2;
x = x + xinc2;
y = y + yinc2;
}
}
}

void ClearPixel(int x, int y)
{
	int y_row,data,y_pos;
	y_row = y/8;
	y_pos = pow(2,(y%8));
	pix_data[x][y_row] = pix_data[x][y_row] & (~y_pos);
	Nokia5110_Setpix(x, y_row,pix_data[x][y_row]);
}

void DrawPixel(int x, int y)
{
	int y_row,data,y_pos;
	y_row = y/8;
	y_pos = pow(2,(y%8));
	pix_data[x][y_row] = pix_data[x][y_row] | y_pos;
	Nokia5110_Setpix(x, y_row,pix_data[x][y_row]);
}


// Draws clock-dial on LCD. 
void Clock_dial()
{
	unsigned int angle = 0; 
	double x=42,y=24;
	double radians;
	Nokia5110_SetCursor(5, 0);
	Nokia5110_OutDec(12); 
	Nokia5110_SetCursor(2, 2);
	Nokia5110_OutCharU('9'); 
	Nokia5110_SetCursor(2, 3);
	Nokia5110_OutCharD('9');
	Nokia5110_SetCursor(9, 2);
	Nokia5110_OutCharU('3');
	Nokia5110_SetCursor(9, 3);
	Nokia5110_OutCharD('3');
	Nokia5110_SetCursor(5, 5);
	Nokia5110_OutChar('6'); 
	for(angle =0; angle <361; angle++)
	{
	radians = (PI/180)*angle;
	x = (cos(radians) * DIAL_CLOCK)+42; 
	x = floor(x);
	y = (sin(radians) * DIAL_CLOCK)+24;
	y = floor(y);
	DrawPixel(x,y);
	}
}

//Clock circular motion
void Clock_second(unsigned int angle)
{
	static double x_s=42,y_s=24;
	double radians;
	ClearLine(42, 24, x_s, y_s);
	radians = (PI/180)*angle;
	x_s = (cos(radians) * DIAL_S)+42; 
	x_s = floor(x_s);
	y_s = (sin(radians) * DIAL_S)+24;
	y_s = floor(y_s);
	DrawLine(42, 24, x_s, y_s);
}

void Clock_minutes(unsigned int angle)
{
	static double x_m=42,y_m=24;
	double radians;
	ClearLine(42, 24, x_m, y_m);
	radians = (PI/180)*angle;
	x_m = (cos(radians) * DIAL_M)+42; 
	x_m = floor(x_m);
	y_m = (sin(radians) * DIAL_M)+24;
	y_m = floor(y_m);
	DrawLine(42, 24, x_m, y_m);
}

void Clock_hours(unsigned int angle)
{
	static double x_h=42,y_h=24;
	double radians;
	ClearLine(42, 24, x_h, y_h);
	radians = (PI/180)*angle;
	x_h = (cos(radians) * DIAL_H)+42; 
	x_h = floor(x_h);
	y_h = (sin(radians) * DIAL_H)+24;
	y_h = floor(y_h);
	DrawLine(42, 24, x_h, y_h);
}

void Digital_second(unsigned int second)
{
	Nokia5110_SetCursor(9, 2);
	Nokia5110_OutChar('S'); 
	Nokia5110_OutChar('S'); 
	Nokia5110_SetCursor(8, 3);
	Nokia5110_OutChar(':'); 
	Nokia5110_SetCursor(9, 3);
	Nokia5110_OutDec(second); 
}

void Digital_minutes(unsigned int minutes)
{
	Nokia5110_SetCursor(6, 2);
	Nokia5110_OutChar('M'); 
	Nokia5110_OutChar('M'); 
	Nokia5110_SetCursor(5, 3);
	Nokia5110_OutChar(':'); 
	Nokia5110_SetCursor(6, 3);
	Nokia5110_OutDec(minutes); 
}

void Digital_hours(unsigned int hours)
{
	Nokia5110_SetCursor(3, 2);
	Nokia5110_OutChar('H'); 
	Nokia5110_OutChar('H');
	//Nokia5110_OutCharU(':'); 
	Nokia5110_SetCursor(3, 3);
	Nokia5110_OutDec(hours); 
}
