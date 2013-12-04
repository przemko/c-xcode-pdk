//
//  slave.h
//  MasterSlave
//
//  Created by Przemyslaw Kobylanski on 26.11.2013.
//  Copyright (c) 2013 Przemyslaw Kobylanski. All rights reserved.
//

#ifndef MasterSlave_slave_h
#define MasterSlave_slave_h

/**
 Zawiera kod procesu Slave.
 
 Przykład użycia:
 @code
 Slave(id, shared_memory, semaphore_id);
 @endcode
 @param id
        Identyfikator procesu (nieujemna liczba całkowita).
 @param shared_memory
        Adres początku współdzielonej pamięci.
 @param semaphore_id
        Identyfikator semafora.
*/

void Slave(int id, int* shared_memory, int semaphore_id);	// proces wykonujący zadanie

#endif
