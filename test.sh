#!/usr/bin/env bash
set -xeuo pipefail

flakes="--extra-experimental-features nix-command --extra-experimental-features flakes"

make -j $NIX_BUILD_CORES

sudo umount /tmp/nix/store
#trap 'sudo umount /tmp/nix/store' EXIT

sudo rm -rf /tmp/nix
sudo rm -rf /tmp/nix-upper
sudo rm -rf /tmp/nix-work
mkdir -p /tmp/nix/store
mkdir -p /tmp/nix-upper
mkdir -p /tmp/nix-work

sudo mount -t overlay overlay \
    -o lowerdir="/var/lib/ersa/nix/store" \
    -o upperdir="/tmp/nix-upper" \
    -o workdir="/tmp/nix-work" \
    "/tmp/nix/store" \

./outputs/out/bin/nix build -vvvv -L --builders '' --max-jobs 0 --show-trace --extra-experimental-features 'nix-command flakes' --store 'local-overlay?root=/tmp&lower-store=local-cache:%3Froot=%2Fvar%2Flib%2Fersa&upper-layer=/tmp/nix-upper' 'github:nixos/nixpkgs/af21c31b2a1ec5d361ed8050edd0303c31306397#hello'

# sudo umount /tmp/nix/store

# sudo mount -t overlay overlay \
#     -o lowerdir="/nix/store" \
#     -o upperdir="/tmp/nix-upper" \
#     -o workdir="/tmp/nix-work" \
#     "/tmp/nix/store" \

# ./outputs/out/bin/nix build -L --extra-experimental-features 'nix-command flakes' --store 'local-overlay?root=/tmp&lower-store=&upper-layer=/tmp/nix-upper' 'nixpkgs#hello'
