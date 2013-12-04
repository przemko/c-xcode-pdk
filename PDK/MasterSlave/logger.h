//
//  logger.h
//  MasterSlave
//
//  Created by Przemyslaw Kobylanski on 26.11.2013.
//  Copyright (c) 2013 Przemyslaw Kobylanski. All rights reserved.
//

#ifndef MasterSlave_logger_h
#define MasterSlave_logger_h

#define INITLOGID   -2
#define MASTERLOGID -1

/**
 Drukuje komunikat poprzedzony godziną i nazwą procesu, który go dostarczył.
 
 Przykład użycia:
 @code
 print_log(MASTERLOGID, "kończę pracę");
 @endcode
 @param who
        Numer procesu, który zamieszcza komunikat: -2 Init, -1 Master, i >= 0 Slave[i].
 @param message
        Komunikat do zapisania w dzienniku.
 */

void print_log(int who, char* message);

#endif
