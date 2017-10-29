mkdir -p ../build
cd ../build
#../../cmake-3.5.2/bin/cmake ../src -DCMAKE_CXX_COMPILER=g++
#/usr/local/bin/cmake ../src -DCMAKE_CXX_COMPILER=g++
#module load cmake/3.5.2
cmake ../src -DCMAKE_CXX_COMPILER=g++



if make ; then

	make install
	cd ../build
#	make test
    ctest
	cd ../simulator
fi
