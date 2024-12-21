/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Declarations of routines for core algorithms dealing with the symmetric group.
 */

#pragma once

#include <vector>

std::vector<int> SYM_compose_permutations(const std::vector<int>& permutation1, const std::vector<int>& permutation2);

void SYM_commute_permutations(std::vector<int>& permutation1, std::vector<int>& permutation2);

int SYM_calculate_order(const std::vector<int>& permutation);

bool SYM_equals_identity(const std::vector<int>& permutation);

void SYM_set_to_identity(std::vector<int>& permutation);