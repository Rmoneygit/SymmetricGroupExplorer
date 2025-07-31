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
#include "Sym_errors.h"

// Standard library includes
#include <exception>
#include <iostream>
#include <string>

void Sym::PrintErrorToStdErrorStream(const std::exception& e, const std::string message)
{
	std::cerr << message << e.what() << std::endl;
    Sym::GetGlobalCppTraceFormatter()->print(cpptrace::from_current_exception());
}

const cpptrace::formatter* Sym::GetGlobalCppTraceFormatter()
{
    static cpptrace::formatter formatterObj;
    return &(formatterObj.paths(cpptrace::formatter::path_mode::basename)
                .symbols(cpptrace::formatter::symbol_mode::pretty));
}
