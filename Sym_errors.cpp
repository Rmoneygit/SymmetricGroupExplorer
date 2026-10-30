/*
    Author: Ryan Patrick
    Timestamp: 27-Jul-2025
    Purpose: Declarations of routines for error handling
 */

// Cpptrace 3rd-party library includes
#include <cpptrace/basic.hpp>
#include <cpptrace/formatting.hpp>
#include <cpptrace/from_current.hpp>

// Normal includes
#include "Sym_data_types.hpp"
#include "Sym_errors.hpp"

// Standard library includes
#include <exception>
#include <iostream>
#include <string>

void Sym::PrintErrorToStdErrorStream(const std::exception& e, const std::string message)
{
	std::cerr << message << e.what() << std::endl;
    Sym::GetGlobalCppTraceFormatter()->print(cpptrace::from_current_exception());
}

void Sym::PrintDebugErrorToStdErrorStream(const Sym::DebugException& e, const std::string message)
{
    std::cerr << message << e.GetDebugMessage() << std::endl;
    Sym::GetGlobalCppTraceFormatter()->print(cpptrace::from_current_exception());
}

const cpptrace::formatter* Sym::GetGlobalCppTraceFormatter()
{
    static cpptrace::formatter formatterObj;
    return &(formatterObj.paths(cpptrace::formatter::path_mode::basename)
                .symbols(cpptrace::formatter::symbol_mode::pretty));
}

std::string Sym::GetDebugString(const Sym::Permutation& permutation)
{
    std::string debugStr("{ ");
    for (int i = 0; i < permutation.size(); i++)
    {
        debugStr += "[" + std::to_string(i) + "]: " + std::to_string(permutation[i]) + ", ";
    }
    debugStr += "}";

    return debugStr;
}

void Sym::ProtectedCall(const std::function<void()>& callable, const std::string& contextErrMsg)
{
    cpptrace::try_catch(
        callable,
        [&](const Sym::DebugException& e) {
            Sym::PrintDebugErrorToStdErrorStream(e, contextErrMsg);
        },
        [&](const std::exception& e) {
            Sym::PrintErrorToStdErrorStream(e, contextErrMsg);
        }
    );
}
