#!/bin/bash
echo "sending file alert.txt"
sshpass -p "raspberry" scp ./Congestion.txt pi@192.168.0.103:traffic
echo "file sent"
