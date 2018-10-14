#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <cassert>

size_t const MaxStringLength = 1000;
char str[MaxStringLength + 1];
size_t strLen;
using cut_t = int;
cut_t const MaxPossibleCuts = 1000;

bool palindrome[MaxStringLength][MaxStringLength];

void performTabulationForPalindromeTable() {
    for (size_t start = 0; start < strLen; ++start) {
        size_t const end = start;
        palindrome[start][end] = true;
    }
    
    for (size_t end = 1; end < strLen; ++end) {
        size_t const start = end - 1;
        palindrome[start][end] = (str[start] == str[end]);
    }

    for (size_t offset = 2; offset < strLen; ++offset) {
        for (size_t start = 0; start + offset < strLen; ++start) {
            size_t const end = start + offset;
            palindrome[start][end] = (str[start] == str[end]) and palindrome[start + 1][end - 1];
        }
    }
}

cut_t cutsArr[MaxStringLength];
void performTabulationForCutsFlatArray() {
    for (size_t end = 0; end < strLen; ++end) {
        cutsArr[end] = MaxPossibleCuts;
        if (palindrome[0][end]) {
            cutsArr[end] = 0;
        } else {
            for (size_t i = 0; i < end; ++i) {
                cut_t minCuts = cutsArr[end];
                size_t startOfTheEndOfTheString = i + 1;
                if (palindrome[startOfTheEndOfTheString][end]) {
                    cut_t currCuts = cutsArr[i] + 1; // + 0 for the palindrome ending
                    if (minCuts > currCuts) minCuts = currCuts;
                }
                cutsArr[end] = minCuts; 
            }
        }
    }
}

int main() {
    size_t numberOfTestCases; scanf("%lu", &numberOfTestCases);
    getchar(); // skip one newline char
    for (size_t i = 0; i < numberOfTestCases; ++i) {
        fgets(str, MaxStringLength, stdin);
        strLen = strlen(str);
        if (str[strLen - 1] == '\n') {
            --strLen;
            str[strLen] = '\0';
        }
        
        performTabulationForPalindromeTable();
        performTabulationForCutsFlatArray();
        
        printf("%i\n", cutsArr[strLen - 1]);
    }
    return 0;
}
