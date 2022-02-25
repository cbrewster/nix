{ pkgs, ... }: {
  boot.kernelPackages = pkgs.linuxPackages_latest;

  virtualisation.qemu.networkingOptions = [ "-nic bridge,br=virbr0,model=virtio-net-pci,mac=12:13:11:11:11:11,helper=/run/wrappers/bin/qemu-bridge-helper" ];

#   fileSystems.cachefs =
#   {
#     mountPoint = "/nix/store";
#     fsType = "overlay";
#     options = ["lowerdir=/mnt/cachenfs:/nix/store,upperdir=/nix/store,workdir=/tmp/nix/store"];
#   };
  
  virtualisation.memorySize = 16384;
  virtualisation.cores = 8;

  nixos-shell.mounts.extraMounts = {
    # override options for each mount
    "/mnt/cachenfs" = {
      target = /cachenfs;
      cache = "none";
    };
  };

  nixos-shell.mounts = {
    cache = "none";
  };
}
