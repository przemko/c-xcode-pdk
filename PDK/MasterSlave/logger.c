//
//  logger.c
//  MasterSlave
//
//  Created by Przemyslaw Kobylanski on 26.11.2013.
//  Copyright (c) 2013 Przemyslaw Kobylanski. All rights reserved.
//

#include <sys/time.h>
#include <stdio.h>

#include "logger.h"

void print_log(int who, char* message)
{
	char buf[10];
	struct timeval tv;
	time_t curtime;
	
	gettimeofday(&tv, NULL);
	curtime = tv.tv_sec;
	
	strftime(buf, 10, "%T", localtime(&curtime));
	switch(who)
	{
		case -2:	printf("%s       Init:  %s\n", buf, message);
            break;
		case -1:	printf("%s     Master:  %s\n", buf, message);
            break;
		default: 	printf("%s  Slave[%2d]:  %s\n", buf, who, message);
	}
}
