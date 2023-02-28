if [ ! -d "build" ]; then
    mkdir build
fi

cd build || return

cmake ..

cmake --build .

./main
