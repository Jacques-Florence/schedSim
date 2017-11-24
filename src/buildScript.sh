mkdir -p ../build
cd ../build
cmake ../src -DCMAKE_CXX_COMPILER=g++

if make ; then

	make install
	cd ../build
#	make test
    ctest
	cd ../simulator
fi
