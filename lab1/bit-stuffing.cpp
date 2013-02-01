#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	string msg;// original message -- without stuffing
	string stuffed_msg; // message after stuffing
	string stuffing = "111111";// stuffing bits

	int loc;// location where stuffing is found in message

	cout << "Enter message: ";
	cin >> msg;

  //initialize stuffed message 01111110
  stuffed_msg = "0" + stuffing + "0 ";

	loc = msg.find(stuffing);

	while(loc >= 0 && loc < msg.length())
	{
		//if stuffing found then append 0 after five 1's 
		stuffed_msg += msg.substr(0,loc+5) + " 0 ";

		//set message to substring after stuffing
		msg = msg.substr(loc + 5);

		//find new location of stuffing
		loc = msg.find(stuffing);
	}

	//append remaining message
	stuffed_msg += msg;

  //terminate stuffed_msg with 01111110
  stuffed_msg += " 0" + stuffing + "0";

	cout << stuffed_msg << endl;

	return 0;
}
