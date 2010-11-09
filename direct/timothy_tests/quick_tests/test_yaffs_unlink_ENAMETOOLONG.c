/*
 * YAFFS: Yet another FFS. A NAND-flash specific file system.
 *
 * Copyright (C) 2002-2010 Aleph One Ltd.
 *   for Toby Churchill Ltd and Brightstar Engineering
 *
 * Created by Timothy Manning <timothy@yaffs.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include "test_yaffs_unlink_ENAMETOOLONG.h"


static int handle=0;
int test_yaffs_unlink_ENAMETOOLONG(void){
	int output=0;
	int error_code=0;
	int x=0;
	int file_name_length=1000000;
	char file_name[file_name_length];
	
	strcat(file_name,YAFFS_MOUNT_POINT);
	for (x=strlen(YAFFS_MOUNT_POINT); x<file_name_length -1; x++){
		file_name[x]='a';
	}
	file_name[file_name_length-2]='\0';

	/*printf("path %s\n",path); */
	output=yaffs_unlink(file_name);
	if (output==-1){
		error_code=yaffs_get_error();
		//printf("EISDIR def %d, Error code %d\n", EISDIR,error_code);
		if (abs(error_code)== EISDIR){
			return 1;
		}
		else {
			printf("different error than expected\n");
			return -1;
		}
	}
	else {
		printf("directory unlinked opened.(which is a bad thing)\n");
		return -1;
	}
	/* the program should not get here but the compiler is complaining */
	return -1;
}
int test_yaffs_unlink_ENAMETOOLONG_clean(void){
	if (handle >=0){
		return yaffs_close(handle);
	}
	else {
		return 1;	/* the file failed to open so there is no need to close it*/
	}
}
