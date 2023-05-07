FROM debian:bookworm as builder
RUN apt update && apt install -y clang build-essential cmake git

COPY . /text
RUN mkdir /text/build && cd /text/build && CC=clang CXX="clang++" CFLAGS="-fsanitize=fuzzer-no-link" cmake .. && CC=clang CXX="clang++" CFLAGS="-fsanitize=fuzzer-no-link" make -j8 && make install

WORKDIR /text/fuzz
RUN make

FROM debian:bookworm
COPY --from=builder /text/fuzz /