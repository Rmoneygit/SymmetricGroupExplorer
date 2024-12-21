/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Implementations of routines for core algorithms dealing with the symmetric group.
 */

#include <vector>
#include <stdexcept>

#include "SYM_symmetric_group.h"

int factorial(const int n)
{    
    int val = 1;
    for (int i = 2; i <= n; i++)
    {
        val = val * i;
    }

    return val;
}

std::vector<int> SYM_compose_permutations(const std::vector<int>& permutation1, const std::vector<int>& permutation2)
{
    if (permutation1.size() != permutation2.size())
        throw std::invalid_argument("Permutations provided should not have different sizes.");
    
    std::vector<int> result(permutation1.size());

    for (int i = 0; i < permutation2.size(); i++)
    {
        result[i] = permutation1[permutation2[i] - 1];
    }

    return result;
}

void SYM_commute_permutations(std::vector<int>& permutation1, std::vector<int>& permutation2)
{
    if(permutation1.size() != permutation2.size())
        throw std::invalid_argument("Permutations provided should not have different sizes.");

    for (int i = 0; i < permutation1.size(); i++)
    {
        int temp = permutation1[i];
        permutation1[i] = permutation2[i];
        permutation2[i] = temp;
    }
}

int SYM_calculate_order(const std::vector<int>& permutation)
{
    std::vector<int> buffer = permutation;
    int order = 1;
    const int max_possible = factorial(permutation.size());
    while (!SYM_equals_identity(buffer))
    {
        buffer = SYM_compose_permutations(buffer, permutation);

        order++;

        if (order > max_possible)
            throw std::invalid_argument("Permutation can never have order greater than the order of the entire symmetric group! The input may be corrupt.");
    }

    return order;
}

bool SYM_equals_identity(const std::vector<int>& permutation)
{
    for (int i = 0; i < permutation.size(); i++)
    {
        if (permutation[i] != i + 1)
            return false;
    }

    return true;
}

void SYM_set_to_identity(std::vector<int>& permutation)
{
    for (int i = 0; i < permutation.size(); i++)
    {
        permutation[i] = i + 1;
    }
}