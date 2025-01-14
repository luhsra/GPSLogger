#include <Adafruit_GFX.h>

#include "TimeFont.h"

// This font is based on Bodoni MT 24pt, slightly corrected in picture editor

const uint8_t TimeFontBitmaps[] = {
	0x07, 0x80, 0x73, 0x83, 0x87, 0x0e, 0x1c, 0x78, 0x79, 0xe1, 0xe7, 0x87, 0xbe, 0x1f, 0xf8, 0x7f, 0xe1, 0xff, 0x87, 0xfe, 0x1f, 0xf8, 0x7f, 0xe1, 0xff, 0x87, 0xde, 0x1e, 0x78, 0x79, 0xe1, 0xe3, 0x87, 0x06, 0x18, 0x0c, 0xc0, 0x1e, 0x00,    //0x30 '0'
	0xff, 0x80, 0x7c, 0x03, 0xe0, 0x1f, 0x00, 0xf8, 0x07, 0xc0, 0x3e, 0x01, 0xf0, 0x0f, 0x80, 0x7c, 0x03, 0xe0, 0x1f, 0x00, 0xf8, 0x07, 0xc0, 0x3e, 0x01, 0xf0, 0x0f, 0x80, 0x7c, 0x03, 0xe0, 0x1f, 0x00, 0xf8, 0x7f, 0xfc,    //0x31 '1'
	0x0f, 0xc0, 0x43, 0xc2, 0x0f, 0x9c, 0x1e, 0x7c, 0x7d, 0xf1, 0xf7, 0xc7, 0xce, 0x1f, 0x00, 0x7c, 0x01, 0xe0, 0x0f, 0x00, 0x38, 0x01, 0xc0, 0x0e, 0x00, 0x70, 0x03, 0x01, 0x18, 0x04, 0xc0, 0x17, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,    //0x32 '2'
	0x0f, 0x80, 0xc7, 0x87, 0x8f, 0x1f, 0x3e, 0x7c, 0xf8, 0xe3, 0xe0, 0x0f, 0x80, 0x3c, 0x00, 0xf0, 0x07, 0x01, 0xe0, 0x00, 0x78, 0x00, 0xf8, 0x01, 0xe0, 0x07, 0xdc, 0x1f, 0xf8, 0x7f, 0xe1, 0xff, 0x87, 0x98, 0x3e, 0x60, 0xf0, 0x7f, 0x00,    //0x33 '3'
	0x00, 0x70, 0x00, 0xe0, 0x03, 0xc0, 0x0f, 0x80, 0x1f, 0x00, 0x7e, 0x01, 0x7c, 0x02, 0xf8, 0x09, 0xf0, 0x13, 0xe0, 0x47, 0xc1, 0x0f, 0x82, 0x1f, 0x08, 0x3e, 0x60, 0x7c, 0xff, 0xff, 0x01, 0xf2, 0x03, 0xe4, 0x07, 0xc0, 0x0f, 0x80, 0x1f, 0x01, 0xff, 0x80,    //0x34 '4'
	0x00, 0x08, 0xff, 0xe3, 0xff, 0x8f, 0xfc, 0x3f, 0xf0, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0xbf, 0x03, 0x1f, 0x00, 0x3e, 0x00, 0x78, 0x01, 0xf0, 0x07, 0xdc, 0x1f, 0xf8, 0x7f, 0xe1, 0xff, 0x87, 0x98, 0x3c, 0x30, 0xe0, 0x7e, 0x00,    //0x35 '5'
	0x00, 0x70, 0x0f, 0x00, 0x70, 0x07, 0x80, 0x1e, 0x00, 0xf0, 0x07, 0xc0, 0x1f, 0x00, 0x7b, 0xc3, 0xf3, 0xcf, 0x87, 0xbe, 0x1e, 0xf8, 0x7f, 0xe1, 0xff, 0x87, 0xfe, 0x1f, 0x78, 0x7d, 0xe1, 0xe7, 0x87, 0x8e, 0x1c, 0x1c, 0xe0, 0x1f, 0x00,    //0x36 '6'
	0x7f, 0xfe, 0xff, 0xfd, 0xff, 0xf7, 0xff, 0xcc, 0x00, 0x90, 0x02, 0x20, 0x08, 0x00, 0x10, 0x00, 0x40, 0x01, 0x00, 0x02, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x60, 0x00, 0xc0, 0x03, 0x80, 0x07, 0x00, 0x1f, 0x00, 0x3e, 0x00, 0x7c, 0x00, 0xf8, 0x00, 0xe0, 0x00,    //0x37 '7'
	0x0f, 0xc0, 0x73, 0x83, 0xcf, 0x1f, 0x3e, 0x7c, 0xf9, 0xf3, 0xe7, 0xcf, 0x9f, 0x3e, 0x3c, 0xf0, 0x73, 0x00, 0x70, 0x07, 0x38, 0x78, 0x79, 0xe1, 0xef, 0x87, 0xfe, 0x1f, 0xf8, 0x7f, 0xe1, 0xf7, 0x87, 0xde, 0x1e, 0x3c, 0xf0, 0x3f, 0x00,    //0x38 '8'
	0x0f, 0x80, 0x73, 0x83, 0x87, 0x1e, 0x1e, 0x78, 0x7b, 0xe1, 0xef, 0x87, 0xfe, 0x1f, 0xf8, 0x7f, 0xe1, 0xf7, 0x87, 0xde, 0x1f, 0x3c, 0xfc, 0x3d, 0xe0, 0x07, 0x80, 0x3e, 0x00, 0xf0, 0x03, 0x80, 0x1e, 0x00, 0xe0, 0x0f, 0x00, 0xe0, 0x00,    //0x39 '9'
	0x77, 0xff, 0xf7, 0x00, 0x00, 0x77, 0xff, 0xf7, 0x00,    //0x3a ':'
	0x78, 0x2f, 0xcf, 0x3f, 0x41, 0xe0,    ////0x3b '~'  - remapped symbol
	0x00	////0x3c ' '  - remapped symbol
}; //409 bytes

const GFXglyph TimeFontGlyphs[] =
{
	// TO_not_DO: Add space symbol
	0, 14, 22, 16, 1, -22,		//0x30 '0'
	39, 13, 22, 16, 2, -22,		//0x31 '1'
	75, 14, 22, 16, 1, -22,		//0x32 '2'
	114, 14, 22, 16, 1, -22,    //0x33 '3'
	153, 15, 22, 16, 0, -22,    //0x34 '4'
	195, 14, 22, 16, 1, -22,    //0x35 '5'
	234, 14, 22, 16, 1, -22,    //0x36 '6'
	273, 15, 22, 16, 1, -22,    //0x37 '7'
	315, 14, 22, 16, 1, -22,    //0x38 '8'
	354, 14, 22, 16, 1, -22,    //0x39 '9'
	393, 5, 13, 9, 2, -17,		//0x3a ':'
	402, 11, 4, 12, 0, -12,		//0x3b - remapped symbol '~'
	408, 1, 1, 12, 0, -12,		//0x3c - remapped symbol ' '
};

const GFXfont TimeFont =
{
	(uint8_t  *)TimeFontBitmaps,
	(GFXglyph *)TimeFontGlyphs,
	0x30,	// First symbol ord
	0x3c,	// Last symbol ord
	22		// Line height
};


