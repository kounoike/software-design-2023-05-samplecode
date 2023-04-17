#!/bin/bash

zig build-lib -dynamic -target wasm32-freestanding-none src/main.zig \
    --export-table
