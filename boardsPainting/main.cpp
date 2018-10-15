#include <stdio.h>
#include <algorithm>
#include <cassert>
using namespace std;

using board_t = unsigned;
using painter_t = unsigned;
using duration_t = unsigned;
duration_t const MaxPossibleDuration = -1;
painter_t const MaxPainterNumber = 30;
size_t const MaxBoardNumber = 50;
board_t const MaxBoardLength = 500; // just so you know

// in this table in the first row will (row 1 (1!!!) (not zero!))
// be the minimal duration of painting 
// the first n boards
duration_t duration[MaxPainterNumber][MaxBoardNumber];
duration_t boards[MaxBoardNumber];
board_t numberOfBoards;
painter_t numberOfPainters; 

// [from, to]
duration_t timeToPaintBoardsFromTo(board_t from, board_t to) {
    if (from == 0) return duration[0][to];
    return duration[0][to] - duration[0][from - 1]; 
}

void performTabulation() {
    duration[0][0] = boards[0];
    for (size_t i = 1; i < numberOfBoards; ++i) {
        duration[0][i] = duration[0][i - 1] + boards[i];
    }
    
    for (painter_t painters = 1; painters < numberOfPainters; ++painters) {
        for (board_t boards = 0; boards < numberOfBoards; ++boards) {
            duration_t minDur = MaxPossibleDuration;
            for (board_t b = 0; b < boards; ++b) {
                duration_t timeToPaintPreviousBoards = duration[painters - 1][b];
                duration_t timeToPaintTheOtherBoards = timeToPaintBoardsFromTo(b + 1, boards);
                duration_t currDur = std::max(timeToPaintPreviousBoards, timeToPaintTheOtherBoards);
                if (minDur > currDur) minDur = currDur;
            }
            duration[painters][boards] = minDur;
        }
    }
}

int main() {
    size_t numberOfTestCases; scanf("%lu", &numberOfTestCases);
    for (size_t i = 0; i < numberOfTestCases; ++i) {
        scanf("%u", &numberOfPainters);
        scanf("%u", &numberOfBoards);
        for (board_t i = 0; i < numberOfBoards; ++i) {
            scanf("%u", &boards[i]);
        }
    
        
        
        duration_t res;
        if (numberOfPainters < numberOfBoards) {
            performTabulation();
            assert(timeToPaintBoardsFromTo(2, 2) == boards[2]);
            res = duration[numberOfPainters - 1][numberOfBoards - 1];
        } else {
            res = *std::max_element(boards, boards + numberOfBoards);
        }
        printf("%u\n", res);
    }
    return 0;
}
