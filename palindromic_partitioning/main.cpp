#include <stdio.h>
#include <string.h>
#include <cassert>

size_t const MaxStringLength = 1000;
char str[MaxStringLength + 1];
size_t strLen;
using cut_t = int;
cut_t const MaxPossibleCuts = 1000;
using index_t = char const *;

enum class Research: char { unchecked=-1, no=0, yes=1 };

Research isPalindromeTable[MaxStringLength][MaxStringLength];

// start is the index of the first character,
// end is the index of the character past the 
// last character (as usual)
bool isPalindrome(index_t start, index_t end) {
    size_t const startIdx = start - str;
    size_t const endIdx = end - str;
    if (isPalindromeTable[startIdx][endIdx] != Research::unchecked) {
        return isPalindromeTable[startIdx][endIdx] == Research::yes;
    } else {
        auto res = Research::unchecked;
        
        --end;
        
        if (start == end) {
            res = Research::yes;
        } else if (*start != *end) {
            res = Research::no;
        } else {
            ++start;
        
            if (start == end) {
                res = Research::yes;
            } else {
                res = isPalindrome(start, end) ? Research::yes : Research::no;
            }
        }
        
        isPalindromeTable[startIdx][endIdx] = res;
        
        return res == Research::yes;
    }
}

cut_t table[MaxStringLength][MaxStringLength];

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
        memset(table, -1, sizeof table);
        memset(isPalindromeTable, (char) Research::unchecked, sizeof isPalindromeTable);
        fgets(str, MaxStringLength, stdin);
        strLen = strlen(str);
        if (str[strLen - 1] == '\n') {
            --strLen;
            str[strLen] = '\0';
        }
        for (size_t i = 0; i < strLen; ++i) {
            for (size_t j = 0; (i + j) <= strLen; ++j) {
                isPalindrome(str + i, str + i + j);
            }
        }
        
        printf("%u\n", numberOfCuts(str, str + strLen));
        // printf("%u %s \n", strLen, str);
        // printf("%i\n", (int)str[strLen]);
    }
    return 0;
}

