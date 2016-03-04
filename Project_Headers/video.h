/*
 * video.h
 *
 *  Created on: Dec 17, 2015
 *      Author: lenovo
 */

#ifndef VIDEO_H_
#define VIDEO_H_

#define byte unsigned char
#define word unsigned int

#define ROWS 80
#define COLUMNS 100

extern byte fieldover;
extern byte a_pix[ROWS][COLUMNS];

void FieldInputCapture(void);
void RowInputCapture(void);
void PixelInputCapture(void);
extern void VideoCopy(byte a[ROWS][COLUMNS],byte b[ROWS][COLUMNS]);

#endif /* VIDEO_H_ */
