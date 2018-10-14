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
using index_t = char const *;

enum class Research: char { unchecked=-1, no=0, yes=1 };

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

cut_t cutsTable[MaxStringLength][MaxStringLength];

void performTabulationForNumberOfCuts() {
    for (size_t start = 0; start < strLen; ++start) {
        size_t const offset = 0;
        cutsTable[offset][start] = 0; // we need zero cuts for strings of length 1
    }
    
    for (size_t offset = 0; offset < strLen; ++offset) {
        size_t const start = 0;
        size_t const end = start + offset;
        cut_t res = -1;
        if (palindrome[start][end]) {
            res = 0;
        } else {
            cut_t minCuts = MaxPossibleCuts;
            for (size_t i = start; i < end; ++i) {
                size_t const start1 = start;
                size_t const offset1 = i - start1;
                size_t const start2 = i + 1;
                size_t const offset2 = end - start2;
                cut_t currCuts = cutsTable[offset1][start1] + 1 + cutsTable[offset2][start2];
                if (minCuts > currCuts) minCuts = currCuts;
            }
            res = minCuts;
        }
        
        cutsTable[offset][start] = res;
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
