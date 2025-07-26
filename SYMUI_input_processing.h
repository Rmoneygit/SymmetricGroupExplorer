/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Declarations of routines for processing user input
 */

#pragma once

#include <vector>

namespace SymUI
{
    // First parameter is the entry in the permutation which will change. The new value is in inputBuffer.
    // If it passes the processing checks, it will be transferred to permutation (the third parameter)
    void ProcessPermutationInput(int i, std::vector<int>& inputBuffer, std::vector<int>& permutation);

    void ShrinkPermutationByOne(std::vector<int>& permutation);

    void CopyPermutation(std::vector<int>& destination, std::vector<int>& source);
}