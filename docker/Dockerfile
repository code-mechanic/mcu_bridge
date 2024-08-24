# Use Ubuntu 20.04 as the base image
FROM ubuntu:20.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV XC8_VERSION=2.50
ENV XC16_VERSION=2.10
ENV XC32_VERSION=4.45

# Install basic programs
RUN apt-get update && apt-get install -y nano
RUN apt-get install -y curl
RUN apt-get install -y ruby
RUN apt-get install -y tar
RUN apt-get install -y wget
RUN apt-get install -y ca-certificates

################################################################################

## Python setup
#RUN apt install -y --no-install-recommends \
#    python3-yaml \
#    python3-pip
#RUN pip3 install poetry setuptools black

################################################################################

## Get the latest plantuml
#RUN curl -o /usr/share/plantuml/plantuml.jar -L http://sourceforge.net/projects/plantuml/files/plantuml.jar/download
## Add LLVM's GPG key
#RUN curl -fsSL https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
## Add LLVM's repos to get the updated clang-format
## Install clang-format-18 from the llvm repo
#RUN wget https://apt.llvm.org/llvm.sh
#RUN chmod +x llvm.sh
#RUN ./llvm.sh 18
#RUN apt install -y --no-install-recommends clang-format-18 clang-tidy-18
#RUN rm llvm.sh
#RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-18 100
#RUN update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-18 100
#RUN update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-18 100
## Install ceedling testing platform
#RUN gem install ceedling
## Install gcovr test coverage report generator
#RUN pip3 install gcovr==5.2
## Install cmakelang for cmake file format/lint
#RUN pip3 install cmakelang
## Install doxygen 1.9.6
#RUN wget https://www.doxygen.nl/files/doxygen-1.9.6.linux.bin.tar.gz \
# && tar -xvzf doxygen-1.9.6.linux.bin.tar.gz  \
# && rm doxygen-1.9.6.linux.bin.tar.gz \
# && cd doxygen-1.9.6/ \
# && make install

################################################################################

# Set working directory
WORKDIR /tmp

# Download Microchip XC8 Compiler
RUN wget https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/xc8-v${XC8_VERSION}-full-install-linux-x64-installer.run && \
    chmod +x xc8-v${XC8_VERSION}-full-install-linux-x64-installer.run && \
    ./xc8-v${XC8_VERSION}-full-install-linux-x64-installer.run --mode unattended --netservername localhost && \
    rm xc8-v${XC8_VERSION}-full-install-linux-x64-installer.run

# Update PATH environment variable
ENV PATH="/opt/microchip/xc8/v${XC8_VERSION}/bin:${PATH}"

# Download Microchip XC16 Compiler
#RUN wget https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/xc16-v${XC16_VERSION}-full-install-linux64-installer.run && \
#    chmod +x xc16-v${XC16_VERSION}-full-install-linux64-installer.run && \
#    ./xc16-v${XC16_VERSION}-full-install-linux64-installer.run --mode unattended --netservername localhost && \
#    rm xc16-v${XC16_VERSION}-full-install-linux64-installer.run

# Update PATH environment variable
#ENV PATH="/opt/microchip/xc16/v${XC16_VERSION}/bin:${PATH}"

# Download Microchip XC32 Compiler
#RUN wget https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/xc32-v${XC32_VERSION}-full-install-linux-x64-installer.run && \
#    chmod +x xc32-v${XC32_VERSION}-full-install-linux-x64-installer.run && \
#    ./xc32-v${XC32_VERSION}-full-install-linux-x64-installer.run --mode unattended --netservername localhost && \
#    rm xc32-v${XC32_VERSION}-full-install-linux-x64-installer.run

# Update PATH environment variable
#ENV PATH="/opt/microchip/xc32/v${XC32_VERSION}/bin:${PATH}"

# Set default command
CMD ["/bin/bash"]
