//
//  semaphore.h
//  MasterSlave
//
//  Created by Przemyslaw Kobylanski on 26.11.2013.
//  Copyright (c) 2013 Przemyslaw Kobylanski. All rights reserved.
//

#ifndef MasterSlave_semaphore_h
#define MasterSlave_semaphore_h

/**
 Inicjowanie binarnego semafora wartością 0.
 
 Przykład użycia:
 @code
 binary_semaphore_initialize(semid);
 @endcode
 @param semid
        Identyfikator semafora.
*/

int binary_semaphore_initialize(int semid);

/**
 Oczekiwanie na binarny semafor. Blokuje aż wartość semafora będzie dodatnia, następnie
 zmniejsza ją o jeden.
 
 Przykład użycia:
 @code
 binary_semaphore_wait(semid);
 @endcode
 @param semid
        Identyfikator semafora.
*/

int binary_semaphore_wait(int semid, int which);

/**
 Zwolnij binarny semafor: zwiększ o jeden jego wartość. Powrót jest natychmiastowy.
 
 Przykład użycia:
 @code
 binary_semaphore_post(semid);
 @endcode
 @param semid
        Identyfikator semafora.
*/

int binary_semaphore_post(int semid, int which);

#endif
