cd search

echo "STRESS TEST:"

rm -rf build
mkdir build
cd build
cmake -DBUILD_PARALLEL=ON .. > /dev/null
cmake --build . > /dev/null
echo "Parallel Execution"
./search

cd ..
rm -rf build
mkdir build
cd build
cmake .. > /dev/null
cmake --build . > /dev/null
echo "Serial Execution"
./search

echo "TESTING:"

cd ..
rm -rf build
mkdir build
cd build
cmake -DBUILD_PARALLEL=ON .. > /dev/null
cmake --build . > /dev/null
echo "Parallel Execution"
./test_parallel/test_parallel

cd ..
rm -rf build
mkdir build
cd build
cmake .. > /dev/null
cmake --build . > /dev/null
echo "Serial Execution"
./test_serial/test_serial
