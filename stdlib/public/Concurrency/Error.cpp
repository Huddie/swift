//===--- Error.cpp - Error handling support code --------------------------===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#include "swift/Threading/Errors.h"
#include <cstdio>

#include "Error.h"

// swift::fatalError is not exported from libswiftCore and not shared, so define another
// internal function instead.
SWIFT_NORETURN
SWIFT_VFORMAT(2)
void swift::swift_Concurrency_fatalErrorv(uint32_t flags, const char *format,
                                          va_list val) {
  vfprintf(stderr, format, val);
  abort();
}

SWIFT_NORETURN
SWIFT_FORMAT(2, 3)
void swift::swift_Concurrency_fatalError(uint32_t flags, const char *format,
                                         ...) {
  va_list val;

  va_start(val, format);
  swift_Concurrency_fatalErrorv(flags, format, val);
}

#if !SWIFT_BUILD_STATIC_STDLIB
// Handle fatal errors from the threading library
SWIFT_ATTRIBUTE_NORETURN
SWIFT_FORMAT(1, 2)
void swift::threading::fatal(const char *format, ...) {
  va_list val;

  va_start(val, format);
  swift_Concurrency_fatalErrorv(0, format, val);
}
#endif // !SWIFT_BUILD_STATIC_STDLIB
