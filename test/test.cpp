#include <iostream>
#include <unistd.h>
#include <string.h>
#include "uart.h"
#include "crc32.h"

using namespace std;
using namespace BBB;


uint8_t preamble_1[4] = {0xAA, 0xBB, 0xCC, 0xDD};
uint8_t preamble_2[4] = {0xAB, 0xBC, 0xCD, 0xDE};

void sendMessage(UART& bus, const void* preamble, const void* data, uint32_t len) {
	crc32_t checksum = crc32_compute(data, len);

	bus.sendBuffer(preamble, 4);
	bus.send(0xAA);
	bus.send(0xBB);
	bus.send(len);
	bus.sendBuffer(data, len);
	bus.sendBuffer(&checksum, 4);

}


void printData(void* arg) {
	UART* bus = static_cast<UART*>(arg);

	printf(">> %c\n", bus->receive());
}


int main(int argc, const char** argv) {

	UART bus(UART::UART1, B115200);
	bus.onReceiveData(printData, &bus);

	const char* s[4] = {"Hello, this's Beaglebone Black", "trongphuongpro",
						"codelungtung", "uart testing"};

	//uint8_t buffer[100];
	
	puts("Reading test");
	
	while (1) {
		for (int i = 0; i < 4; i++) {
			bus.sendBuffer(s[i], strlen(s[i]));
		}
		sleep(2);
	}
}