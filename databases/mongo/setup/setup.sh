sudo apt-get install git
sudo apt-get install libbson-1.0-0
sudo apt-get install libmongoc-1.0-0
sudo apt-get install libboost-all-dev
sudo apt-get install libcrypto*
sudo apt-get install libssl*
sudo apt-get install libmongoc-dev
sudo apt-get install libbson-dev

curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.7.0/mongo-cxx-driver-r3.7.0.tar.gz
tar -xzf mongo-cxx-driver-r3.7.0.tar.gz
cd mongo-cxx-driver-r3.7.0/build

cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local  -DCMAKE_BUILD_TYPE=Release

sudo cmake --build . --target EP_mnmlstc_core

cmake --build .

sudo cmake --build . --target install


