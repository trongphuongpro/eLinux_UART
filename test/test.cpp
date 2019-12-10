#include <iostream>
#include <unistd.h>
#include <string.h>
#include "uart.h"

using namespace std;
using namespace BBB;


int main(int argc, const char** argv) {
	UART bus(UART::UART5, 9600);

	const char* s = "Hello, this's Beaglebone Black\n";

	while (1) {
		bus.writeBuffer(s, strlen(s));
		sleep(1);
	}
}