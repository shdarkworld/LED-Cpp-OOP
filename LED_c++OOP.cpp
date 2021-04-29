// Code to control LED3 usr (C++ OOP)
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstring>
using namespace std;

#define LED3 "/sys/class/leds/beaglebone:green:usr3"	// path

class LED{
	private:
		string path;
		virtual void writeLED(string filename, string value);
		virtual void removeTrigger();
	public:
		virtual void On();
		virtual void Off();
		virtual void flash();
};

void LED::writeLED(string filename, string value)
{
	// Writes the passed value to the file in the path
	ostringstream s;
	s << LED3;
	path = string(s.str());
	ofstream fs;
	fs.open((path + filename).c_str());
	fs << value;
	fs.close();
}

void LED::removeTrigger()
{
	// Writes "none" in trigger
	writeLED("/trigger", "none");
}

void LED::On()
{
	// Turns on LED3
	cout << "LED on" << endl;
	removeTrigger();
	writeLED("/brightness", "1");
}

void LED:: Off()
{
	// Turns off LED3
	cout << "LED off" << endl;
	removeTrigger();
	writeLED("/brightness", "0");
}

void LED::flash()
{
	// LED3 starts flashing 50ms on, 50ms off (needs sudo)
	cout << "LED Flashing" << endl;
	writeLED("/trigger", "timer");
	writeLED("/delay_on", "50");
	writeLED("/delay_off", "50");
}


int main(int argc, char* argv[])
{
	// Checks if number of arguments are right
	if(argc != 2){
		cout << "Error wrong number of arguments!" << endl;
	}
	cout << "Starting the script..." << endl;

	LED led; // Object led (Class LED)

	// Comparing argument
	if(strcmp(argv[1],"on") == 0)
	{
		// Turns on LED3
		led.On();
	}
	else
	{
		if(strcmp(argv[1],"off") == 0)
		{
			// Turns off LED3
			led.Off();
		}
		else
		{
			if(strcmp(argv[1],"flash") == 0)
			{
				// LED3 starts flashing 50ms on, 50ms off (needs sudo)
				led.flash();
			}
			else
			{
				cout << "Wrong arguments" << endl;
			}
		}
	}
	cout << "Script Done" << endl;

	return 0;
}
