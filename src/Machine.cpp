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

#include <archer/Machine.h>

ARCHER_NAMESPACE_BEGIN

Word assembly(Word instruction, Word processorRegister) {
    return (instruction << 12) | (processorRegister << 8);
}
Word assembly(InstructionType instruction, Word processorRegister, Word address) {
    return (instruction << 12) | (processorRegister << 8) | address;
}
Word assembly(Word instruction,
    Word processorRegister0, Word processorRegister1, Word processorRegister2) {
    return (instruction << 12) | (processorRegister0 << 8)
        | (processorRegister1 << 4) | processorRegister2;
}

Machine::Machine() {
    reset();
}
Machine::~Machine() {}

Word & Machine::operator [](UInteger index) {
    return memory[index];
}
const Word & Machine::operator [](UInteger index) const {
    return memory[index];
}
Machine & Machine::operator <<(Word rhs) {
    memory[heapSize + stackIndex] = rhs;
    stackIndex++;

    return *this;
}

Machine & Machine::run() {
    while (!processorRegister[AbortFlag]) {
        decode();
        processorRegister[ProgramCounter]++;

        execute();
    }

    return *this;
}
Machine & Machine::reset() {
    for (UInteger i = 0; i < processorRegister.size(); i++)
        processorRegister[i] = 0;

    for (UInteger i = 0; i < memory.size(); i++)
        memory[i] = 0;

    heapSize = 192;
    stackIndex = 0;

    processorRegister[ProgramCounter] = 0;

    return *this;
}

Machine & Machine::decode() {
    Word word = memory[processorRegister[ProgramCounter]];
    InstructionType instruction = (InstructionType)(word >> 12);

    switch (instruction) {
    case Load:
        break;
    case Store:
        break;
    case Move:
        break;
    case Set:
        break;
    case Clear:
        break;
    case Add:
        break;
    case Subtract:
        break;
    case Multiply:
        break;
    case Divide:
        break;
    case And:
        break;
    case Or:
        break;
    case Xor:
        break;
    case Compare:
        break;
    case Branch:
        break;
    default:
        processorRegister[AbortFlag] = true;
        break;
    }

    return *this;
}
Machine & Machine::execute() {
    InstructionType instruction = (InstructionType)processorRegister[Instruction];

    Word source0 = processorRegister[Source0];
    Word source1 = processorRegister[Source1];
    Word destination = processorRegister[Destination];

    switch (instruction) {
    case Load:
        break;
    case Store:
        break;
    case Move:
        break;
    case Set:
        break;
    case Clear:
        break;
    case Add:
        break;
    case Subtract:
        break;
    case Multiply:
        break;
    case Divide:
        break;
    case And:
        break;
    case Or:
        break;
    case Xor:
        break;
    case Compare:
        break;
    case Branch:
        break;
    default:
        processorRegister[AbortFlag] = true;
        break;
    }

    return *this;
}

ARCHER_NAMESPACE_END