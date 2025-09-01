/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Declarations of routines for processing user input
 */

#pragma once

#include "Sym_data_types.hpp"

namespace SymUI
{
    // This method takes the permutation entered by the user in the UI and validates it.
    // First parameter is the entry in the permutation which will change. The new value is in inputBuffer.
    // If it passes the processing checks, it will be transferred to permutation (the third parameter)
    void ProcessPermutationInput(int i, Sym::Permutation& inputBuffer, Sym::Permutation& permutation);

    void ShrinkPermutationByOne(Sym::Permutation& permutation);

    void CopyPermutation(Sym::Permutation& destination, Sym::Permutation& source);

    Sym::Permutation InitializePermutation(int size);

    // Purpose: Process permutations written in cycle notation.
    // 
    // Consider the permutation
    // 
    //       [1 2 3]
    //  f =  [2 3 1]
    // 
    // Since f(1) = 2, f(2) = 3, and f(3) = 1
    // 
    // We say that f is a 3-cycle. More generally a permutation can be a n-cycle, where n is the length of the cycle.
    // It turns out that every permutation can be written as the product of cycles. This lends itself to a much more
    // compact notation for writing permutations. Using cycle notation, f can be expressed as:
    // 
    // (1 2 3)
    // 
    // with the understanding that
    // 
    // 1. each element is mapped to the element immediately listed to the right
    // 2. The last element is mapped to the first
    // 3. Elements not listed are mapped to themselves.
    //
    // The product of two cycles would be written like:
    //
    // (4 6 7)(3 4 5)
    //
    // Strictly speaking, cycle notation is ambiguous - the above permutation might be in S_7, or S_8, or in any
    // S_n with n >= 7. As long as the context of what S_n we're in is given, this isn't a problem.
    //
    // Also notice that there are multiple different ways to write the same permutation, even just as a single cycle:
    // (143), (431), and (314)
    // all represent the function which maps 1 to 4, 4 to 3, 3 to 1, and 2 to 2.
    Sym::Permutation ProcessCycleNotationInput(const char* cycleInput);
}