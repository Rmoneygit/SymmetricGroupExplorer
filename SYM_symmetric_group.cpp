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
    if (n < 1)
        throw std::invalid_argument("Input to factorial function must be a positive integer.");
    
    if (n == 1)
        return 1;
    
    if (n == 2)
        return 2;

    return factorial(n - 1) * factorial(n - 2);
}

std::vector<int> SYM_compose_permutations(const std::vector<int>& permutation1, const std::vector<int>& permutation2)
{
    std::vector<int> result(permutation1.size());

    for (int i = 0; i < permutation2.size(); i++)
    {
        result[i] = permutation1[permutation2[i] - 1];
    }

    return result;
}

void SYM_commute_permutations(std::vector<int>& permutation1, std::vector<int>& permutation2)
{
    // Throw error if the permutations are different sizes

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
