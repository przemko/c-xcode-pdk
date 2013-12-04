//
//  init.c
//  MasterSlave
//
//  Created by Przemyslaw Kobylanski on 26.11.2013.
//  Copyright (c) 2013 Przemyslaw Kobylanski. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "init.h"
#include "semaphore.h"
#include "logger.h"
#include "master.h"
#include "slave.h"

void Init(int n)
{
    int semaphore_id;
    
	int segment_id;
	int* shared_memory;
	const int shared_segment_size = 0x0001;
	
	pid_t child_pid;
	pid_t pids[n+1];
	int child_status;
	int i;
	char message[80];
    
    // inicjowanie semafora
    
    print_log(INITLOGID, "tworzę dwa semafory");
    semaphore_id = semget(IPC_PRIVATE, 2,
                          IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); // sprawdzić stałe!!!
    
    print_log(INITLOGID, "inicjuję semafory wartością 0 (zamknięte)");
    binary_semaphore_initialize(semaphore_id);
    
	// inicjowanie współdzielonej pamięci
	
	print_log(INITLOGID, "rozpoczynam inicjowanie wspólnej pamięci");
	
	segment_id = shmget(IPC_PRIVATE, shared_segment_size,
						IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	
	shared_memory = (int*) shmat(segment_id, 0, 0);
	
	print_log(INITLOGID, "piszę do współdzielonej pamięci wartość 0 (RUN)");
	shared_memory[0] = 0;
	
	// tworzenie procesu Master
	
	print_log(INITLOGID, "tworzę proces Master");
	
	child_pid = fork();
	if(child_pid == 0)
		Master(n, shared_memory, semaphore_id); // musi kończyć się exit() a nie return
	
	pids[0] = child_pid;
	sprintf(message, "utworzono proces Master z PID = %d", (int) pids[0]);
	print_log(INITLOGID, message);
	
	// tworzenie procesów Slave[0], ..., Slave[n-1]
	
	print_log(INITLOGID, "tworzę procesy Slave");
	
	for(i = 0; i < n; i++)
	{
		child_pid = fork();
		if(child_pid == 0)
			Slave(i, shared_memory, semaphore_id); // musi kończyć się exit() a nie return
        
		pids[i+1] = child_pid;
		sprintf(message, "utworzono proces Slave[%2d] z PID = %d", i, (int) pids[i+1]);
		print_log(INITLOGID, message);
	}
	
    // zwolnienie semafora
    
    print_log(INITLOGID, "otwieram semafory");
    binary_semaphore_post(semaphore_id, 0); // UWAGA: jeśli zakomentować to procesy będą czekać!
    binary_semaphore_post(semaphore_id, 1);
    
	// oczekiwanie na zakończenie procesów potomnych
	
	print_log(INITLOGID, "oczekuję na zakończenie procesów potomnych");
	
	for(i = 0; i < n+1; i++)
	{
		while(waitpid(pids[i], &child_status, 0) == -1);
		sprintf(message, "proces PID = %d zakończył się", (int) pids[i]);
		print_log(INITLOGID, message);
	}
	
	print_log(INITLOGID, "wszystkie procesy potomne zakończyły się");
	
	// odłączenie i usunięcie współdzielonej pamięci
	
	shmdt(shared_memory);
	print_log(INITLOGID, "współdzielona pamięć została odłączona");
	shmctl(segment_id, IPC_RMID, 0);
	print_log(INITLOGID, "usunięto segment współdzielonej pamięci");
	
    // usunięcie semafora
    
    union semun ignored_argument;
    semctl(semaphore_id, 1, IPC_RMID, ignored_argument);
    print_log(INITLOGID, "usunięto semafor");
    
	// zakończenie pracy
	
	print_log(INITLOGID, "kończę pracę");
}

