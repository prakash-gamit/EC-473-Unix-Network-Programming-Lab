/*
 * =====================================================================================
 *
 *       Filename:  que1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/27/2012 11:10:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Prakash Gamit (), prakashgamit23@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstring>
#include <cmath>

#include "crc.h"

using namespace std;

int main()
{
    string msg;
    string gen;

    cout << "Enter message(binary): ";
    cin >> msg;
    cout << "Enter generator(binary): ";
    cin >> gen;

    Crc c(msg, gen);
    cout << "Message: " << msg << endl;
    cout << "    CRC: " << c.get_crc() << endl;

    return 0;
}
