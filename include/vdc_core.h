// ====================================================================================
// vdc_core.h
//
// Functions and definitions which make working with the Commodore 128's VDC easier
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#ifndef _VDC_CORE_
#define _VDC_CORE_


#define VDC_BLACK	0
#define VDC_DGREY	1
#define VDC_DBLUE	2
#define VDC_LBLUE	3
#define VDC_DGREEN	4
#define VDC_LGREEN	5
#define VDC_DCYAN	6
#define VDC_LCYAN	7
#define VDC_DRED	8
#define VDC_LRED	9
#define VDC_DPURPLE	10
#define VDC_LPURPLE	11
#define VDC_DYELLOW	12
#define VDC_LYELLOW	13
#define VDC_LGREY	14
#define VDC_WHITE	15

#define VDC_CURSORMODE_SOLID      0
#define VDC_CURSORMODE_NONE       1
#define VDC_CURSORMODE_FAST       2
#define VDC_CURSORMODE_NORMAL     3

typedef unsigned char BYTE;
typedef unsigned char* BUFFER;

// Function Prototypes
void VDC_Init(void);
void VDC_DrawBox(BYTE x, BYTE y, BYTE width, BYTE height, BYTE borderStyle);
int VDC_PetsciiToScreenCode(int p);
int VDC_PetsciiToScreenCodeRvs(int p);
int VDC_RowColToAddress(int row, int col);
void VDC_Poke(int address,  unsigned char value);
int VDC_Peek(int address);
void VDC_BackColor(int color);
int VDC_CursorAt(int row, int col);
int VDC_PrintAt(int row, int col, char *text, int rvsOn);
int VDC_Clear(unsigned char val);
int VDC_BlockCopy(int sourceaddr, int destaddr, int length);
int VDC_Fill(int startAddr, int endAddr, unsigned char value);
void VDC_StashScreen(void);
int VDC_FetchScreen(void);
void VDC_SetCursorMode(int cursorMode);
int VDC_CopyVDCToMem(int vdcAddress, int memAddress, int length);
int VDC_CopyMemToVDC(int memAddress, int vdcAddress, int length);

#endif