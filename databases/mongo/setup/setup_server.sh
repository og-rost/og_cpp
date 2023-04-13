#!/bin/bash

function install_served_dependencies() {
  git clone https://github.com/meltwater/served.git
  cd served/
  cmake .
  make
  sudo make install
  cd ../
  rm -rf served
}

function install_json_dependencies() {
  if ! [[ -d "SimpleJSON" ]]; then
      mkdir SimpleJSON
  fi
  cd SimpleJSON
  curl https://raw.githubusercontent.com/nbsdx/SimpleJSON/master/json.hpp -o json.hpp
}

function main() {
  cd lib
  install_served_dependencies
  install_json_dependencies
  cd ..
}

main