cmake_minimum_required(VERSION 3.20.0)

set(BOARD particle_xenon)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(ble_thermometer)

target_sources(app PRIVATE src/main.c)

