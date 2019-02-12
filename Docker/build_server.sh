#!/bin/bash
cd /app/node_1
cmake . -Bbuild && cmake --build build -- -j8
cd ..
