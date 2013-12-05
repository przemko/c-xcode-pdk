//
//  slave.c
//  MasterSlave
//
//  Created by Przemyslaw Kobylanski on 26.11.2013.
//  Copyright (c) 2013 Przemyslaw Kobylanski. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "slave.h"
#include "init.h"
#include "semaphore.h"
#include "logger.h"

void Slave(int id, int* shared_memory, int semaphore_id)
{
    int ok;
    char message[80];
    
    char *kim_jestem[3] = {"Producent", "Dostawca", "Konsument"};
    int ile_snu[3] = {1, 2, 3};
    
    sprintf(message, "rozpoczynam pracę jako %s", kim_jestem[id]);
	print_log(id, message);
	
    do {
        sprintf(message, "idę spać na %d s", ile_snu[id]);
        print_log(id, message);
        sleep(ile_snu[id]);
    
    
        switch(id)
        {
            case 0:
                print_log(id, "czekam na semafor dla fabryki");
                binary_semaphore_wait(semaphore_id, 0);
                print_log(id, "zablokowałem semafor dla fabryki");
                
                print_log(id, "produkuję jedną sztukę");
                shared_memory[1]++;
                
                sprintf(message, "stan: w fabryce = %d, w sklepie = %d", shared_memory[1], shared_memory[2]);
                print_log(id, message);
                
                print_log(id, "otwieram semafor dla fabryki");
                binary_semaphore_post(semaphore_id, 0);
                break;

            case 1:
                print_log(id, "czekam na semafor dla fabryki i sklepu");
                binary_semaphore_wait(semaphore_id, 0);
                binary_semaphore_wait(semaphore_id, 1);
                print_log(id, "zablokowałem oba semafory");
                
                if(shared_memory[1] > 0)
                {
                    print_log(id, "zabieram jedną sztukę z frabryki");
                    shared_memory[1]--;
                
                    print_log(id, "dostarczam jedną sztukę do sklepu");
                    shared_memory[2]++;
                    
                    sprintf(message, "stan: w fabryce = %d, w sklepie = %d", shared_memory[1], shared_memory[2]);
                    print_log(id, message);

                }
                
                print_log(id, "otwieram oba semafory");
                binary_semaphore_post(semaphore_id, 0);
                binary_semaphore_post(semaphore_id, 1);
                break;

            case 2:
                print_log(id, "czekam na semafor dla sklepu");
                binary_semaphore_wait(semaphore_id, 1);
                print_log(id, "zablokowałem semafor dla sklepu");
                
                if(shared_memory[2] > 0)
                {
                    print_log(id, "konsumuję jedną sztukę");
                    shared_memory[2]--;
                    
                    sprintf(message, "stan: w fabryce = %d, w sklepie = %d", shared_memory[1], shared_memory[2]);
                    print_log(id, message);

                }
                
                print_log(id, "otwieram semafor dla sklepu");
                binary_semaphore_post(semaphore_id, 1);
        }
        
        print_log(id, "czy we współdzielonej pamięci jest polecenie HALT?");
        ok = shared_memory[0] == 1;
        
        
    } while (!ok);
	
	print_log(id, "odczytałem ze wspólnej pamięci polecenie HALT");
	
	print_log(id, "kończę pracę");
	exit(0);
}
