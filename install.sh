install_dependencies() {
    echo "Installing dependencies for $OS..."
    # Add installation commands here
    case $OS in
        ubuntu|debian)
            apt-get update
            apt-get install -y libssh-dev libncurses5-dev cmake
            ;;
        fedora|centos)
            dnf install -y libssh-devel ncurses-devel cmake
            ;;
        arch)
            pacman -Syu libssh ncurses cmake
            ;;
        *)
            echo "Unsupported OS: $OS"
            exit 1
            ;;
    esac
}

check_permission() {
    if [ "$EUID" -ne 0 ]; then
        echo "Please run as root"
        exit 1
    fi
}

echo "This script will attempt to install the necessary dependencies."
echo "Here is the list of dependencies: ncurses, libssh"

OS=$(awk -F= '/^ID=/{print $2}' /etc/os-release)
echo "Your operating system is $OS"
check_permission
install_dependencies

echo "Dependencies installed."

sleep 5

mkdir build
cd build
cmake ..
make