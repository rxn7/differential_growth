#!/bin/sh

pushd build/debug >/dev/null
gdb ./differential_growth -q
popd >/dev/null

