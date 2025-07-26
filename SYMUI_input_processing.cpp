/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Implementations of routines for processing user input
 */

#include "SYM_data_types.h"
#include "SYMUI_input_processing.h"

#include <cassert>
#include <vector>
#include <stdexcept>

void SymUI::ProcessPermutationInput(int i, Sym::Permutation& inputBuffer, Sym::Permutation& permutation)
{
    if (inputBuffer.size() != permutation.size())
    {
        throw std::invalid_argument("Expected inputBuffer and permutation to have the same size.");
    }

    // Only allow values between 1-n inclusive
    if (inputBuffer[i] > 0 && inputBuffer[i] <= inputBuffer.size())
    {
        // A permutation is a shuffling of symbols, so repetitions can't be allowed. 
        // So, swap the existing occurrence of this symbol with this one. Example:
        /*
        **********Stage 1**********
        inputBuffer
        1 2 3 4
        1 3 2 3

        permutation
        1 2 3 4
        1 4 2 3

        **********Stage 2**********
        inputBuffer
        1 2 3 4
        1 3 2 *4*

        permutation
        1 2 3 4
        1 4 2 *4*

        **********Stage 3**********
        inputBuffer
        1 2 3 4
        1 3 2 4

        permutation
        1 2 3 4
        1 *3* 2 4

        */
        bool foundValue = false;
        for (int j = 0; j < inputBuffer.size(); j++)
        {
            if (inputBuffer[j] == inputBuffer[i] && i != j)
            {
                inputBuffer[j] = permutation[i];
                permutation[j] = permutation[i];
                foundValue = true;
                break;
            }
        }

        assert(foundValue);

        permutation[i] = inputBuffer[i];
    }
    else
    {
        inputBuffer[i] = permutation[i];
    }
}

void SymUI::ShrinkPermutationByOne(Sym::Permutation& permutation)
{
    int n = static_cast<int>(permutation.size());
    for (int i = 0; i < n; i++)
    {
        if (permutation[i] == n)
        {
            permutation[i] = permutation[n - 1];
        }
    }

    permutation.resize(n - 1);
}

void SymUI::CopyPermutation(Sym::Permutation& destination, Sym::Permutation& source)
{
    for (int i = 0; i < destination.size(); i++)
    {
        destination[i] = source[i];
    }
}

Sym::Permutation SymUI::InitializePermutation(int size)
{
    Sym::Permutation permutation;

    for (int i = 0; i < size; i++)
    {
        permutation.push_back(i + 1);
    }

    return permutation;
}
