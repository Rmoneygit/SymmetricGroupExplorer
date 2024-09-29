/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Implementations of routines for core algorithms dealing with the symmetric group.
 */

#include <vector>

void SYM_compose_permutations(const std::vector<int>& permutation1, const std::vector<int>& permutation2, std::vector<int>& result)
{
    result.clear();
    result.resize(permutation1.size());

    for (int i = 0; i < permutation2.size(); i++)
    {
        result[i] = permutation1[permutation2[i] - 1];
    }
}