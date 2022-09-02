#include <iostream>
#include <thread>
#include <string>
#include "planta.h"
extern bool s_finished = false;
extern Sensores mySensors;

int main()
{
	using namespace std;
	std::string input_char = "";
	std::thread worker(planta);



	while (input_char != "Q") {
		cin >> input_char;
		if (input_char == "LT01") {
			mySensors.LT01 = true;
		}
		else if (input_char ==  "FS01"){
			mySensors.FS01 = true;
		}
		else if (input_char == "LSL02") {
			mySensors.LSL02 = false;
		}
		else if (input_char == "LSL01") {
			mySensors.LSL01 = true;
		}
	}
	s_finished = true;
	worker.join();
	std::cout << "Finished program, press anything to leave " << std::endl << std::flush;
	cin >> input_char;
	return 0;
}