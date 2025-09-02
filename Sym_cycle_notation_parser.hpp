/*
    Author: Ryan Patrick
    Timestamp: 01-Sep-2025
    Purpose: Declarations of routines for use by the cycle notation parser
 */

#include "Sym_data_types.hpp"

/* Interface to the scanner*/
void yyerror(const char* s);

//class PermutationComposition
//{
//public:
//    PermutationComposition(PermutationComposition* left, PermutationComposition* right) : m_left(left), m_right(right) {};
//    
//    PermutationComposition* m_left;
//    PermutationComposition* m_right;
//};

struct NumNode
{
    NumNode(int number, NumNode* next) : m_number(number), m_next(next) {};

    int m_number;
    NumNode* m_next;
};

NumNode* AddNodeToTail(NumNode* head, int value);

void PrintNumNodeList(NumNode* head);

//Permutation EvaluateComposition(PermutationComposition* comp);
