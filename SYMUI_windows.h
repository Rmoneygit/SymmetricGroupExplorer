/*
    Author: Ryan Patrick
    Timestamp: Jul-26-2025
    Purpose: Declarations of routines for constructing and controlling windows
 */

#pragma once

#include "imgui.h"
#include "imgui_internal.h"

#include "SYM_data_types.h"

namespace SymUI
{
    void CalculatorWindow(bool& showWindow);

    void OrderWindow(bool& showWindow);

    bool PermutationSizeSlider(int& n, int& prevN, Sym::PermutationVector& permVec);

    void DrawArrowBetweenPoints(ImVec2 source, ImVec2 dest, ImU32 color = IM_COL32_BLACK, float arrowSize = 10.0f, float lineThickness = 2.0f);
    
    ImRect GetTableCellRect();
}