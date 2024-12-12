/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Declarations of routines for core algorithms dealing with the symmetric group.
 */

#pragma once

#include <vector>

void SYM_compose_permutations(const std::vector<int>& permutation1, const std::vector<int>& permutation2, std::vector<int>& result);

void SYM_commute_permutations(std::vector<int>& permutation1, std::vector<int>& permutation2);