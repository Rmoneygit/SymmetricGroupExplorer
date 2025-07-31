/*
    Author: Ryan Patrick
    Timestamp: 26-Jul-2025
    Purpose: Definitions of routines for constructing and controlling windows
 */

// IMGUI 3rd-party library includes
#include "imgui.h"
#include "imgui_internal.h"

// CppTrace 3rd-party library includes
#include <cpptrace/from_current.hpp>
#include <cpptrace/from_current_macros.hpp>

// Normal includes
#include "Sym_data_types.h"
#include "Sym_errors.h"
#include "Sym_symmetric_group.h"
#include "SymUI_data_types.h"
#include "SymUI_error_presentation.h"
#include "SymUI_input_processing.h"
#include "SymUI_windows.h"

// Standard library includes
#include <iostream>
#include <string>
#include <vector>

void SymUI::MainWindow()
{
    static bool showCalculator = false;
    static bool showOrder = false;

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::MenuItem("Calculator"))
        {
            showCalculator = true;
        }
        if (ImGui::MenuItem("Order"))
        {
            showOrder = true;
        }
        ImGui::EndMainMenuBar();
    }

    if (showCalculator)
    {
        CPPTRACE_TRY
        {
            SymUI::CalculatorWindow(showCalculator);
        }
        CPPTRACE_CATCH(const std::exception & e)
        {
            std::string errorMsg = "Unhandled exception encountered in CalculatorWindow: ";
            Sym::PrintErrorToStdErrorStream(e, errorMsg);
            SymUI::ShowErrorPopup(e, errorMsg);
        }
    }

    if (showOrder)
    {
        CPPTRACE_TRY
        {
            SymUI::OrderWindow(showOrder);
        }
        CPPTRACE_CATCH(const std::exception & e)
        {
            std::string errorMsg = "Unhandled exception encountered in OrderWindow: ";
            Sym::PrintErrorToStdErrorStream(e, errorMsg);
            SymUI::ShowErrorPopup(e, errorMsg);
        }
    }
}

