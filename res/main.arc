# Program:
#
# size_t sum = 0;
# for (size_t i = 0; i <= 10; i++) {
#     if (i != 5)
#         sum += i;
# }
#
# Output: 50

set r0 0                    # i variable
set r1 10                   # Loop conditional value to exit
set r2 1                    # i variable increment
set r3 5                    # Ignored i value
set r4 0                    # Initial value of the sum variable
set r5 15                   # Instruction address to exit of loop
set r6 13                   # Instruction address to skip the sum variable update
set r7 8                    # Instruction address to keep looping
gt r8 r0 r1                 # Update loop condition
bch r8 pc r5                # Check to exit of loop
eq r9 r0 r3                 # Update if condition
bch r9 pc r6                # Check to skip the sum variable update
add r4 r4 r0                # Add i to the sum variable
add r0 r0 r2                # Increment i variable
mov pc r7                   # Continue loop
st r4 128                   # Store sum in the data segment of memory
set af 1                    # Set abort flag to true