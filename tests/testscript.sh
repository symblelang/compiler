#!/bin/bash

source progress_bar.sh

make clean --directory=../

tasks_in_total=37
for current_task in $(seq $tasks_in_total) 
    do
    sleep 0.1
    show_progress $current_task $tasks_in_total
done

make --directory=../
cd ../utils/
doxygen

cd ../tests/

# Unit Tests
retVal = $?

echo Running Comment Test...
../bin/symble comment_test.sy
if [ $retVal -ne 0 ]; then
    echo "Error Running Comment Test"
else 
    echo "Comment Test Complete!"
fi

echo Running Expr Test...
../bin/symble expr_test.sy
if [ $retVal -ne 0 ]; then
    echo "Error Running expr Test"
else 
    echo "expr Test Complete!"
fi

echo Running function Test...
../bin/symble function_test.sy
if [ $retVal -ne 0 ]; then
    echo "Error Running function Test"
else 
    echo "function Test Complete!"
fi

echo Running if_statement Test...
../bin/symble if_statement.sy
if [ $retVal -ne 0 ]; then
    echo "Error Running if_statement Test"
else 
    echo "if_statement Test Complete!"
fi

echo Running symbol_table Test...
../bin/symble symbol_table_test.sy
if [ $retVal -ne 0 ]; then
    echo "Error Running symbol_table Test"
else 
    echo "symbol_table Test Complete!"
fi

echo Running while_loop Test...
../bin/symble while_loop.sy
if [ $retVal -ne 0 ]; then
    echo "Error Running while_loop Test"
else 
    echo "while_loop Test Complete!"
fi

echo Running sieve Test...
../bin/symble while_loop.sy
if [ $retVal -ne 0 ]; then
    echo "Error Running sieve Test"
else 
    echo "sieve Test Complete!"
fi
