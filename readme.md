# how to install 
sudo apt install libncurses-dev

# how to run
```
mkdir build  
cd build && cmake -DCMAKE_CXX_COMPILER=g++ .. && make  
./main  
```

# how to run tests
```
mkdir build  
cd build && cmake -DCMAKE_CXX_COMPILER=g++ .. && make  
./test/testSimpleTimer
```