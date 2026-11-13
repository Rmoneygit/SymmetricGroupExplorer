/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Implementations of routines for core algorithms dealing with the symmetric group.
 */

#include <cstdlib>
#include <cstdint>
#include <limits>
#include <vector>
#include <stdexcept>
#include <unordered_set>

#include "Sym_data_types.hpp"
#include "Sym_symmetric_group.hpp"

using namespace Sym;

// -------------------------------------------------------------------------------------------------
Permutation Sym::ComposePermutations(const Permutation& permutation1, const Permutation& permutation2)
{
    if (permutation1.size() != permutation2.size())
        throw std::invalid_argument("Cannot compose permutations of different sizes.");
    
    Permutation result(permutation1.size());

    for (int i = 0; i < permutation2.size(); i++)
    {
        result[i] = permutation1[permutation2[i] - 1];
    }

    return result;
}

// -------------------------------------------------------------------------------------------------
Permutation Sym::ComposePermutations(const PermutationVector& permutations)
{
    if (permutations.empty())
        throw std::invalid_argument("Trying to compose permuations, but none were provided.");

    Permutation result(permutations[0]->size());
    SetToIdentity(result);

    for (const auto perm : permutations)
    {
        Permutation temp(result);
        result = ComposePermutations(temp, *perm);
    }

    return result;
}

// -------------------------------------------------------------------------------------------------
void Sym::CommutePermutations(Permutation& permutation1, Permutation& permutation2)
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

// -------------------------------------------------------------------------------------------------
std::uint64_t Sym::CalculateOrder(const Permutation& permutation)
{
    Sym::ValidatePermutation(permutation);
    
    Permutation buffer = permutation;
    std::uint64_t order = 1;
    while (!Sym::EqualsIdentity(buffer))
    {
        buffer = Sym::ComposePermutations(buffer, permutation);

        order++;

        if (order == std::numeric_limits<uint64_t>::max())
            throw std::invalid_argument("Iterated too many times while trying to calculate order. The input may be corrupt.");
    }

    return order;
}

// -------------------------------------------------------------------------------------------------
bool Sym::EqualsIdentity(const Permutation& permutation)
{
    for (int i = 0; i < permutation.size(); i++)
    {
        if (permutation[i] != i + 1)
            return false;
    }

    return true;
}

// -------------------------------------------------------------------------------------------------
void Sym::SetToIdentity(Permutation& permutation)
{
    for (int i = 0; i < permutation.size(); i++)
    {
        permutation[i] = i + 1;
    }
}

// -------------------------------------------------------------------------------------------------
std::string Sym::GetCycleNotationString(const Permutation& permutation)
{
    std::string cycleString = "";

    std::unordered_set<int> numsFound;
    int n = permutation.size();

    for (int currNum = 1; currNum <= permutation.size(); currNum++)
    {
        // If this number has already been seen in some cycle, skip. In general, it's completely
        // possible and fine for a number to appear in multiple cycles. But here we will write the
        // permutation as a product of disjoint cycles (no common elements)
        if (numsFound.find(currNum) != numsFound.end())
        {
            continue;
        }

        // If this number is unmoved by the permutation (maps to itself), skip.
        // In cycle notation, those numbers are not written and are implied by context.
        if (currNum == permutation[currNum - 1])
        {
            continue;
        }

        // Traverse through the cycle that currNum is a part of
        int cycleStart = currNum;
        cycleString += "(";

        do
        {
            int iterations = 0;

            // Since this is a set, if this number has already been encountered, inserting again is a no-op
            numsFound.insert(currNum);

            cycleString += std::to_string(currNum) + " ";

            currNum = permutation[currNum - 1];

            if (iterations > permutation.size())
            {
                throw std::exception("Failed to generate cycle notation string for permutation.");
            }

            iterations++;
        }
        while(currNum != cycleStart);

        // After reaching the end of the cycle, close the parentheses
        cycleString.back() = ')';

    }

    // Special case: If provided the identity permutation, then the above loop skips every element.
    // But rather than return an empty string, we should return (1).
    if (cycleString == "")
    {
        cycleString = "(1)";
    }

    return cycleString;
}

// -------------------------------------------------------------------------------------------------
void Sym::ValidatePermutation(const Permutation& permutation)
{
    if (permutation.size() == 0)
        throw std::invalid_argument("Permutation is empty.");
    
    std::vector<bool> seenBefore(permutation.size(), false);

    for (std::uint32_t element : permutation)
    {
        if (element > permutation.size())
            throw std::invalid_argument("Permutation maps to a symbol outside its domain.");

        if (seenBefore[element - 1])
            throw std::invalid_argument("Permutation is not injective - it maps more than one symbol to the same image.");

        seenBefore[element - 1] = true;
    }
}
