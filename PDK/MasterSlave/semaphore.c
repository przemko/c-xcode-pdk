//
//  semaphore.c
//  MasterSlave
//
//  Created by Przemyslaw Kobylanski on 26.11.2013.
//  Copyright (c) 2013 Przemyslaw Kobylanski. All rights reserved.
//

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "semaphore.h"

int binary_semaphore_initialize(int semid)
{
    union semun argument;
    unsigned short values[2];
    values[0] = 0;
    values[1] = 0;
    argument.array = values;
    return semctl(semid, 1, SETALL, argument);
}

int binary_semaphore_wait(int semid, int which)
{
    struct sembuf operations[1];
    operations[0].sem_num = which;
    operations[0].sem_op = -1;
    operations[0].sem_flg = SEM_UNDO;
    return semop(semid, operations, 1);
}

int binary_semaphore_post(int semid, int which)
{
    struct sembuf operations[1];
    operations[0].sem_num = which;
    operations[0].sem_op = 1;
    operations[0].sem_flg = SEM_UNDO;
    return semop(semid, operations, 1);
}
