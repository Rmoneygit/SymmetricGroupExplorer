/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Declarations of routines for core algorithms dealing with the symmetric group.
 */

#pragma once

#include "Sym_data_types.hpp"

namespace Sym
{
    Permutation ComposePermutations(const Permutation& permutation1, const Permutation& permutation2);

    Permutation ComposePermutations(const PermutationVector& permutations);

    void CommutePermutations(Permutation& permutation1, Permutation& permutation2);

    int CalculateOrder(const Permutation& permutation);

    bool EqualsIdentity(const Permutation& permutation);

    void SetToIdentity(Permutation& permutation);
}