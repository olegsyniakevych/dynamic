#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
//#include <cassert>

size_t const MaxStringLength = 1000;
char str[MaxStringLength + 1];
size_t strLen;
using cut_t = int;
cut_t const MaxPossibleCuts = 1000;
using index_t = char const *;

enum class Research: char { unchecked=-1, no=0, yes=1 };

Research isPalindromeTable[MaxStringLength][MaxStringLength];

void performTabulationForPalindromeTable() {
    for (size_t offset = 0; offset < strLen; ++offset) {
        for (size_t start = 0; start + offset < strLen; ++start) {
            size_t end = start + offset;
            auto res = Research::unchecked;
            if (start == end) {
                res = Research::yes;
            } else {
                if (str[start] == str[end]) {
                    if (end - start == 1) {
                        res = Research::yes;  
                    } else {
                        res = isPalindromeTable[start + 1][end - 1];
                    }
                } else {
                    res = Research::no;
                }
            }
            isPalindromeTable[start][end] = res;
        }
    }
}

// start is the index of the first character,
// end is the index of the character past the 
// last character (as usual)
bool isPalindrome(index_t start, index_t end) {
    size_t const startIdx = start - str;
    size_t const endIdx = end - str;
    return isPalindromeTable[startIdx][endIdx - 1] == Research::yes;
}

cut_t table[MaxStringLength][MaxStringLength];

void performTabulationForNumberOfCuts() {
    for (size_t start = 0; start < strLen; ++start) {
        size_t const offset = 0;
        table[offset][start] = 0; // we need zero cuts for strings of length 1
    }
    
    for (size_t offset = 1; offset < strLen; ++offset) {
        for (size_t start = 0; start + offset < strLen; ++start) {
            size_t end = start + offset;
            cut_t res = -1;
            if (isPalindromeTable[start][end] == Research::yes) {
                res = 0;
            } else {
                cut_t minCuts = MaxPossibleCuts;
                for (size_t i = start; i < end; ++i) {
                    size_t const start1 = start;
                    size_t const offset1 = i - start1;
                    size_t const start2 = i + 1;
                    size_t const offset2 = end - start2;
//                    printf("start1: %zu, offset1:%zu, start2: %zu, offset2:%zu\n", start1, offset1, start2, offset2);
                    cut_t currCuts = table[offset1][start1] + 1 + table[offset2][start2];
                    if (minCuts > currCuts) minCuts = currCuts;
                }
                res = minCuts;
            }
            
            table[offset][start] = res;
        }
    }
}

// end also points to some segfault-prone end of the line (or null char)
cut_t numberOfCuts(index_t start, index_t end) {
    size_t const startIdx = start - str;
    size_t const endIdx = end - str;
    if (table[startIdx][endIdx] != -1) {
        return table[startIdx][endIdx];
    } else {
        // so, here we will divide our string
        // in parts at all places, and get the number of cuts needed to 
        // cut the left and the right side
        // but first we will check if the string is a palindrome
        cut_t res;
        if (isPalindrome(start, end)) {
            res = 0;
        } else {
            cut_t currMinCut = MaxPossibleCuts;
            for (index_t i = start + 1; i < end; ++i) {
                cut_t currCut = numberOfCuts(start, i) + 1 + numberOfCuts(i, end);
                if (currMinCut > currCut) currMinCut = currCut;
            }
            res = currMinCut;
        }
        
        table[startIdx][endIdx] = res;
        
        return res;
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
        performTabulationForNumberOfCuts();
        
        printf("%u\n", table[strLen - 1][0]);
    }
    return 0;
}
