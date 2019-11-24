ps aux | grep gdb | cut -c18-23 | while read -r pid; do echo "Killed PID: "$pid; kill -9 $pid 2> /dev/null; true; done
