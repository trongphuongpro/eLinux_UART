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

	bus.writeBuffer(preamble, 4);
	bus.write(0xAA);
	bus.write(0xBB);
	bus.write(len);
	bus.writeBuffer(data, len);
	bus.writeBuffer(&checksum, 4);

}


int main(int argc, const char** argv) {

	crc32_init();

	UART bus(UART::UART1, 9600);

	const char* s[4] = {"Hello, this's Beaglebone Black", "trongphuongpro",
						"codelungtung", "uart testing"};
	
	while (1) {
		puts("sending...");

		for (int i = 0; i < 4; i++) {
			sendMessage(bus, preamble_1, s[i], strlen(s[i]));
			sleep(1);
		}

		for (int i = 0; i < 4; i++) {
			sendMessage(bus, preamble_2, s[i], strlen(s[i]));
			sleep(1);
		}

		puts("----");
		sleep(3);
	}
}