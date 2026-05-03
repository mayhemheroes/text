FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    ca-certificates gnupg wget software-properties-common \
    clang build-essential git

# Install cmake >= 3.31 from Kitware APT repo
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | \
    gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null && \
    echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' | \
    tee /etc/apt/sources.list.d/kitware.list >/dev/null && \
    apt-get update && apt-get install -y cmake

COPY . /text

# Pin all ztd.* FetchContent dependencies to Dec 2022/early 2023 era versions
# that are mutually compatible with the mayhemheroes/text fork headers
RUN sed -i \
    '/FetchContent_Declare(ztd.cmake/,/FetchContent_MakeAvailable(ztd.cmake)/ { \
        s|GIT_SHALLOW.*ON|GIT_SHALLOW    OFF|; \
        s|GIT_TAG.*main|GIT_TAG        b365519855861f2772ba68acd770cd39bc6439d7|; \
    }' /text/CMakeLists.txt && \
    sed -i \
    '/FetchContent_Declare(ztd.idk/,/FetchContent_MakeAvailable(ztd.idk)/ { \
        s|GIT_SHALLOW.*ON|GIT_SHALLOW    OFF|; \
        s|GIT_TAG.*main|GIT_TAG        4f6ce4ffdba2658bab87aaa692930613168f7448|; \
    }' /text/CMakeLists.txt && \
    sed -i \
    '/FetchContent_Declare(ztd.static_containers/,/FetchContent_MakeAvailable(ztd.static_containers)/ { \
        s|GIT_SHALLOW.*ON|GIT_SHALLOW    OFF|; \
        s|GIT_TAG.*main|GIT_TAG        e1a21217b6dba3028e6cc6bf0f9562972ea1c43d|; \
    }' /text/CMakeLists.txt && \
    sed -i \
    '/FetchContent_Declare(ztd.encoding_tables/,/FetchContent_MakeAvailable(ztd.encoding_tables)/ { \
        s|GIT_SHALLOW.*ON|GIT_SHALLOW    OFF|; \
        s|GIT_TAG.*main|GIT_TAG        d2fc75bb4cdba5c641dab5378b23b6b8f7e97b57|; \
    }' /text/CMakeLists.txt && \
    sed -i \
    '/FetchContent_Declare(ztd.cuneicode/,/FetchContent_MakeAvailable(ztd.cuneicode)/ { \
        s|GIT_SHALLOW.*ON|GIT_SHALLOW    OFF|; \
        s|GIT_TAG.*main|GIT_TAG        1bed7034c8f6b42390e1ec299e95ff07915bf871|; \
    }' /text/CMakeLists.txt && \
    sed -i \
    '/FetchContent_Declare(ztd.platform/,/FetchContent_MakeAvailable(ztd.platform)/ { \
        s|GIT_SHALLOW.*ON|GIT_SHALLOW    OFF|; \
        s|GIT_TAG.*main|GIT_TAG        d92b8e5b85a4cabae62ad19ccfcc5c3f94ab1a14|; \
    }' /text/CMakeLists.txt

RUN mkdir /text/build
WORKDIR /text/build
RUN CC=clang CXX="clang++" CFLAGS="-fsanitize=fuzzer-no-link" cmake .. && \
    CC=clang CXX="clang++" CFLAGS="-fsanitize=fuzzer-no-link" make -j8 && \
    make install

# Install ztd.static_containers headers (not installed by cmake but needed by fuzz target)
RUN cp -r /text/build/_deps/ztd.static_containers-src/include/ztd/. /usr/local/include/ztd/

WORKDIR /text/fuzz
RUN make

FROM ubuntu:22.04
COPY --from=builder /text/fuzz /
