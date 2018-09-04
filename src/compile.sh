echo "Compiling main.cpp"
g++ $(pkg-config --cflags --libs opencv) -std=c++11 main.cpp -o winnie
echo "main.cpp compiled to ./winnie"