void SymUI::CalculatorWindow(bool& showWindow)
{
    static int n = 3;
    static int prevN = 3;
    static Sym::Permutation inputBuffer1 = InitializePermutation(n);
    static Sym::Permutation inputBuffer2 = InitializePermutation(n);
    static Sym::Permutation permutation1 = InitializePermutation(n);
    static Sym::Permutation permutation2 = InitializePermutation(n);
    static Sym::Permutation composition = InitializePermutation(n);
    static Sym::PermutationVector permVector = { &inputBuffer1, &inputBuffer2, &permutation1, &permutation2, &composition };
    static bool dataChanged = false;
    static InputMode inputMode = TABLE;
    std::vector<ImVec2> perm2InputPositions;
    std::vector<ImVec2> perm1LabelPositions;

    ImGui::Begin("Calculator", &showWindow, ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::MenuItem("Table Notation"))
        {
            inputMode = TABLE;
        }
        if (ImGui::MenuItem("Cycle Notation"))
        {
            inputMode = CYCLE;
        }
        ImGui::EndMenuBar();
    }

    dataChanged = SymUI::PermutationSizeSlider(n, prevN, permVector);

    if (inputMode == TABLE)
    {
        ImGui::Text("Permutation 2");
        if (ImGui::BeginTable("permutation2Table", n, ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
        {
            for (int i = 0; i < n; i++)
            {
                char label[32];
                sprintf_s(label, "%d", i + 1);
                ImGui::TableNextColumn();
                ImGui::Text(label);
            }

            ImGui::TableNextRow();

            for (int i = 0; i < n; i++)
            {
                ImGui::TableNextColumn();
                // '##hidden' tells imgui to not show the label. But it still needs a unique label to internally identify the input object
                std::string labelText = "##hidden Perm2Input " + std::to_string(i + 1);
                const char* label = labelText.c_str();
                // 0 step and 0 step_fast indicate "no plus or minus buttons".
                if (ImGui::InputInt(label, &inputBuffer2[i], 0, 0))
                {
                    CPPTRACE_TRY
                    {
                        SymUI::ProcessPermutationInput(i, inputBuffer2, permutation2);
                        dataChanged = true;
                    }
                    CPPTRACE_CATCH(const std::exception& e)
                    {
                        std::string errorMsg = "Exception encountered while processing permutation input: ";
                        Sym::PrintErrorToStdErrorStream(e, errorMsg);
                        SymUI::ShowErrorPopup(e, errorMsg);
                    }
                }

                ImRect cellRect = SymUI::GetTableCellRect();
                ImVec2 middleBottom = ImVec2((cellRect.Max.x + cellRect.Min.x) / 2, cellRect.Max.y);
                perm2InputPositions.push_back(middleBottom);
            }

            ImGui::EndTable();
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Text("Permutation 1");
        if (ImGui::BeginTable("permutation1Table", n, ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
        {
            for (int i = 0; i < n; i++)
            {
                char label[32];
                sprintf_s(label, "%d", i + 1);
                ImGui::TableNextColumn();
                ImGui::Text(label);
                ImRect cellRect = SymUI::GetTableCellRect();
                ImVec2 middleTop = ImVec2((cellRect.Max.x + cellRect.Min.x) / 2, cellRect.Min.y);
                perm1LabelPositions.push_back(middleTop);
            }

            for (int i = 0; i < n; i++)
            {
                ImGui::TableNextColumn();
                // '##hidden' tells imgui to not show the label. But it still needs a unique label to internally identify the input object
                std::string labelText = "##hidden Perm1Input " + std::to_string(i + 1);
                const char* label = labelText.c_str();
                // 0 step and 0 step_fast indicate "no plus or minus buttons".
                if (ImGui::InputInt(label, &inputBuffer1[i], 0, 0))
                {
                    CPPTRACE_TRY
                    {
                        SymUI::ProcessPermutationInput(i, inputBuffer1, permutation1);
                        dataChanged = true;
                    }
                    CPPTRACE_CATCH(const std::exception & e)
                    {
                        std::string errorMsg = "Exception encountered while processing permutation input: ";
                        Sym::PrintErrorToStdErrorStream(e, errorMsg);
                        SymUI::ShowErrorPopup(e, errorMsg);
                    }
                }
            }

            ImGui::EndTable();
        }

    }
    else if (inputMode == CYCLE)
    {
        ImGui::Text("Permutation 1");
        char* rawCycleInput = new char[30];
        if (ImGui::InputText("Permutation1 Cycle Input", rawCycleInput, 30))
        {
            int i = 0;
            while (rawCycleInput[i] != '\0');
            {
                i++;
            }
        }
    }

    //for (int i = 0; i < n; i++)
    //{
    //    int val = permutation2[i];
    //    SymUI::DrawArrowBetweenPoints(perm2InputPositions[i], perm1LabelPositions[val - 1], ImColor(255.0f, 0.0f, 0.0f));
    //}

    ImGui::Spacing();

    if (ImGui::Button("Commute"))
    {
        CPPTRACE_TRY
        {
            Sym::CommutePermutations(permutation1, permutation2);
            dataChanged = true;
        }
        CPPTRACE_CATCH(const std::exception& e)
        {
            std::string errorMsg = "Exception encountered while executing \"Commute\" command: ";
            Sym::PrintErrorToStdErrorStream(e, errorMsg);
            SymUI::ShowErrorPopup(e, errorMsg);
        }
    }

    ImGui::SameLine(85);

    if (ImGui::Button("Use Output"))
    {
        CPPTRACE_TRY
        {
            // This transfers values to the internal data structure
            SymUI::CopyPermutation(permutation1, composition);
            dataChanged = true;
        }
        CPPTRACE_CATCH(const std::exception& e)
        {
            std::string errorMsg = "Exception encountered while executing \"Use Output\" command: ";
            Sym::PrintErrorToStdErrorStream(e, errorMsg);
            SymUI::ShowErrorPopup(e, errorMsg);
        }
    }

    ImGui::SameLine(180);

    if (ImGui::Button("Reset"))
    {
        CPPTRACE_TRY
        {
            for (Sym::Permutation* permutation : permVector)
            {
                n = 3;
                prevN = 3;
                permutation->resize(3);
                Sym::SetToIdentity(*permutation);
            }
            dataChanged = true;
        }
        CPPTRACE_CATCH(const std::exception& e)
        {
            std::string errorMsg = "Exception encountered while executing \"Reset\" command: ";
            Sym::PrintErrorToStdErrorStream(e, errorMsg);
            SymUI::ShowErrorPopup(e, errorMsg);
        }
    }

    if (dataChanged)
    {
        CPPTRACE_TRY
        {
            // This transfers values to the input fields so the change is visible to the user
            SymUI::CopyPermutation(inputBuffer1, permutation1);
            SymUI::CopyPermutation(inputBuffer2, permutation2);

            composition = Sym::ComposePermutations(permutation1, permutation2);
            dataChanged = false;
        }
        CPPTRACE_CATCH(const std::exception& e)
        {
            std::string errorMsg = "Exception encountered while trying to update internal data model: ";
            Sym::PrintErrorToStdErrorStream(e, errorMsg);
            SymUI::ShowErrorPopup(e, errorMsg);
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::Text("Composition");
    if (ImGui::BeginTable("compositionTable", static_cast<int>(composition.size()), ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
    {
        for (int i = 0; i < composition.size(); i++)
        {
            char label[32];
            sprintf_s(label, "%d", i + 1);
            ImGui::TableNextColumn();
            ImGui::Text(label);
        }

        ImGui::TableNextRow();

        for (int i = 0; i < composition.size(); i++)
        {
            char label[32];
            sprintf_s(label, "%d", composition[i]);
            ImGui::TableNextColumn();
            ImGui::Text(label);
        }
        ImGui::EndTable();
    }

    ImGui::End();
}

void SymUI::OrderWindow(bool& showWindow)
{
    static int n = 3;
    static int prevN = 3;
    static Sym::Permutation inputBuffer = InitializePermutation(n);
    static Sym::Permutation permutation = InitializePermutation(n);
    static Sym::PermutationVector permVector = { &inputBuffer, &permutation };
    static int order = 1;

    ImGui::Begin("Order", &showWindow);

    PermutationSizeSlider(n, prevN, permVector);

    if (ImGui::BeginTable("orderPermutationTable", n, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
    {
        for (int i = 0; i < n; i++)
        {
            char label[32];
            sprintf_s(label, "%d", i + 1);
            ImGui::TableNextColumn();
            ImGui::Text(label);
        }

        ImGui::TableNextRow();

        for (int i = 0; i < n; i++)
        {
            ImGui::TableNextColumn();
            // '##hidden' tells imgui to not show the label. But it still needs a unique label to internally identify the input object
            std::string labelText = "##hidden OrderPermInput " + std::to_string(i + 1);
            const char* label = labelText.c_str();
            // 0 step and 0 step_fast indicate "no plus or minus buttons".
            if (ImGui::InputInt(label, &inputBuffer[i], 0, 0))
            {
                CPPTRACE_TRY
                {
                    ProcessPermutationInput(i, inputBuffer, permutation);
                }
                CPPTRACE_CATCH(const std::exception & e)
                {
                    std::string errorMsg = "Exception encountered while processing permutation input: ";
                    Sym::PrintErrorToStdErrorStream(e, errorMsg);
                    SymUI::ShowErrorPopup(e, errorMsg);
                }
            }
        }
    }
    ImGui::EndTable();

    if (ImGui::Button("Calculate Order"))
    {
        CPPTRACE_TRY
        {
            order = Sym::CalculateOrder(permutation);
        }
        CPPTRACE_CATCH(const std::exception & e)
        {
            std::string errorMsg = "Exception encountered while executing command \"Calculate Order\": ";
            Sym::PrintErrorToStdErrorStream(e, errorMsg);
            SymUI::ShowErrorPopup(e, errorMsg);
        }
    }

    ImGui::Text("Order: %d", order);

    ImGui::End();
}

bool SymUI::PermutationSizeSlider(int& n, int& prevN, Sym::PermutationVector& permVec)
{
    bool dataChanged = false;

    // The slider returns true if the value changed
    std::string label = "Symbols";
    if (ImGui::SliderInt(label.c_str(), &n, 1, 20))
    {
        dataChanged = true;

        if (prevN < n)
        {
            // Fill out the new cells at the end of the permutations with a default value
            for (int i = prevN; i < n; i++)
            {
                for (Sym::Permutation* permutation : permVec)
                {
                    permutation->push_back(i + 1);
                }
            }
        }

        if (prevN > n)
        {
            // If the permutation got smaller, there could be cells which contain values too large now.
            for (int i = 0; i < prevN - n; i++)
            {
                for (Sym::Permutation* permutation : permVec)
                {
                    ShrinkPermutationByOne(*permutation);
                }
            }
        }

        prevN = n;
    }

    return dataChanged;
}

void SymUI::DrawArrowBetweenPoints(ImVec2 source, ImVec2 dest, ImU32 color, float arrowSize, float lineThickness)
{
    ImDrawList* drawList = ImGui::GetForegroundDrawList();

    //ImVec2 direction = ImVec2(dest.x - source.x, dest.y - source.y);
    //float length = sqrtf(direction.x * direction.x + direction.y * direction.y); // Distance formula

    drawList->AddLine(source, dest, color, lineThickness);
}

ImRect SymUI::GetTableCellRect()
{
    ImGuiContext& g = *GImGui;
    ImGuiTable* table = g.CurrentTable;

    if (!table) {
        return ImRect(ImVec2(0, 0), ImVec2(0, 0));
    }

    int column = table->CurrentColumn;

    float x1 = table->Columns[column].MinX;
    float x2 = table->Columns[column].MaxX;

    float y1 = table->RowPosY1;
    float y2 = table->RowPosY2;

    return ImRect(ImVec2(x1, y1), ImVec2(x2, y2));
}
