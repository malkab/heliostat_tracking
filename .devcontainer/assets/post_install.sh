#!/bin/bash

# -----------------------------------------------------------------
#
# Install packages in pip with this script. For initializing
# VSCode Dev Containers.
#
# -----------------------------------------------------------------

# Install cmake 3.29.3 binaries
sudo mkdir -p /usr/share/cmake-3.29/Modules
sudo cp .devcontainer/assets/cmake-3.29.3/bin/* /usr/bin
sudo cp -r .devcontainer/assets/cmake-3.29.3/Modules/* /usr/share/cmake-3.29/Modules

# APT installs
# sudo apt-get update

# sudo apt-get install -y \
#     whatever

# sudo apt-get -y upgrade

# sudo ldconfig

# sudo rm -rf /var/lib/apt/lists/*

# PIP installs and upgrade
/usr/local/bin/python3 -m pip install --upgrade --break-system-packages \
    pybind11[global]

# # Install Wheels packages
# /usr/local/bin/python3 -m pip install \
#     whl_packages/whatever.whl
