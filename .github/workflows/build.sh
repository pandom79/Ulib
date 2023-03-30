#!/bin/sh

meson setup build
meson compile build
meson install build
