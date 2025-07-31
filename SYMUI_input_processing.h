/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Declarations of routines for processing user input
 */

#pragma once

#include "Sym_data_types.h"

namespace SymUI
{
    // This method takes the permutation entered by the user in the UI and validates it.
    // First parameter is the entry in the permutation which will change. The new value is in inputBuffer.
    // If it passes the processing checks, it will be transferred to permutation (the third parameter)
    void ProcessPermutationInput(int i, Sym::Permutation& inputBuffer, Sym::Permutation& permutation);

    void ShrinkPermutationByOne(Sym::Permutation& permutation);

    void CopyPermutation(Sym::Permutation& destination, Sym::Permutation& source);

    Sym::Permutation InitializePermutation(int size);
}