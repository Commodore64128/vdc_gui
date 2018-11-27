// ====================================================================================
// vdc_core.c
//
// Functions and definitions which make working with the Commodore 128's VDC easier
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_gui.h"

void VDC_Init(void)
{
	printf("%c%c",0x0E,147); // Up/Lowercase, clr
	fast();
}

void VDC_DrawBox(BYTE x, BYTE y, BYTE width, BYTE height, BYTE borderStyle)
{
	char borderChars[8];
	int i;
	
	borderChars[0] = VDC_PetsciiToScreenCode(240);
	borderChars[1] = VDC_PetsciiToScreenCode(238);
	borderChars[2] = VDC_PetsciiToScreenCode(192);
	borderChars[3] = VDC_PetsciiToScreenCode(192);
	borderChars[4] = VDC_PetsciiToScreenCode(125);
	borderChars[5] = VDC_PetsciiToScreenCode(125);
	borderChars[6] = VDC_PetsciiToScreenCode(237);
	borderChars[7] = VDC_PetsciiToScreenCode(253);

	/* Substitute the passed border character if not a line */
	if(borderStyle != VDC_WIN_BORDER_LINE)
		for(i=0;i<8;i++)
			borderChars[i] = VDC_PetsciiToScreenCode(borderStyle);

	/* Top left corner */
	VDC_Poke(VDC_RowColToAddress(y, x), borderChars[0]);
	
	/* Top right corner */
	VDC_Poke(VDC_RowColToAddress(y,x + width - 1), borderChars[1]);
	
	/* Top and Bottom Border */
	for(i = 1; i < width-1; i++)
	{
		VDC_Poke(VDC_RowColToAddress(y, x+i), borderChars[2]);
		VDC_Poke(VDC_RowColToAddress(y + height-1, x+i), borderChars[3]);
	}

	for(i = 1; i < height -1; i++)
	{	
		/* Left Border */
		VDC_Poke(VDC_RowColToAddress(y+i, x), borderChars[4]);

		/* Right Border */
		VDC_Poke(VDC_RowColToAddress(y+i, x+width-1), borderChars[5]);
	}

	/* Bottom left and right corners */
	VDC_Poke(VDC_RowColToAddress(y + height-1,x), borderChars[6]);
	VDC_Poke(VDC_RowColToAddress(y + height-1,x + width-1), borderChars[7]);

}

int VDC_PetsciiToScreenCode(int p)
{
	/* Convert Petscii values to screen code values */
	if(p >= 0 && p <32)	p = p + 128;
	else if (p > 63  && p < 96 ) p = p - 64;
	else if (p > 95  && p < 128) p = p - 32;
	else if (p > 127 && p < 160) p = p + 64;
	else if (p > 161 && p < 192) p = p - 64;
	else if (p > 191 && p < 254) p = p - 128;
	else if (p == 255) p = 94;
	
	return p;
}

int VDC_PetsciiToScreenCodeRvs(int p)
{
	/* Convert Petscii values to screen code values */
	if(p >= 0 && p <32)	p = p + 128;
	else if (p > 31  && p < 64 ) p = p + 128;
	else if (p > 63  && p < 96 ) p = p + 64;
	else if (p > 95  && p < 128) p = p - 32;
	else if (p > 127 && p < 160) p = p + 64;
	else if (p > 161 && p < 192) p = p - 64;
	else if (p > 191 && p < 224) p = p - 128;
	else if (p > 223 && p < 255) p = p - 128;
	else if (p == 255) p = 94;

	return p;
}

int VDC_RowColToAddress(int row, int col)
{
	/* Function returns a VDC memory address for a given row and column */

	int addr;
	addr = row * 80 + col;

	if (addr > -1 && addr < 2000)
		return addr;
	else
		return -1;
}


void VDC_Poke(int address,  unsigned char value)
{
	/* Hi-byte of the address to register 18 */
	VDC.ctrl = 18;
	VDC.data = (address/256) & 255;

	/* Lo-byte of the address to register 19 */
	VDC.ctrl = 19;
	VDC.data = address & 255;

	/* Data byte to data register */
	VDC.ctrl = 31;
	VDC.data = value;
}


int VDC_Peek(int address)
{
	/* Hi-byte of the address to register 18 */
	VDC.ctrl = 18;
	VDC.data = (address/256) & 255;

	/* Lo-byte of the address to register 19 */
	VDC.ctrl = 19;
	VDC.data = address & 255;

	VDC.ctrl = 31;

	return VDC.data;
}


void VDC_BackColor(int color)
{
	int regval;

	/* Talking to register 26 */
	VDC.ctrl = 26;
	regval = VDC.data;

	VDC.ctrl = 26;
	VDC.data = (regval & 240) + color;
}

