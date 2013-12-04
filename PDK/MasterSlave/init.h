//
//  init.h
//  MasterSlave
//
//  Created by Przemyslaw Kobylanski on 26.11.2013.
//  Copyright (c) 2013 Przemyslaw Kobylanski. All rights reserved.
//

#ifndef MasterSlave_init_h
#define MasterSlave_init_h

#define MINNUMOFSLAVES 1
#define MAXNUMOFSLAVES 10

/**
 Tworzy współdzieloną pamięć, uruchamia proces Master i n procesów Slave, czeka na zakończenie procesów potomnych a na zakończenie zwalnia współdzieloną pamięć.
 
 Przykład użycia:
 @code
 Init(n);
 @endcode
 @param n
        Liczba tworzonych procesów Slave.
*/

void Init(int n); 							// utworzenie Master i n Slave'ów

#endif
