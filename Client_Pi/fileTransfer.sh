#!/bin/bash
echo "sending file text.txt"
sshpass -p "raspberry" scp ./text1.txt pi@10.133.0.194:traffic
echo "file sent"
