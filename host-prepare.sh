#!/bin/bash

TEMPDIR=temp

URLS=(
    "http://files.randombit.net/botan/v1.10/Botan-1.10.0.tbz"
    "ftp://ftp.gnupg.org/gcrypt/libgcrypt/libgcrypt-1.5.2.tar.bz2"
    "http://cryptopp.com/cryptopp562.zip"
)

for url in "${URLS[@]}"; do
    wget $url
    archive=$(echo $url | awk -F'/' '{printf("%s", $NF)}')

    mkdir $TEMPDIR
    if [[ "$archive" == *zip* ]]; then
        unzip -a $archive -d $TEMPDIR
    else
        tar -xjvf $archive -C $TEMPDIR/
    fi
    cd $TEMPDIR

    if [ 1 -eq `ls | wc -l` ]; then
        cd `ls`
    fi

    CONFIG=$(ls | grep configure | head -n 1)
    if [ -n "$CONFIG" ]; then
        echo "Found config file $CONFIG"
        ./$CONFIG --prefix=/usr
        TARGET=""
    else
        mv GNUmakefile Makefile
        sed -i 's/# CXXFLAGS += -fPIC/CXXFLAGS += -fPIC/g' Makefile
        TARGET=" dynamic"
    fi

    make $TARGET

    sudo make install

    cd ..
    if [ 1 -eq `ls | wc -l` ]; then
        cd ..
    fi

    sudo rm -R $TEMPDIR
    sudo rm $archive

done
