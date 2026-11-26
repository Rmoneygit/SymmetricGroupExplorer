/*
    Author: Ryan Patrick
    Timestamp: Sep-29-2024
    Purpose: Implementations of routines for core algorithms dealing with the symmetric group.
 */

#include <cstdlib>
#include <cstdint>
#include <limits>
#include <numeric>
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

    for (std::uint32_t i = 0; i < permutation2.size(); i++)
    {
        result[i] = permutation1[permutation2[i] - 1];
    }

    return result;
}

// -------------------------------------------------------------------------------------------------
Permutation Sym::ComposePermutations(const PermutationPtrVector& permutations)
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

    for (std::uint32_t i = 0; i < permutation1.size(); i++)
    {
        std::uint32_t temp = permutation1[i];
        permutation1[i] = permutation2[i];
        permutation2[i] = temp;
    }
}

// -------------------------------------------------------------------------------------------------
// This method leverages this theorem: The order of a permutation f in S_n is the least common multiple
// of the lengths of the disjoint cycles whose product is f.
std::uint64_t Sym::CalculateOrder(const Permutation& permutation)
{
    Sym::ValidatePermutation(permutation);
    
    std::uint64_t order = 1;
    std::unordered_set<std::uint32_t> numsFound;

    // Traverse each disjoint cycle in the permutation
    for (std::uint32_t currNum = 1; currNum <= permutation.size(); currNum++)
    {
        // If this number has already been seen in some cycle, skip.
        if (numsFound.find(currNum) != numsFound.end())
        {
            continue;
        }

        // Traverse through the cycle that currNum is a part of
        std::uint32_t cycleStart = currNum;
        std::size_t cycleLength = 0;

        do
        {
            // Since this is a set, if this number has already been encountered, inserting again is a no-op
            numsFound.insert(currNum);

            currNum = permutation[currNum - 1];

            if (cycleLength > permutation.size())
            {
                throw std::exception("Iterated too many times while trying to find the order of the permutation.");
            }

            cycleLength++;
        } while (currNum != cycleStart);

        // The below code utilizes this formula:
        // lcm(a, b) = |ab|/gcd(a, b)
        //
        // We can keep writing back into the variable "order" because by definition,
        // lcm(a, b, c) = lcm(lcm(a, b), c)
        const auto greatestCommonDivisor = std::gcd(order, cycleLength);
        const auto reducedOrder = order / greatestCommonDivisor;

        // Before computing reducedOrder * length, check if the multiplication would cause integer overflow.
        if (reducedOrder > std::numeric_limits<std::uint64_t>::max() / cycleLength)
        {
            throw std::overflow_error("Permutation order exceeds max uint64_t.");
        }


        order = reducedOrder * cycleLength;
    }

    return order;
}

// -------------------------------------------------------------------------------------------------
bool Sym::EqualsIdentity(const Permutation& permutation)
{
    for (std::uint32_t i = 0; i < permutation.size(); i++)
    {
        if (permutation[i] != i + 1)
            return false;
    }

    return true;
}

// -------------------------------------------------------------------------------------------------
void Sym::SetToIdentity(Permutation& permutation)
{
    for (std::uint32_t i = 0; i < permutation.size(); i++)
    {
        permutation[i] = i + 1;
    }
}

// -------------------------------------------------------------------------------------------------
std::string Sym::GetCycleNotationString(const Permutation& permutation)
{
    std::string cycleString = "";
    std::unordered_set<std::uint32_t> numsFound;

    for (std::uint32_t currNum = 1; currNum <= permutation.size(); currNum++)
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
        std::uint32_t cycleStart = currNum;
        cycleString += "(";

        do
        {
            std::size_t iterations = 0;

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

// -------------------------------------------------------------------------------------------------
PermutationUnorderedSet Sym::FindGeneratedSubgroup(const PermutationUnorderedSet& subset)
{
    if (subset.empty())
        throw std::invalid_argument("No subgroup is generated by the empty set!");
    
    const std::size_t permutationSize = subset.begin()->size();

    for (const Permutation& element : subset)
    {
        ValidatePermutation(element);

        if (element.size() != permutationSize)
            throw std::invalid_argument("Permutations in the subset must have the same size");
    }

    Permutation identity(permutationSize);
    SetToIdentity(identity);

    PermutationUnorderedSet subgroup;
    subgroup.insert(identity);

    PermutationUnorderedSet newElements = subset;
    while (!newElements.empty())
    {
        const PermutationUnorderedSet elementsToProcess = newElements;
        const PermutationUnorderedSet subgroupSnapshot = subgroup;
        newElements.clear();
        for (const Permutation& element : elementsToProcess)
        {
            for (const Permutation& member : subgroupSnapshot)
            {
                Permutation composition = ComposePermutations(element, member);
                const auto result = subgroup.insert(composition);

                if (result.second)
                    newElements.insert(composition);
            }
        }
    }

    return subgroup;
}
