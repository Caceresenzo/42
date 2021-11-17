export DEBIAN_FRONTEND="noninteractive"

apt-get update

apt-get install -y nano zsh git wget curl screen
apt-get install -y bash binutils bison bzip2 coreutils diffutils findutils gawk gcc libc6 grep gzip m4 make patch perl python3 sed tar texinfo xz-utils g++ parallel

#sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" || true

