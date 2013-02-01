/*
 * =====================================================================================
 *
 *       Filename:  ipheader.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/12/2012 02:48:07 PM
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
using namespace std;

class IPHeader
{
  public:
    IPHeader(string);
    unsigned int toDecimal(string);
    int getDecimalVal(char);
    unsigned int calculateChecksum();
    bool verifyChecksum();
  protected:
    string header;
};


IPHeader :: IPHeader(string header)
{
  this -> header = header;
}


unsigned int IPHeader :: toDecimal(string hex)
{
  unsigned int dec = 0;
  for(int i = hex.length() - 1; i >= 0; i--)
  {
    dec += getDecimalVal(hex[i]) * pow(16.0,hex.length() - 1 - i);
  }
  return dec;
}


int IPHeader :: getDecimalVal(char ch)
{
  switch(ch)
  {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': return 10;
    case 'b': return 11;
    case 'c': return 12;
    case 'd': return 13;
    case 'e': return 14;
    case 'f': return 15;
    default : return -1;
  }
}


unsigned int IPHeader :: calculateChecksum()
{
  unsigned int sum = 0;
  //omit checksum field in IP packet
  string temp_header = header.substr(0,20) + header.substr(24);

  for(int i = 0; i < 36; i += 4)
  {
    sum += toDecimal(temp_header.substr(i,4));

    /* there is an extra carry bit (17th bit)
    *  but crc is always 16 bit
    *  so add carry bit to sum again
    */
    if(sum >> 16)
      //------ 16 bits ------ carry bit
      sum = (sum & 0xFFFF) + (sum >> 16);
  }

  //int is 32 bit
  //bitwise inversion will invert MSB 16 bits to 1
  //if we don't bitwise & sum with 0xFFFF answer will be wrong
  unsigned int checksum = (~sum & 0xFFFF);

  return checksum;
}


bool IPHeader :: verifyChecksum()
{
  unsigned int calculated_checksum = calculateChecksum();

  //checksum field starts at 21 bit and it is 16 bits in length
  //16 bits = 4 hex digits
  unsigned int packet_checksum = toDecimal(header.substr(20,4));

  cout << "packet_checksum:     " << hex << packet_checksum << endl;
  cout << "calculated_checksum: " << hex << calculated_checksum << endl;

  if(packet_checksum == calculated_checksum)
    return true;//correct checksum

  //invalid checksum
  return false;
}
