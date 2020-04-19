FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
  xz-utils \
  build-essential \
  curl \
  clang-4 \ 
  clang-5 \
  clang-6 \
  clang-7 \
  clang-8 \
  clang-9 \
  && rm -rf /var/lib/apt/lists/* \

# Start from a Bash prompt
CMD [ "/bin/bash" ]
