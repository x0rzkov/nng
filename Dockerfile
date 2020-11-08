FROM alpine:3.12

RUN apk add --no-cache cmake make musl-dev mbedtls-dev git ca-certificates bash nano jq gcc g++ re2c

RUN git clone --depth=1 https://github.com/ninja-build/ninja /opt/ninja && \
    cd /opt/ninja && \
    cmake -Bbuild-cmake -H. && \
    cmake --build build-cmake && \  
    cmake --build build-cmake --target install && \
    rm -fR /opt/ninja

WORKDIR /opt/source
COPY . .

RUN mkdir -p /opt/source/build && \
    cd /opt/source/build && \
    cmake -G Ninja .. && \
    ninja && \
    ninja install

CMD ["/bin/bash"]
