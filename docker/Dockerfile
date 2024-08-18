# Use Ubuntu 20.04 as the base image
FROM ubuntu:20.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV XC8_VERSION=2.50
ENV XC16_VERSION=2.10
ENV XC32_VERSION=4.45

# Update and install necessary packages
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    wget \
    nano \
    ca-certificates

# Set working directory
WORKDIR /tmp

# Download Microchip XC8 Compiler
RUN wget https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/xc8-v${XC8_VERSION}-full-install-linux-x64-installer.run && \
    chmod +x xc8-v${XC8_VERSION}-full-install-linux-x64-installer.run && \
    ./xc8-v${XC8_VERSION}-full-install-linux-x64-installer.run --mode unattended --netservername localhost && \
    rm xc8-v${XC8_VERSION}-full-install-linux-x64-installer.run

# Download Microchip XC16 Compiler
RUN wget https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/xc16-v${XC16_VERSION}-full-install-linux64-installer.run && \
    chmod +x xc16-v${XC16_VERSION}-full-install-linux64-installer.run && \
    ./xc16-v${XC16_VERSION}-full-install-linux64-installer.run --mode unattended --netservername localhost && \
    rm xc16-v${XC16_VERSION}-full-install-linux64-installer.run

# Download Microchip XC32 Compiler
RUN wget https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/xc32-v${XC32_VERSION}-full-install-linux-x64-installer.run && \
    chmod +x xc32-v${XC32_VERSION}-full-install-linux-x64-installer.run && \
    ./xc32-v${XC32_VERSION}-full-install-linux-x64-installer.run --mode unattended --netservername localhost && \
    rm xc32-v${XC32_VERSION}-full-install-linux-x64-installer.run

# Update PATH environment variable
ENV PATH="/opt/microchip/xc8/v${XC8_VERSION}/bin:/opt/microchip/xc16/v${XC16_VERSION}/bin:/opt/microchip/xc32/v${XC32_VERSION}/bin:${PATH}"

# Set default command
CMD ["/bin/bash"]

RUN mkdir -p /home/user_pic
WORKDIR /home/user_pic
COPY entrypoint.sh ./
RUN chmod +x entrypoint.sh
