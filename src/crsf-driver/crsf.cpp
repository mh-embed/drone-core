#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <ros/rosserial>

// Currently no clue how to actually import the ros serial libs or any serial
// lib for that matter...

#define CRSF_PORT    "/dev/serial0" // UART port on rPi
#define CRSF_BAUD    420000         // not exactly sure on baud but should work
#define CRSF_TIMEOUT serial::Timeout::simpleTimeout(1000) // timeout in ms

int run(int argc, char ** argv) {
	// Attempt to open the serial port
	serial::Serial uartPort(CRSF_PORT, CRSF_BAUD, CRSF_TIMEOUT);
	while(!uartPort.isOpen()) {
		usleep(10000); // check for uart every 10 ms
	}

	// Test the timeout, there should be 1 second between prints
	cout << "Timeout == 1000ms, asking for 1 more byte than written." << endl;
	while (count < 10) {
		size_t bytes_wrote = uartPort.write(test_string);

		string result = uartPort.read(test_string.length()+1);

		cout << "Iteration: " << count << ", Bytes written: ";
		cout << bytes_wrote << ", Bytes read: ";
		cout << result.length() << ", String read: " << result << endl;

		count += 1;
	}
	return 0;
}

int main(int argc, char** argv) {
	try {
		return run(argc, argv);
	} catch (std::exception &e) {
		std::cerr << "Unhandled Exception: " << e.what() << std::endl;
	}
}