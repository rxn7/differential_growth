#!/bin/sh

cmake --build build/debug
cp build/debug/compile_commands.json .

if [ $? -ne 0 ]; then
exit
fi

pushd build/debug >/dev/null
./differential_growth
popd >/dev/null

