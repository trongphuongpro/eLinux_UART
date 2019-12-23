#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include "uart.h"


using namespace std;
using namespace BBB;


UART::UART(UART::PORT port, int baudrate, uint8_t datasize) {
	this->port = port;
	this->baudrate = baudrate;
	this->datasize = datasize;
	this->filename = UART_PATH + to_string(port);
	this->file = -1;

	open();
}


UART::~UART() {
	if (this->file != -1)
		close();
}


int UART::open() {
	if ((this->file = ::open(this->filename.c_str(), O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
		perror("UART: Failed to open the file.");
		return -1;
	}

	struct termios options;

	tcgetattr(this->file, &options);
	options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
	options.c_iflag = IGNPAR | ICRNL;

	tcflush(this->file, TCIFLUSH);
	tcsetattr(this->file, TCSANOW, &options);

	return 0;
}


void UART::close() {
	::close(this->file);
	this->file = -1;
}


int UART::write(uint8_t data) {
	if (::write(this->file, &data, 1) < 0) {
		perror("UART: Failed to write to the output");
		return -1;
	}
	return 0;
}


int UART::writeBuffer(const void* buffer, uint32_t len) {
	if (::write(this->file, buffer, len) < 0) {
		perror("UART: Failed to write to the output");
		return -1;
	}
	return 0;
}


uint8_t UART::read() {
	uint8_t data;

	if (::read(this->file, &data, 1) < 0) {
		perror("UART: Failed to read from the input");
		return 255;
	}
	return data;
}