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

#include <archer/Archer.h>

#include <iostream>

ARCHER_NAMESPACE_USING

int main(int argc, char ** argv) {
    // A machine with 16 x 8 bits processor registers and 256 x 16 bits of memory (program and data segments)
    // Create a machine and initialize the registers  by calling reset function
    Machine machine;

    // Store the variables in the data memory segment
    machine[0] = 0; // Loop begin
    machine[1] = 10; // Loop end
    machine[2] = 1; // Loop step
    machine[3] = 5; // Bypass value

    // Implement the code:
    //
    // size_t sum = 0;
    // for (size_t i = 0; i < 10; i++) {
    //     if (i != 5)
    //         sum += i;
    // }
    //
    // Store the instruction buffer in the program memory segment
    machine << assembly(Load, Register0, 0);
    machine << assembly(Load, Register1, 1);
    machine << assembly(Load, Register2, 2);
    machine << assembly(Load, Register3, 3);
    machine << assembly(Clear, Register4);
    machine << assembly(Compare, Register5, Register0, Register1);
    machine << assembly(Branch, Register5, 38);
    machine << assembly(Compare, Register6, Register0, Register3);
    machine << assembly(Branch, Register6, 34);
    machine << assembly(Add, Register4, Register4, Register0);
    machine << assembly(Add, Register0, Register0, Register2);
    machine << assembly(Move, ProgramCounter, 14);
    machine << assembly(Store, Register4, 4);
    machine << assembly(Set, AbortFlag);

    // Try to interpret the instruction buffer
    machine.run();

    // Print the sum (40) stored in the data memory segment
    std::cout << "Output: " << machine[4] << std::endl;

    return 0;
}