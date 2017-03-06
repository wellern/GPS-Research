#!/bin/bash
gpio mode 0 out
gpio mode 2 out
gpio mode 3 out
gpio write 0 1
gpio write 2 1
gpio write 3 0
sleep 5
gpio write 0 0
gpio write 2 0
gpio write 3 0

