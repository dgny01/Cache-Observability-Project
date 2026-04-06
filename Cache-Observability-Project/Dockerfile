FROM gcc:latest

COPY . /usr/src/myapp

WORKDIR /usr/src/myapp

RUN g++ -O3 -o cache_analyzer main.cpp

CMD ["./cache_analyzer"]