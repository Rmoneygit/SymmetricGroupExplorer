/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Declarations of routines for core algorithms dealing with the symmetric group.
 */

#pragma once

#include <vector>

namespace Sym
{
    std::vector<int> ComposePermutations(const std::vector<int>& permutation1, const std::vector<int>& permutation2);

    void CommutePermutations(std::vector<int>& permutation1, std::vector<int>& permutation2);

    int CalculateOrder(const std::vector<int>& permutation);

    bool EqualsIdentity(const std::vector<int>& permutation);

    void SetToIdentity(std::vector<int>& permutation);
}