#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

REQUIRED_PKGS=(libssh-dev libncurses5-dev cmake)

log() { printf '[INFO] %s\n' "$*"; }
err() { printf '[ERROR] %s\n' "$*" >&2; }

require_cmd() {
    if ! command -v "$1" &>/dev/null; then
        err "Required command '$1' not found. Install it and re-run."
        exit 1
    fi
}

detect_os() {
    if [[ -r /etc/os-release ]]; then
        . /etc/os-release
        OS_ID=${ID,,}
        OS_LIKE=${ID_LIKE:-}
    else
        err "/etc/os-release not found. Unsupported system."
        exit 1
    fi

    case "$OS_ID" in
        ubuntu|debian)
            OS_FAMILY="debian"
            ;;
        fedora)
            OS_FAMILY="fedora"
            ;;
        centos|rhel)
            OS_FAMILY="rhel"
            ;;
        arch)
            OS_FAMILY="arch"
            ;;
        *)
            # Try falling back via ID_LIKE
            if [[ "$OS_LIKE" == *"debian"* ]]; then
                OS_FAMILY="debian"
            elif [[ "$OS_LIKE" == *"rhel"* ]]; then
                OS_FAMILY="rhel"
            else
                err "Unsupported OS: $OS_ID"
                exit 1
            fi
            ;;
    esac

    log "Detected OS: $OS_ID (family: $OS_FAMILY)"
}

install_dependencies() {
    log "Installing dependencies..."

    case "$OS_FAMILY" in
        debian)
            require_cmd apt-get
            DEBIAN_PKGS=(libssh-dev libncurses5-dev cmake build-essential)
            apt-get update -y
            apt-get install -y "${DEBIAN_PKGS[@]}"
            ;;
        fedora)
            require_cmd dnf
            FEDORA_PKGS=(libssh-devel ncurses-devel cmake make gcc gcc-c++)
            dnf install -y "${FEDORA_PKGS[@]}"
            ;;
        rhel)
            # CentOS/RHEL (dnf or yum depending on version)
            if command -v dnf &>/dev/null; then
                PM=dnf
            else
                PM=yum
            fi
            RHEL_PKGS=(libssh-devel ncurses-devel cmake make gcc gcc-c++)
            "$PM" install -y "${RHEL_PKGS[@]}"
            ;;
        arch)
            require_cmd pacman
            ARCH_PKGS=(libssh ncurses cmake base-devel)
            pacman -Sy --needed --noconfirm "${ARCH_PKGS[@]}"
            ;;
        *)
            err "install_dependencies: Unsupported OS family: $OS_FAMILY"
            exit 1
            ;;
    esac

    log "All dependencies installed (or already present)."
}

check_root() {
    if [[ $EUID -ne 0 ]]; then
        err "This script must be run as root (or with sudo)."
        exit 1
    fi
}

build_project() {
    require_cmd cmake
    require_cmd make

    log "Configuring and building project..."
    mkdir -p build
    cd build
    cmake ..
    make -j"$(nproc || echo 2)"
    log "Build completed successfully."
}

main() {
    log "This script will install: libssh, ncurses, cmake (and basic build tools)."
    check_root
    detect_os
    install_dependencies
    build_project
}

main "$@"