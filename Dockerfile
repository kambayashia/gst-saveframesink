FROM ubuntu:latest

WORKDIR /work
RUN apt update \
 && apt install -y --no-install-recommends \
    build-essential \
    libgstreamer1.0-dev \
    gstreamer1.0-tools \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-libav \
 && apt -y clean \
 && rm -rf /var/lib/apt/lists/*

COPY gst-plugins-bad/tools/gst-element-maker /bin/
COPY gst-plugins-bad/tools/element-templates /bin/
COPY gstreamer/tools/gst-indent /bin

#ENTRYPOINT gst-launch-1.0 filesrc location=test.mp4 ! decodebin ! identity
