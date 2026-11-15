/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Declarations of routines for core algorithms dealing with the symmetric group.
 */

#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

#include "Sym_data_types.hpp"

namespace Sym
{
    Permutation ComposePermutations(const Permutation& permutation1, const Permutation& permutation2);

    Permutation ComposePermutations(const PermutationPtrVector& permutations);

    void CommutePermutations(Permutation& permutation1, Permutation& permutation2);

    std::uint64_t CalculateOrder(const Permutation& permutation);

    bool EqualsIdentity(const Permutation& permutation);

    void SetToIdentity(Permutation& permutation);

    std::string GetCycleNotationString(const Permutation& permutation);

    void ValidatePermutation(const Permutation& permutation);

    PermutationUnorderedSet FindGeneratedSubgroup(const PermutationUnorderedSet& subset);
}