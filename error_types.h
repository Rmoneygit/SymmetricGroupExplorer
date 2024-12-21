/*
    Author: Ryan Patrick
    Timestamp: Dec-20-2024
    Purpose: Types and macros for error handling
 */

#define ERROR_PROTECT try {

#include <iostream>

#define ERROR_CATCH } catch (const std::invalid_argument& e) { \
            std::cerr << "Error: " << e.what() << std::endl; \
                                                           } \
         catch (...) { \
            std::cerr << "An unexpected error occurred." << std::endl; \
            }