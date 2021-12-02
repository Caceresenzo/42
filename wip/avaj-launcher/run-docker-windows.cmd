@echo off

docker run -it --rm -v %cd%:/app openjdk:7 bash -c "cd /app && sh compile.sh && sh run.sh"