#!/usr/bin/env bash

set -eo pipefail

sun="/home/cbrewster/Development/single-user-nix"


{
    upper=$(mktemp -d)
    work=$(mktemp -d)
    mount -t overlay overlay -olowerdir=/nix/store:/mnt/chaos:${sun}/nix/store,upperdir=${upper},workdir=${work} /nix/store
}

{
    upper=$(mktemp -d)
    work=$(mktemp -d)

    mount -t overlay overlay -olowerdir=${sun}/nix/var,upperdir=${upper},workdir=${work} /nix/var
}


exec nix --extra-experimental-features 'nix-command flakes local-overlay-store read-only-local-store' --store 'local-overlay?lower-store=tvix%3A%2F%2F&upper-layer=%2Fnix%2Fstore&check-mount=false' $@


