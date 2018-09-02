// Copyright (c) 2018, Danilo Peixoto. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef ARCHER_GLOBAL_H
#define ARCHER_GLOBAL_H

#define ARCHER_NAME "Archer"
#define ARCHER_VERSION "1.0.0"
#define ARCHER_AUTHOR "Danilo Peixoto"
#define ARCHER_COPYRIGHT "Copyright (c) 2018, Danilo Peixoto. All rights reserved."
#define ARCHER_LICENSE "BSD-3-Clause License"

#define ARCHER_VERSION_MAJOR 1
#define ARCHER_VERSION_MINOR 0
#define ARCHER_VERSION_PATCH 0

#define ARCHER_NAMESPACE_BEGIN namespace archer {
#define ARCHER_NAMESPACE_END };
#define ARCHER_NAMESPACE_USING using namespace archer;

#define ARCHER_FALSE 0
#define ARCHER_TRUE 1

#define ARCHER_NULL nullptr

#include <string>

ARCHER_NAMESPACE_BEGIN

typedef void Void;
typedef unsigned char UCharacter;
typedef char Character;
typedef UCharacter Byte;
typedef bool Boolean;
typedef uint8_t UInteger8;
typedef uint16_t UInteger16;
typedef uint32_t UInteger32;
typedef uint64_t UInteger64;
typedef UInteger64 UInteger;
typedef int8_t Integer8;
typedef int16_t Integer16;
typedef int32_t Integer32;
typedef int64_t Integer64;
typedef Integer64 Integer;
typedef float Float32;
typedef double Float64;
typedef Float64 Float;
typedef std::string String;

ARCHER_NAMESPACE_END

#endif