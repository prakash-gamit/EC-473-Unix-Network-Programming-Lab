/*
 * =====================================================================================
 *
 *       Filename:  que2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/12/2012 03:05:13 PM
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
#include <cstdlib>

#include "ipheader.h"

using namespace std;

int main(int argc, char *argv[])
{
  string header;
  //header = "4500003c1c4640004006b1e6ac100a63ac100a0c";
  //
  if(argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
  {
    cout << "Usage: " << argv[0] << " <checksum>" << endl;
  }
  else if(argc == 2)
  {
    header = argv[1];
  }
  else
  {
    cout << "Enter IP header(hexadecimal format)\neg. 4500003c1c4640004006b1e6ac100a63ac100a0c\nheader: ";
    cin >> header;
  }

  if(header.length() != 40)
  {
    cerr << "Invalid IP header: header length = " << header.length() << endl;
    cerr << "header length should be 32" << endl;
    exit(-1);
  }
  IPHeader ip(header);

  if(ip.verifyChecksum())
    cout << "Checksum verified:\ncorrect checksum :)" << endl;
  else
    cout << "Checksum verified:\nincorrect checksum :(" << endl;

  return 0;
}
