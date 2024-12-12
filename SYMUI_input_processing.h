/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Declarations of routines for processing user input
 */

#pragma once

#include <vector>

// First parameter is the entry in the permutation which will change. The new value is in inputBuffer.
// If it passes the processing checks, it will be transferred to permutation (the third parameter)
void processPermutationInput(int i, std::vector<int>& inputBuffer, std::vector<int>& permutation);

void shrinkPermutation(std::vector<int>& inputBuffer, std::vector<int>& permutation);

void updateInputBuffer(std::vector<int>& inputBuffer, std::vector<int>& permutation);