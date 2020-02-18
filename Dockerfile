FROM ubuntu:latest

WORKDIR /work
RUN apt update \
 && apt install -y --no-install-recommends \
    build-essential \
    libgstreamer1.0-dev \
    gstreamer1.0-tools \
 && apt -y clean \
 && rm -rf /var/lib/apt/lists/*

COPY gst-plugins-bad/tools/gst-element-maker /bin/
COPY gst-plugins-bad/tools/element-templates /bin/
COPY gstreamer/tools/gst-indent /bin

