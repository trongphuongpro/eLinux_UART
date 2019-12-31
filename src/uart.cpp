/** 
 * @file uart.cpp
 * @brief This file contains implementation for class UART - a wrapper for
 * Linux's UART C-library
 * @author Nguyen Trong Phuong (aka trongphuongpro)
 * @date December 29, 2019
 */


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
	options.c_cflag = CS8 | CREAD | CLOCAL;
	options.c_iflag = IGNPAR | ICRNL;

	options.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);

	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);

	tcflush(this->file, TCIFLUSH);
	tcsetattr(this->file, TCSANOW, &options);

	return 0;
}


void UART::close() {
	::close(this->file);
	this->file = -1;
}


int UART::write(uint8_t data) {
	int ret;

	if ((ret=::write(this->file, &data, 1)) < 0) {
		perror("UART: Failed to write to the output");
	}

	return ret;
}


int UART::writeBuffer(const void* buffer, uint32_t len) {
	int ret;

	if ((ret=::write(this->file, buffer, len)) < 0) {
		perror("UART: Failed to write to the output");
	}

	return ret;
}


int UART::read() {
	uint8_t data;

	if (::read(this->file, &data, 1) < 0) {
		//perror("UART: Failed to read from the input");
		return -1;
	}

	return data;
}


int UART::readBuffer(void* buffer, uint32_t len) {
	int ret;

	if ((ret=::read(this->file, buffer, len)) < 0) {
		//perror("UART: Failed to read from the input");
	}

	return ret;
}