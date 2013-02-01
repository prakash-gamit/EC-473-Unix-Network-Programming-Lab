// =====================================================================================
// 
//       Filename:  tsp.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  Monday 15 October 2012 08:25:51  IST
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Prakash Gamit (09211014), <prakashgamit23@gmail.com>
//        Organisation:  Indian Institute of Technology, Roorkee
// 
// =====================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int main(){
    uint32_t total_nodes = 8;
    float distance_matrix[8][8] = 
                   {{0, 2.2, 5.8, 4.0, 5.0, 8.5, 3.6, 3.6},
                    {2.2, 0, 4.1, 3.6,5.8, 4.9, 5.0, 5.8 },
                    {5.8, 4.1, 0, 3.2, 6.1, 9.0, 6.7, 9.2},
                    {4.0, 3.6, 3.2, 0, 3.0, 6.3, 3.6, 6.7},
                    {5.0, 5.8, 6.1, 3.0, 0, 3.6, 2.0, 6.0},
                    {8.5, 9.4, 9.0, 6.3, 3.6, 0, 3.6, 8.5},
                    {3.6, 5.0, 6.7, 3.6, 2.0, 3.6, 0, 4.0},
                    {3.6, 5.8, 9.2, 6.7, 6.0, 8.5, 4.0, 0}
                };
    uint32_t t_nodes = 0, tour[8] = {0};
    uint32_t temp, i, j, k;

    printf("Distance matrix\n\t");
    for(i = 0; i < total_nodes; i++){
        printf("%d\t", i+1);
    }
    printf("\n\n");

    for(i = 0; i < total_nodes; i++){
        printf("%d\t", i+1);
        for(j = 0; j < total_nodes; j++){
            if(i == j){
                printf("---\t");
            }
            else
                printf("%.1f\t", distance_matrix[i][j]);
        }
        printf("\n");
    }

    /* get nodes in tour */
    printf("Enter nodes in tour(0 to stop)\n");
    for(i = 0; i < total_nodes; i++){
        scanf("%d", &temp);

        if(temp == 0)
            break;
        else if(temp > 0 && temp <= total_nodes){
            tour[temp - 1] = 1;
            ++t_nodes;
        }
        else{
            printf("invalid node: %d", temp);
            --i;
        }
    }/* for */

    //find first node in tour
    i = 0;
    while(tour[i++] != 1)
        ;
    k = --i;

    //tsp
    float min, t_dist = 0;
    printf("\nTour:\n");
    while(t_nodes-- != 1){
        tour[i] = 0;
        min = 100;//set it to high value

        printf("==> %d ", i+1);

        for(j = k; j < total_nodes; j++){
            if(tour[j] == 1 && min > distance_matrix[i][j]){
                min = distance_matrix[i][j];
                temp = j;
            }
        }/* for */

        t_dist += min;
        i = temp;
    }/* while */

    t_dist += distance_matrix[k][i];
    printf("==> %d\n", i+1);
    printf("total distance = %.1f\n", t_dist);
    return 0;
}
