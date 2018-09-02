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

#include <vector>
#include <fstream>
#include <sstream>

ARCHER_NAMESPACE_BEGIN

Memory::Memory() {}
Memory::~Memory() {}

Word & Memory::operator [](UInteger index) {
    return stack[index];
}
const Word & Memory::operator [](UInteger index) const {
    return stack[index];
}

const SymbolTable Machine::symbols = {
    { "ld", Load },
    { "st", Store },
    { "mov", Move },
    { "set", Set },
    { "add", Add },
    { "sub", Subtract },
    { "mul", Multiply },
    { "div", Divide },
    { "and", And },
    { "or", Or },
    { "xor", Xor },
    { "cmp", Compare },
    { "bch", Branch },
    { "pc", ProgramCounter },
    { "af", AbortFlag },
    { "r0", Register0 },
    { "r1", Register1 },
    { "r2", Register2 },
    { "r3", Register3 },
    { "r4", Register4 },
    { "r5", Register5 },
    { "r6", Register6 },
    { "r7", Register7 },
    { "r8", Register8 },
    { "r9", Register9 }
};

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

Boolean Machine::load(const String & filename) {
    std::ifstream file(filename, std::ifstream::in);

    if (!file.is_open())
        return false;

    String line;
    UInteger index = ARCGER_STACK_BEGIN;

    while (std::getline(file, line) && index != ARCHER_STACK_SIZE) {
        std::vector<UInteger> commandData;

        std::istringstream stream(line);
        String token;

        while (stream >> token) {
            if (token[0] == '#')
                break;

            SymbolTable::const_iterator it = symbols.find(token);
            commandData.push_back(it != symbols.end() ? it->second : std::stoull(token));
        }

        Word word;
        UInteger size = commandData.size();

        if (size == 3) {
            switch (commandData[0]) {
            case Load:
            case Store:
            case Set:
                word = assemblyA(commandData[0], commandData[1], commandData[2]);
                break;
            case Move:
                word = assemblyB(commandData[0], commandData[1], commandData[2]);
                break;
            default:
                return false;
            }
        }
        else if (size == 4) {
            switch (commandData[0]) {
            case Add:
            case Subtract:
            case Multiply:
            case Divide:
            case And:
            case Or:
            case Xor:
            case Compare:
            case Branch:
                word = assemblyC(commandData[0], commandData[1], commandData[2], commandData[3]);
                break;
            default:
                return false;
            }
        }
        else
            return false;

        memory[index++] = word;
    }

    return true;
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
    for (UInteger i = 0; i < ARCHER_REGISTER_SIZE; i++)
        processorRegister[i] = 0;

    for (UInteger i = 0; i < ARCHER_MEMORY_SIZE; i++)
        memory[i] = 0;

    processorRegister[ProgramCounter] = ARCGER_STACK_BEGIN;

    return *this;
}

Word Machine::assemblyA(Word mnemonic, Word operand0, Word operand1) const {
    return (mnemonic << 48) | (operand0 << 32) | operand1;
}
Word Machine::assemblyB(Word mnemonic, Word operand0, Word operand1) const {
    return (mnemonic << 48) | (operand0 << 32) | (operand1 << 16);
}
Word Machine::assemblyC(Word mnemonic, Word operand0, Word operand1, Word operand2) const {
    return (mnemonic << 48) | (operand0 << 32) | (operand1 << 16) | operand2;
}

void Machine::disassemblyA(Word word,
    Word & mnemonic, Word & operand0, Word & operand1) const {
    mnemonic = word >> 48;
    operand0 = (word >> 32) & 0x000000000000FFFF;
    operand1 = word & 0x00000000FFFFFFFF;
}
void Machine::disassemblyB(Word word,
    Word & mnemonic, Word & operand0, Word & operand1) const {
    mnemonic = word >> 48;
    operand0 = (word >> 32) & 0x000000000000FFFF;
    operand1 = (word >> 16) & 0x000000000000FFFF;
}
void Machine::disassemblyC(Word word,
    Word & mnemonic, Word & operand0, Word & operand1, Word & operand2) const {
    mnemonic = word >> 48;
    operand0 = (word >> 32) & 0x000000000000FFFF;
    operand1 = (word >> 16) & 0x000000000000FFFF;
    operand2 = word & 0x000000000000FFFF;
}

InstructionType Machine::disassemblyInstruction(Word word) const {
    return (InstructionType)(word >> 48);
}

Machine & Machine::decode() {
    Word mnemonic, operand0, operand1, operand2;

    Word word = memory[processorRegister[ProgramCounter]];
    processorRegister[Instruction] = disassemblyInstruction(word);

    switch (processorRegister[Instruction]) {
    case Load:
    case Store:
    case Set:
        disassemblyA(word, mnemonic, operand0, operand1);

        processorRegister[Operand0] = operand0;
        processorRegister[Operand1] = operand1;

        break;
    case Move:
        disassemblyB(word, mnemonic, operand0, operand1);

        processorRegister[Operand0] = operand0;
        processorRegister[Operand1] = operand1;

        break;
    case Add:
    case Subtract:
    case Multiply:
    case Divide:
    case And:
    case Or:
    case Xor:
    case Compare:
    case Branch:
        disassemblyC(word, mnemonic, operand0, operand1, operand2);

        processorRegister[Operand0] = operand0;
        processorRegister[Operand1] = operand1;
        processorRegister[Operand2] = operand2;

        break;
    default:
        processorRegister[AbortFlag] = ARCHER_TRUE;
        break;
    }

    return *this;
}
Machine & Machine::execute() {
    InstructionType instruction = (InstructionType)processorRegister[Instruction];

    Word operand0 = processorRegister[Operand0];
    Word operand1 = processorRegister[Operand1];
    Word operand2 = processorRegister[Operand2];

    switch (instruction) {
    case Load:
        processorRegister[operand0] = memory[operand1];
        break;
    case Store:
        memory[operand1] = processorRegister[operand0];
        break;
    case Move:
        processorRegister[operand0] = processorRegister[operand1];
        break;
    case Set:
        processorRegister[operand0] = operand1;
        break;
    case Add:
        processorRegister[operand0] = processorRegister[operand1] + processorRegister[operand2];
        break;
    case Subtract:
        processorRegister[operand0] = processorRegister[operand1] - processorRegister[operand2];
        break;
    case Multiply:
        processorRegister[operand0] = processorRegister[operand1] * processorRegister[operand2];
        break;
    case Divide:
        processorRegister[operand0] = processorRegister[operand1] / processorRegister[operand2];
        break;
    case And:
        processorRegister[operand0] = processorRegister[operand1] && processorRegister[operand2];
        break;
    case Or:
        processorRegister[operand0] = processorRegister[operand1] || processorRegister[operand2];
        break;
    case Xor:
        processorRegister[operand0] = processorRegister[operand1] ^ processorRegister[operand2];
        break;
    case Compare:
        processorRegister[operand0] = processorRegister[operand1] == processorRegister[operand2];
        break;
    case Branch:
        if (processorRegister[operand0])
            processorRegister[operand1] = processorRegister[operand2];

        break;
    default:
        processorRegister[AbortFlag] = ARCHER_TRUE;
        break;
    }

    return *this;
}

ARCHER_NAMESPACE_END