//
//  main.c
//  MasterSlave
//
//  Created by Przemyslaw Kobylanski on 26.11.2013.
//  Copyright (c) 2013 Przemyslaw Kobylanski. All rights reserved.
//

#include <stdio.h>

#include "init.h"

int main()
{
	Init(3); // Slave[0] = Producent, Slave[1] = Dostawca, Slave[2] = Konsument
	return 0;
}
