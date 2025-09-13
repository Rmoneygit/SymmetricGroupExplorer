/*
    Author: Ryan Patrick
    Timestamp: Jul-26-2025
    Purpose: Declarations of routines for constructing and controlling windows
 */

#pragma once

#include "imgui.h"
#include "imgui_internal.h"

#include "Sym_data_types.hpp"

namespace SymUI
{
    // Creates and manages the main window along with all subwindows in the program
    void MainWindow();
    
    // Creates and manages the window which is used to calculate the composition of permutations
    void CalculatorWindow(bool& showWindow);

    // Creates and manages the window which is used to calculate the order of a permutation.
    // The order of a permutation p is the smallest positive integer exponent n such that p^n = i,
    // where i is the identity permutation.
    void OrderWindow(bool& showWindow);

    // Creates a slider widget which controls the number of symbols in each permutation for the current window.
    // The current window is whatever ImGUI window code block this has been invoked inside of. So, it's intended
    // to be called in between a ImGui::Begin and ImGui::End function call.
    bool PermutationSizeSlider(int& n, int& prevN, Sym::PermutationVector& permVec);

    // Does what it says on the tin
    void DrawArrowBetweenPoints(ImVec2 source, ImVec2 dest, ImU32 color = IM_COL32_BLACK, float arrowSize = 10.0f, float lineThickness = 2.0f);
    
    // This is intended to be called inside of a ImGui::BeginTable block. It will return position and size information of the current table
    ImRect GetTableCellRect();

    void AboutWindow(bool& showWindow);
}
