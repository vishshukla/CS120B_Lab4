# Test file for "Lab4_SMs"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

test "PINA: 0x00 -> 0x01 -> 0x00 -> 0x01 => PORTC: 0x07 -> 0x08 -> 0x08 -> 0x09"
setPINA 0x00
set state = start
continue 2
expectPORTC 0x07
expect state s0

setPINA 0x01
continue 2
expectPORTC 0x08
expect state increment

setPINA 0x00
continue 2
expectPORTC 0x08
expect state s0

setPINA 0x01
continue 2
expectPORTC 0x09
expect state increment
checkResult

test "PINA: 0x00 -> 0x01 x4 => PORTC: 0x07 -> 0x08 -> 0x09 -> 0x09"
setPINA 0x00
set state = start
continue 2
expectPORTC 0x07
expect state s0

setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2

expect state increment
expectPORTC 0x09
checkResult

test "PINA: 0x00 -> 0x02 -> 0x00 => PORTC: 0x07 -> 0x06 -> 0x06"
setPINA 0x00
set state = start
continue 2
expectPORTC 0x07
expect state s0

setPINA 0x02
continue 2
expectPORTC 0x06
expect state decrement

setPINA 0x00
continue 2
expectPORTC 0x06
expect state s0
checkResult

test "PINA: 0x00 -> 0x02 -> 0x00 -> 0x02 .... => PORTC: 0x07 -> ... -> 0x00"
setPINA 0x00
set state = start
continue 2
expectPORTC 0x07
expect state s0

setPINA 0x02 #6
continue 2
setPINA 0x00
continue 2

setPINA 0x02 #5
continue 2
setPINA 0x00
continue 2

setPINA 0x02 #4
continue 2
setPINA 0x00
continue 2

setPINA 0x02 #3
continue 2
setPINA 0x00
continue 2

setPINA 0x02 #2
continue 2
setPINA 0x00
continue 2

setPINA 0x02 #1
continue 2
setPINA 0x00
continue 2

setPINA 0x02 #0
continue 2
setPINA 0x00
continue 2

setPINA 0x02 #0
continue 2
setPINA 0x00
continue 2

setPINA 0x02 #0
continue 2
setPINA 0x00
continue 2

expectPORTC 0x00
expect state s0
checkResult
# Add tests below

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
