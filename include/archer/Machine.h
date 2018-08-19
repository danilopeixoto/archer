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

#ifndef ARCHER_MACHINE_H
#define ARCHER_MACHINE_H

#include <archer/Global.h>

ARCHER_NAMESPACE_BEGIN

typedef UInteger16 Word;

enum InstructionType {
    Load = 0,
    Store,
    Move,
    Set,
    Clear,
    Add,
    Subtract,
    Multiply,
    Divide,
    And,
    Or,
    Xor,
    Compare,
    Branch
};

enum RegisterType {
    ProgramCounter = 0,
    Instruction,
    Source0,
    Source1,
    Destination,
    AbortFlag,
    Register0,
    Register1,
    Register2,
    Register3,
    Register4,
    Register5,
    Register6,
    Register7,
    Register8,
    Register9
};

Word assembly(InstructionType, Word);
Word assembly(InstructionType, Word, Word);
Word assembly(InstructionType, Word, Word, Word);

class Machine {
public:
    Machine();
    ~Machine();

    Word & operator [](UInteger);
    const Word & operator [](UInteger) const;
    Machine & operator <<(Word);

    Machine & run();
    Machine & reset();

private:
    typedef Array<Word, 16> Register;
    typedef Array<Word, 256> Memory;

    UInteger heapSize, stackIndex;

    Register processorRegister;
    Memory memory;

    Machine & decode();
    Machine & execute();
};

ARCHER_NAMESPACE_END

#endif