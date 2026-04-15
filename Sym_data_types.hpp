/*
    Author: Ryan Patrick
    Timestamp: Jun-26-2025
    Purpose: Type declarations for the core code
 */

#pragma once

#include <vector>
#include <cstdint>

namespace Sym
{
	using Permutation = std::vector<std::uint32_t>;
	using PermutationVector = std::vector<Permutation*>;
}
