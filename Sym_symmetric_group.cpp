/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Implementations of routines for core algorithms dealing with the symmetric group.
 */

#include <vector>
#include <stdexcept>

#include "Sym_symmetric_group.hpp"

namespace
{
    int factorial(const int n)
    {
        int val = 1;
        for (int i = 2; i <= n; i++)
        {
            val = val * i;
        }

        return val;
    }
}

std::vector<int> Sym::ComposePermutations(const std::vector<int>& permutation1, const std::vector<int>& permutation2)
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

void Sym::CommutePermutations(std::vector<int>& permutation1, std::vector<int>& permutation2)
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

int Sym::CalculateOrder(const std::vector<int>& permutation)
{
    std::vector<int> buffer = permutation;
    int order = 1;
    const int max_possible = factorial(permutation.size());
    while (!Sym::EqualsIdentity(buffer))
    {
        buffer = Sym::ComposePermutations(buffer, permutation);

        order++;

        if (order > max_possible)
            throw std::invalid_argument("Permutation can never have order greater than the order of the entire symmetric group! The input may be corrupt.");
    }

    return order;
}

bool Sym::EqualsIdentity(const std::vector<int>& permutation)
{
    for (int i = 0; i < permutation.size(); i++)
    {
        if (permutation[i] != i + 1)
            return false;
    }

    return true;
}

void Sym::SetToIdentity(std::vector<int>& permutation)
{
    for (int i = 0; i < permutation.size(); i++)
    {
        permutation[i] = i + 1;
    }
}
