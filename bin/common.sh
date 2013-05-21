#!/bin/sh

check_status() {
    ret=$?
    if [ "$ret" -ne "0" ]; then
        echo "Failed setup, aborting.."
        exit 1
    fi
}
