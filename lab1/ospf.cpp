/*
 * =====================================================================================
 *
 *       Filename:  ospf.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/13/2012 03:50:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Prakash Gamit (), prakashgamit23@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{
  int connection[32][32];
  int distance[32][32];
  int nodes;
  cin >> nodes;

  for(int i=0; i<nodes; i++)
  {
    for(int j=0; j<nodes; j++)
    {
      cin >> connection[i][j];
      cin >> distance[i][j];
    }
  }

  int min_dist[nodes];
  min_dist[0] = 0;

  for(int i = 1; i< nodes; i++)
    min_dist[i] = 10000;

  int min;
  int next_node = 0;
  int k;
  for(int i=0; i< nodes; i++)
  {
    k = 0;
    for(int j=0; j<nodes; j++)
    {
      if(connection[next_node][j] == 1 && distance[next_node][j]+min_dist[next_node] < min_dist[j])
      {
        min_dist[j] = distance[next_node][j] + min_dist[next_node];

        if(k == 0){
          min = min_dist[j];
        }
        connection[i][j] = 0;
        if(min_dist[j] < min)
        {
          min = min_dist[j];
          next_node = j;
        }
      }
    }
  }

  for(int i=0; i<nodes; i++)
    cout << min_dist[i] << endl;
}
