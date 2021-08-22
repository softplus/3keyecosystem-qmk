#!/bin/sh
git add . && git commit -m update && git push
pushd ~/code/arduino/3keyecosystem-qmk/private
git pull
rm -rf ../public/*
cp -r * ../public/
cd ../public
git add .
git commit
git push
popd
