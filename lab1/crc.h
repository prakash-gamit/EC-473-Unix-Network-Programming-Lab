/*
 * =====================================================================================
 *
 *       Filename:  crc.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/07/2012 02:27:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Prakash Gamit (), prakashgamit23@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

class Crc
{
  public:
    Crc(string, string);

    string get_crc();
  protected:
    string message;
    string generator_polynomial;
};


Crc :: Crc(string message, string generator_polynomial)
{
  this -> message = message;
  this -> generator_polynomial = generator_polynomial;
}


string Crc :: get_crc()
{
  int n = generator_polynomial.length();//length of generator_polynomial
  int i,j;

  //append n-1 0's to message
  for(i = 0; i < n - 1; i++)
    message += "0";

  /*
   * convert message string to integer array
   */
  int msg[message.length()];
  for(i = 0; i < message.length(); i++)
  {
    msg[i] = (int)message[i] - (int)'0';
  }

  /*
   * convert generator_polynomial string to integer array
   */
  int gen_pol[n];// n = length of generator_polynomial
  for(i = 0; i < n; i++)
  {
    gen_pol[i] = (int)generator_polynomial[i] - (int)'0';
  }
  
  int k = message.length() - (n - 1);
  for(i = 0; i < k;)
  {
    for(j = i; j < i+n; j++)
    {
      msg[j] = (msg[j] ^ gen_pol[j-i]);
    }
    while(msg[i] == 0)
      i++;
  }

  //calculate remainder
  string rem = "";
  for(i = k; i < message.length(); i++)
    rem.append(1,msg[i] + 48);

  //retrun crc
  return message.substr(0,k) + rem;
}
