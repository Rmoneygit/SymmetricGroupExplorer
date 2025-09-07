/*
    Author: Ryan Patrick
    Timestamp: 01-Sep-2025
    Purpose: Declarations of routines for use by the cycle notation parser
 */

#pragma once

#include "Sym_data_types.hpp"

namespace Sym
{

    static int s_numSymbols = 3;

    struct NumNode
    {
        NumNode(int number, NumNode* next) : m_number(number), m_next(next) {};

        int m_number;
        NumNode* m_next;
    };

    NumNode* AddNodeToTail(NumNode* head, int value);

    void PrintNumNodeList(NumNode* head);

    void FreeNumNodeList(NumNode* head);

    PermutationVector* AddCycleToTail(PermutationVector* vec, Permutation* perm);

    Permutation* CreatePermutation(NumNode* head);
}
