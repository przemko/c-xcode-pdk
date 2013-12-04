//
//  master.c
//  MasterSlave
//
//  Created by Przemyslaw Kobylanski on 26.11.2013.
//  Copyright (c) 2013 Przemyslaw Kobylanski. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "master.h"
#include "init.h"
#include "semaphore.h"
#include "logger.h"

void Master(int n, int* shared_memory, int semaphore_id)
{
	print_log(MASTERLOGID, "rozpoczynam pracę");
	
	print_log(MASTERLOGID, "idę spać na 10 sekund (po tym czasie wydam polecenie zakończenia pracy)");
	sleep(10); // kiedy proces śpi to nie upływa jego czas!
	
    print_log(MASTERLOGID, "piszę do wspólnej pamięci wartość 1 (HALT)");
	shared_memory[0] = 1;
	   
	print_log(MASTERLOGID, "kończę pracę");
	exit(0);
}
