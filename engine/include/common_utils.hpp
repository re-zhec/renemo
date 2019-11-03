////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>

#define MESSAGE(m) __FILE__ << ":" << __LINE__ << ":" << __func__ << ": " << m
#define STDINFO(m) (std::cout << "INFO: " << MESSAGE(m) << std::endl)
#define STDERR(m)  (std::cerr << "ERROR: " << MESSAGE(m) << std::endl)
#define STDWARN(m) (std::cerr << "WARNING: " << MESSAGE(m) << std::endl)