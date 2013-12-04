//
//  master.h
//  MasterSlave
//
//  Created by Przemyslaw Kobylanski on 26.11.2013.
//  Copyright (c) 2013 Przemyslaw Kobylanski. All rights reserved.
//

#ifndef MasterSlave_master_h
#define MasterSlave_master_h

/**
 Zawiera kod procesu Master.
 
 Przykład użycia:
 @code
 Master(n, shared_memory, semaphore_id);
 @endcode
 @param n
        Ile procesów Slave jest do dyspozycji.
 @param shared_memory
        Adres początku współdzielonej pamięci.
 @param semaphore_id
        Identyfikator semafora.
*/

void Master(int n, int* shared_memory, int semaphore_id);	// główny proces zlecający zadanie

#endif
