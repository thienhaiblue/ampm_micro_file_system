/* ampm_ff.h
 *
 * Copyright (C) AMPM ELECTRONICS EQUIPMENT TRADING COMPANY LIMITED.,
 * Email: thienhaiblue@ampm.com.vn or thienhaiblue@mail.com
 *
 * This file is part of ampm_open_lib
 *
 * ampm_open_lib is free software; you can redistribute it and/or modify.
 *
 * Add: 143/36/10 , Lien khu 5-6 street, Binh Hung Hoa B Ward, Binh Tan District , HCM City,Vietnam
 */

#include <stdio.h>
#include <string.h>

#include "ampm_ff/ampm_ff.h"

AMPM_FIL file;

AMPM_FIL*  ampm_fopen(const char * filename, const char * mode)
{
	if(ampm_f_open(&file,(char *)filename,AMPM_FA_READ) == FR_OK)
		return &file;
	return 0;
}


AMPM_FRESULT  ampm_fread (
	char* ptr,		/* Pointer to data buffer */
	uint32_t size,		/* Number of bytes to read */
	uint32_t count,		
	AMPM_FIL* fil 		/* Pointer to the file object */
)
{
	uint32_t bytes;
	return ampm_f_read(fil,ptr,size,&bytes);
}


AMPM_FRESULT  ampm_fwrite (
	char* ptr,		/* Pointer to data buffer */
	uint32_t size,		/* Number of bytes to read */
	uint32_t count,		
	AMPM_FIL* fil 		/* Pointer to the file object */
)
{
	uint32_t bytes;
	return ampm_f_write(fil,ptr,size,&bytes);
}


AMPM_FRESULT  ampm_fseek (
	AMPM_FIL* fil, 		/* Pointer to the file object */
	uint32_t offset,		/* File pointer from top of file */
	uint8_t origin
)
{
	return ampm_f_lseek(fil,offset);
}


