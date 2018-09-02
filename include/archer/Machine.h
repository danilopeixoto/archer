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

#include <unordered_map>

#define ARCHER_STACK_SIZE 128
#define ARCHER_DATA_SIZE 256
#define ARCHER_MEMORY_SIZE (ARCHER_STACK_SIZE + ARCHER_DATA_SIZE)
#define ARCHER_REGISTER_SIZE 16
#define ARCGER_STACK_BEGIN 0
#define ARCHER_DATA_BEGIN ARCHER_STACK_SIZE

ARCHER_NAMESPACE_BEGIN

typedef UInteger64 Word;

typedef Word StackSegment[ARCHER_STACK_SIZE];
typedef Word DataSegment[ARCHER_DATA_SIZE];
typedef Word ProcessorRegister[ARCHER_REGISTER_SIZE];

typedef std::unordered_map<String, UInteger> SymbolTable;

struct Memory {
    StackSegment stack;
    DataSegment data;

    Memory();
    ~Memory();

    Word & operator [](UInteger);
    const Word & operator [](UInteger) const;
};

enum InstructionType {
    Load = 0,
    Store,
    Move,
    Set,
    Add,
    Subtract,
    Multiply,
    Divide,
    And,
    Or,
    Xor,
    Less,
    Greater,
    Equal,
    Branch
};

enum RegisterType {
    ProgramCounter = 0,
    Instruction,
    Operand0,
    Operand1,
    Operand2,
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

class Machine {
public:
    Machine();
    ~Machine();

    Word & operator [](UInteger);
    const Word & operator [](UInteger) const;

    Boolean load(const String &);
    Machine & run();
    Machine & reset();

private:
    static const SymbolTable symbols;

    ProcessorRegister processorRegister;
    Memory memory;

    Word assemblyA(Word, Word, Word) const;
    Word assemblyB(Word, Word, Word) const;
    Word assemblyC(Word, Word, Word, Word) const;

    void disassemblyA(Word, Word &, Word &, Word &) const;
    void disassemblyB(Word, Word &, Word &, Word &) const;
    void disassemblyC(Word, Word &, Word &, Word &, Word &) const;

    InstructionType disassemblyInstruction(Word) const;

    Machine & decode();
    Machine & execute();
};

ARCHER_NAMESPACE_END

#endif