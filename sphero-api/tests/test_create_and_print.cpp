/*
 * test_create_and_print.cpp
 *
 *  Created on: 17 mars 2015
 *      Author: slock
 */

#include <stddef.h>
#include <iostream>

using namespace std;

#include "../API-src/ClientCommandPacket.h"

int main(int argc, char **argv)
{
	ClientCommandPacket pack(0x02,0x20,0x00,0x05,NULL,false, false);
	cout  << pack.toString();
}



