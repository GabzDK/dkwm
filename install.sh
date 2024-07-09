#!/bin/bash

# Install the dependencies
install_arch() {
    sudo pacman -Syu --noconfirm
    sudo pacman -S --noconfirm base-devel libconfig dbus libev libx11 libxcb libxext libgl libegl libepoxy meson pcre2 pixman uthash xcb-util-image xcb-util-renderutil xorgproto cmake
}

if [ -f /etc/os-release ]; then
    . /etc/os-release
    case $ID in 
        arch)
            echo "Installing dependencies"
            install_arch
            ;;
    esac
else
    echo "/etc/os-release not found. Unsupported distribution"
    exit 1
fi


picom_animations() {
    # Clone the repository in the home/build directory
    mkdir -p ~/build
    if [ ! -d ~/build/picom ]; then
        if ! git clone https://github.com/FT-Labs/picom.git ~/build/picom; then
            echo "Failed to clone the repository"
            return 1
        fi
    else
        echo "Repository already exists, skipping clone"
    fi

    cd ~/build/picom || { echo "Failed to change directory to picom"; return 1; }

    # Build the project
    if ! meson setup --buildtype=release build; then
        echo "Meson setup failed"
        return 1
    fi

    if ! ninja -C build; then
        echo "Ninja build failed"
        return 1
    fi

    # Install the built binary
    if ! sudo ninja -C build install; then
        echo "Failed to install the built binary"
        return 1
    fi

    echo "Picom animations installed successfully"
}


# Call the function
picom_animations

