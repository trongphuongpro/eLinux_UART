/** 
 * @file uart.h
 * @brief This file contains class UART - a wrapper for Linux's UART C-library
 * @author Nguyen Trong Phuong (aka trongphuongpro)
 * @date December 29, 2019
 */

#ifndef __UART__
#define __UART__

#include <string>

/**
 * @brief Path to UART character files
 */
#define UART_PATH	"/dev/ttyS"

/**
 * @brief namespace for BeagleBone Black
 */
namespace BBB {

typedef void (*CallbackType)(void*);

/**
 * @brief Class UART contains functions and variables
 * using for UART communication.
 */
class UART {
public:

	/**
	 * @brief enum PORT contains number of UART bus.
	 */
	enum PORT {UART1=1, UART2=2, UART4=4, UART5=5};


	/**
	 * Constructor
	 * @param bus UART bus number;
	 * @param baudrate UART baudrate;
	 * @param bit data size: 5,6,7 or 8 bit
	 */
	UART(PORT bus, int baudrate, uint8_t bit=8);


	/**
	 * Destructor
	 */
	~UART();


	/**
	 * @brief Transmit one byte via UART bus
	 * @param data one byte data.
	 * @return 0: OK, 1: Error.
	 */
	int write(uint8_t data);


	/**
 	 * @brief Transmit a byte array via UART bus
 	 * @param data pointer to data.
 	 * @param len the length of data in byte.
 	 * @return 0: OK, 1: Error.
 	 */
	int writeBuffer(const void* data, uint32_t len);


	/** 
	 * @brief Get one byte from UART bus
	 * @return one byte.
	 */
	int read();


	/** 
	 * @brief Get one byte from UART bus
	 * @param data pointer to RX buffer;
	 * @parem the number of bytes will be received.
	 * @return 0: OK, -1: Error.
	 */	
	int readBuffer(void* data, uint32_t len);


	/**
	 * @brief Callback for incoming data
	 * @param callback callback function name;
	 * @param arg argument of callback function.
	 * @return nothing.
	 */
	void onReceiveData(void (*callback)(void*), void *arg=NULL);


private:

	/** 
	 * Name of UART character device file
	 */
	std::string filename;


	/** 
	 * File descriptor of UART character device file
	 */
	int file;


	/** 
	 * UART baudrate
	 */
	int baudrate;


	/** 
	 * UART datasize
	 */
	uint8_t datasize;


	/** 
	 * UART bus number
	 */
	PORT port;

	
	/**
	 * @brief Polling for incoming data
	 * @return 0: OK, -1: Error.
	 */
	int waitData();


	/**
	 * state of thread
	 */
	bool threadRunning;


	/**
	 * callback function on incoming data
	 */
	CallbackType callbackFunction;


	/**
	 * argument for callback function
	 */
	void* callbackArgument;


	/**
	 * thread ID
	 */
	pthread_t thread;


	/** 
	 * @brief Open UART character device file 
	 * and setup baudrate, datasize
	 * @return 0: OK;
	 * @return -1: Error.
	 */	
	int open();


	/** 
	 * @brief Close UART character device file 
	 * @return nothing.
	 */		
	void close();


	/**
	 * @brief Friend function used for multi-threading
	 * @param value void pointer to argument
	 * @return NULL
	 */
	friend void *threadedPoll(void* arg);
	
};


void *threadedPoll(void* arg);

} /* namespace BBB */

#endif /* __UART__ */