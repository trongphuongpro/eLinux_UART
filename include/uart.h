#ifndef __UART__
#define __UART__

#include <string>

#define UART_PATH	"/dev/ttyS"

namespace BBB {

class UART {
public:
	enum PORT {UART1=1, UART2=2, UART4=4, UART5=5};

	UART(PORT, int baudrate, uint8_t=8);
	~UART();

	int write(uint8_t);
	int writeBuffer(const void*, uint32_t);

	uint8_t read();
	int readBuffer(void*, uint32_t);


private:
	std::string filename;
	int file;
	int baudrate;
	uint8_t datasize;
	PORT port;

	int open();
	void close();
};

} /* namespace BBB */

#endif /* __UART__ */