int VDC_CursorAt(int row, int col)
{
	int address;

	if(row < 0 || row > 24 || col < 0 || col > 79)
		return -1;

	address = VDC_RowColToAddress(row, col);

	VDC.ctrl = 14;
	VDC.data = (address/256) & 255;

	VDC.ctrl = 15;
	VDC.data = address & 255;

	return 0;
}
int VDC_PrintAt(int row, int col, char *text, int rvsOn)
{
	int x;
	int address;

	address = VDC_RowColToAddress(row, col);

	if (address != -1)
	{
		x = 0;
		while(text[x] != 0)
		{
			char c = text[x];

			if (rvsOn == 1)
				VDC_Poke(address, VDC_PetsciiToScreenCodeRvs(c));
			else
				VDC_Poke(address, VDC_PetsciiToScreenCode(c));
			
			address++;
			x++;
		}
		return x;
	}
	else
		return -1;
}

int VDC_Clear(unsigned char val)
{
	int i;

	/* Hi-byte of the start address to register 18 */
	VDC.ctrl = 18;
	VDC.data = 0;

	/* Lo-byte of the start address to register 19 */
	VDC.ctrl = 19;
	VDC.data = 0;

	/* Clear the copy bit of register 24 (fill mode) */
	VDC.ctrl = 24;
	VDC.data = VDC.data & 127;

	/* Write the first clear (zero) byte to the data register */
	VDC.ctrl = 31;
	VDC.data = val;

	/* Talk to the word count register ... */
	VDC.ctrl = 30;

	/* 8 255-byte pages to clear (2047 bytes) */
	for(i = 0; i < 8; i++)
		VDC.data = 255;

	return 0;
}


int VDC_BlockCopy(int sourceaddr, int destaddr, int length)
{
	if (length > 255)
		return -1;

	/* Hi-byte of the destination address to register 18 */
	VDC.ctrl = 18;
	VDC.data = (destaddr/256) & 255;

	/* Lo-byte of the destination address to register 19 */
	VDC.ctrl = 19;
	VDC.data = destaddr & 255;

	/* Hi-byte of the source address to block copy source register 32 */
	VDC.ctrl = 32;
	VDC.data = (sourceaddr/256) & 255;
	
	/* Lo-byte of the source address to block copy source register 33 */
	VDC.ctrl = 33;
	VDC.data = sourceaddr & 255;
	
	/* Set the copy bit (bit 7) of register 24 (block copy mode) */
	VDC.ctrl = 24;
	VDC.data = VDC.data | 128;

	/* Number of bytes to copy */
	VDC.ctrl = 30;
	VDC.data = length+1;  // -1 ?

	return length;
}


int VDC_Fill(int startAddr, int endAddr, unsigned char value)
{
	while(startAddr <= endAddr)
		VDC_Poke(startAddr++,value);

	return 0;
}
void VDC_StashScreen(void)
{
	/* Function that will copy the screen contents to VDC buffer */
	int sourceAddr = 0;
	int destAddr = 4096;
	
	while(sourceAddr < 2048)
	{
		VDC_BlockCopy(sourceAddr, destAddr, 255);
		sourceAddr += 256;
		destAddr += 256;
	};
/*
	VDC_BlockCopy(0, 4096, 255);
	VDC_BlockCopy(256, 4352, 255);
	VDC_BlockCopy(512, 4608, 255);
	VDC_BlockCopy(768, 4864, 255);
	VDC_BlockCopy(1024, 5120, 255);
	VDC_BlockCopy(1280, 5376, 255);
	VDC_BlockCopy(1536, 5632, 255);
	VDC_BlockCopy(1792, 5888, 255); */
}

int VDC_FetchScreen(void)
{
	/* Function that will restore the screen contents from the VDC buffer */

	int sourceAddr = 4096;
	int destAddr = 0;

	while(sourceAddr < 6144)
	{
		VDC_BlockCopy(sourceAddr, destAddr, 255);
		sourceAddr += 256;
		destAddr += 256;
	};
/*
	VDC_BlockCopy(4096, 0, 255);
	VDC_BlockCopy(4352, 256, 255);
	VDC_BlockCopy(4608, 512, 255);
	VDC_BlockCopy(4864, 768, 255);
	VDC_BlockCopy(5120, 1024, 255);
	VDC_BlockCopy(5376, 1280, 255);
	VDC_BlockCopy(5632, 1536, 255);
	VDC_BlockCopy(5888, 1792, 255);*/

	return 0;
}

void VDC_SetCursorMode(int cursorMode)
{
	if (cursorMode > VDC_CURSORMODE_NORMAL || cursorMode < VDC_CURSORMODE_SOLID)
		return;

	/* Hi-byte of the address to register 18 */
	VDC.ctrl = 18;
	VDC.data = 0;

	/* Lo-byte of the address to register 19 */
	VDC.ctrl = 19;
	VDC.data = 0;

	/* Set cursor mode via register 10 */
	VDC.ctrl = 10;
	VDC.data = cursorMode;

}

int VDC_CopyVDCToMem(int vdcAddress, int memAddress, int length)
{
	int x;

	for(x=0; x< length; x++)
		POKE(memAddress+x, VDC_Peek(vdcAddress + x));

	return 0;
}

int VDC_CopyMemToVDC(int memAddress, int vdcAddress, int length)
{
	int x;

	for(x=0; x< length; x++)
		VDC_Poke(vdcAddress+x, PEEK(memAddress+x)); 

	return 0;
}

