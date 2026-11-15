/*
    Author: Ryan Patrick
    Timestamp: Jun-26-2025
    Purpose: Type declarations for the core code
 */

#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <unordered_set>

namespace Sym
{
	using Permutation = std::vector<std::uint32_t>;
	using PermutationVector = std::vector<Permutation>;
	using PermutationPtrVector = std::vector<Permutation*>;

	struct PermutationHash
	{
		std::size_t operator()(const Permutation& permutation) const noexcept
		{
			// This constant is (2^32)/phi, where phi is the golden ratio (sqrt(5) + 1)/2
			// It is commonly used in hashing due to having nice scattering properties
			constexpr std::size_t hashCombineConstant = 0x9e3779b9;
			std::size_t seed = permutation.size();

			for (const std::uint32_t value : permutation)
			{
				// Bitwise XOR assignment operator ^=. Seed << 6 moves bits upward, while
				// seed >> 2 moves bits downward. The addition and XOR help spread changes
				// across the result. The empty braces {} initialize the hash, and (value) calls
				// its operator() implementation to produce the hash.
				seed ^= std::hash<std::uint32_t>{}(value)
					+ hashCombineConstant
					+ (seed << 6)
					+ (seed >> 2);
			}

			return seed;
		}
	};

	using PermutationUnorderedSet = std::unordered_set<Permutation, PermutationHash>;
}
