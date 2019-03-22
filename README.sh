echo "================================================="
echo "=================COMP2160 A3Q1==================="
echo "================================================="
echo "==============Wu Tommy (7852291)================="
echo "================================================="
echo
echo

####  Run this script to automatically make and run this
####  table program, and test from provided script.

####  How to use this test shell:
####    ./bin/table for interactive shell, OR
####    ./bin/table script.file to use as a scripter

####  Supported operations:
####  new (int set): construct a new set
####  delete (int set): delete the given set
####  insert (int set) (int toInsert): insert an integer into given set
####  remove (int set) (int toRemove): remove an integer into given set
####  equal (int set1) (int set2): tell if 2 sets are equal
####  disjoint (int set1) (int set1): tell if 2 sets have common items
####  union (int set1) (int set2) (int set3): calculate set1 union set2 then put it in set3
####  symdiff (int set1) (int set2) (int set3): calculate set1 symmetric difference set2 then put it in set3

echo "================================================="
echo "=================excuting make==================="
echo "================================================="
echo 

make

echo
echo

echo "================================================="
echo "===============testing 1st set.o================="
echo "================================================="

./bin/test/test1 ./test_script/1 > ./test_result/test.result1

echo "================================================="
echo "===============testing 2nd set.o================="
echo "================================================="

./bin/test/test2 ./test_script/1 > ./test_result/test.result2

echo "================================================="
echo "===============testing 3rd set.o================="
echo "================================================="

./bin/test/test3 ./test_script/1 > ./test_result/test.result3

echo "================================================="
echo "===============testing 4th set.o================="
echo "================================================="

./bin/test/test4 ./test_script/1 > ./test_result/test.result4

echo "================================================="
echo "===============testing 5th set.o================="
echo "================================================="

./bin/test/test5 ./test_script/1 > ./test_result/test.result5

echo "================================================="
echo "===============testing 6th set.o================="
echo "================================================="

./bin/test/test6 ./test_script/1 > ./test_result/test.result6

echo
echo


echo "================================================="
echo "=============comparing difference================"
echo "================================================="

diff ./test_result/test.reference ./test_result/test.result1
# 1st set.o OK
diff ./test_result/test.reference ./test_result/test.result2
# 2nd set.o equal function is not working 
diff ./test_result/test.reference ./test_result/test.result3
# 3rd set.o OK
diff ./test_result/test.reference ./test_result/test.result4
# 4th set.o remove function is not working
diff ./test_result/test.reference ./test_result/test.result5
# 5th set.o disjoint and symmetric difference functions are not working
diff ./test_result/test.reference ./test_result/test.result6
# 6th set.o disjoint not working

echo
echo

echo "================================================="
echo "====================cleaning====================="
echo "================================================="

make clean