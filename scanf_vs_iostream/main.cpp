//
//  main.cpp
//  scanf_vs_iostream
//
//  Created by Oleg Syniakevych on 13/10/2018.
//  Copyright © 2018 Oleg Syniakevych. All rights reserved.
//

#include <stdio.h>
#include <time.h>
size_t const size = 10000000;
int arr[size];
int main(int argc, const char * argv[]) {
    clock_t start = clock();
    for (size_t i = 0; i < size; ++i) {
        scanf("%u", &arr[i]);
    }
    clock_t duration = clock() - start;
    duration /= 1000;
    printf("%lu\n", duration);
    
    return 0;
}
