#!/bin/bash

source progress_bar.sh

make clean --directory=../

tasks_in_total=17
for current_task in $(seq $tasks_in_total) 
    do
    sleep 0.1
    show_progress $current_task $tasks_in_total
done

make --directory=../
echo "✅ Compilation Complete"

cd ../utils/
doxygen
if [ $? -ne 0 ]; then
    echo "❌ Error Running Doxygen"
else 
    echo "✅ Doxygen Documentation Generated"
fi

cd ../tests/

# Symble Unit Tests

echo -e "\n"
echo Running Comment Test...
../bin/symble comment_test.sy
if [ $? -ne 0 ]; then
    echo "❌ Error Running Comment Test"
else 
    echo "✅ Comment Test Complete!"
fi

echo -e "\n"
echo Running Expr Test...
../bin/symble expr_test.sy
if [ $? -ne 0 ]; then
    echo "❌ Error Running expr Test"
else 
    echo "✅ expr Test Complete!"
fi

echo -e "\n"
echo Running function Test...
../bin/symble function_test.sy
if [ $? -ne 0 ]; then
    echo "❌ Error Running function Test"
else 
    echo "✅ function Test Complete!"
fi

echo -e "\n"
echo Running if_statement Test...
../bin/symble if_statement.sy
if [ $? -ne 0 ]; then
    echo "❌ Error Running if_statement Test"
else 
    echo "✅ if_statement Test Complete!"
fi

echo -e "\n"
echo Running while_loop Test...
../bin/symble while_loop.sy
if [ $? -ne 0 ]; then
    echo "❌ Error Running while_loop Test"
else 
    echo "✅ while_loop Test Complete!"
fi

echo -e "\n"
echo Running sieve Test...
../bin/symble sieve.sy
if [ $? -ne 0 ]; then
    echo "❌ Error Running sieve Test"
else 
    echo "✅ sieve Test Complete!"
fi
