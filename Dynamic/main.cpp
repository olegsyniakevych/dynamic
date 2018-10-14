//
//  main.cpp
//  Dynamic
//
//  Created by Oleg Syniakevych on 13/10/2018.
//  Copyright © 2018 Oleg Syniakevych. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <cstring>

typedef unsigned cost_t;
cost_t MAX_POSSIBLE_COST = -1;

size_t const MAX_ARRAY_SIZE = 100;
cost_t minCuts[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
cost_t array[MAX_ARRAY_SIZE];
size_t N;


cost_t minCost(size_t start, size_t end) {
    assert(end - start >= 2);
    if (minCuts[start][end] != -1) return minCuts[start][end];
    
    cost_t res;
    switch (end - start) {
        case 2: 
            res = 0; 
            break;
        case 3: 
            res = array[start] * array[start+1] * array[start+2]; 
            break;
        default: {
            cost_t currMinCost = MAX_POSSIBLE_COST;
            for (size_t i = start + 2; i < end; ++i) {
                cost_t currCost 
                    = minCost(start, i) + minCost(i - 1, end)
                    + array[start] * array[i - 1] * array[end - 1]
                    ;
                if (currMinCost > currCost) currMinCost = currCost;
            }
            res = currMinCost;
            break;
        }
    }
    
    minCuts[start][end] = res;
    return res;
}

int main() {
    size_t numberOfTestCases; scanf("%lu", &numberOfTestCases);
    for (size_t i = 0; i < numberOfTestCases; ++i) {
        memset(minCuts, -1, sizeof(minCuts));
        scanf("%lu", &N);
        for (size_t i = 0; i < N; ++i) {
            scanf("%u", &array[i]);
        }
        
        printf("%u\n", minCost(0, N));
    }
    return 0;
}
