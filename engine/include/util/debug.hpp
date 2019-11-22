////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>
#include <cassert>

#define __TRACE         __FILE__ << ":" << __LINE__ << ":" << __func__ << ": "
#define __MESSAGE(m)    __TRACE << m << std::endl

#define __INFOSTREAM    std::cout << "INFO: "
#define __ERRSTREAM     std::cerr << "ERROR: "
#define __WARNSTREAM    std::cerr << "WARNING: "
#define __DEBUGSTREAM   std::clog << "DEBUG: "

#define STDINFO(m)      (__INFOSTREAM  << __MESSAGE(m))
#define STDERR(m)       (__ERRSTREAM   << __MESSAGE(m))
#define STDWARN(m)      (__WARNSTREAM  << __MESSAGE(m))
#define STDDEBUG(m)     (__DEBUGSTREAM << __MESSAGE(m))

#define OBJ_STDINFO(m)  (__INFOSTREAM  << __MESSAGE(this << ": " << m))
#define OBJ_STDERR(m)   (__ERRSTREAM   << __MESSAGE(this << ": " << m))
#define OBJ_STDWARN(m)  (__WARNSTREAM  << __MESSAGE(this << ": " << m))
#define OBJ_STDDEBUG(m) (__DEBUGSTREAM << __MESSAGE(this << ": " << m))