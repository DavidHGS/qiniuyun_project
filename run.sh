#! /bin/bash
cd test
g++ serverTest.cpp ../src/Server.cpp ../src/HttpHandler.cpp ../src/JsonObject.cpp -lpthread -o serverTest
./serverTest