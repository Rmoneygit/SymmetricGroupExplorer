/*
    Author: Ryan Patrick
    Timestamp: Jun-26-2025
    Purpose: Type declarations for the core code
 */

#pragma once

#include <cstdint>
#include <vector>
#include <unordered_set>

namespace Sym
{
	using Permutation = std::vector<std::uint32_t>;
	using PermutationVector = std::vector<Permutation>;
	using PermutationPtrVector = std::vector<Permutation*>;
	using PermutationUnorderedSet = std::unordered_set<Permutation>;
}
