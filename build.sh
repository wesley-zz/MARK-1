#!/bin/bash
function usage()
{
    echo -e "-------------------------------"
    echo -e "make:"
	echo -e "	./build.sh y"
    echo -e "make clean:"
	echo -e "	./build.sh n"
    echo -e "-------------------------------"
}

function build_judge()
{
    if [ "y" == $STATUS ]; then
        echo "making"
    elif [ "n" == $STATUS ]; then
        echo "cleaning"
    else
        usage
        exit 1
    fi
}

function build()
{
    rm -rf bin/*
    cd build

    if [ "y" == $STATUS ]; then
        cmake ..
        make
        echo "make success"
        cd ../bin
        echo "-------------------------------"
        ./main
    elif [ "n" == $STATUS ]; then
        echo "clean success"
        make clean
    else
        usage
        exit 1
    fi
    
    cd $ROOT_PATH
}

STATUS=$1

export ROOT_PATH=$PWD

# build_judge

build