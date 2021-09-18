# vezdecode_cpp30

# Install and run
sudo apt install libcurl4-openssl-dev
<!-- cmake . -->
mkdir build
cd build
cmake ..
cmake --build .
./vezde30

# Дополнительное задание
Чтобы ввести название метода, достаточно написать:
    ./vezde30 <method_name>

# test_server 
curl -X POST https://httpbin.org/post -L -d '{"id":0, "jsonrpc":"2.0","method":"systemInfo","params":[]}'