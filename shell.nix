{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = with pkgs; [
    cmake
    ninja
    openocd
    python3Packages.west

    # mcuboot requirements
    python3Packages.cryptography
    python3Packages.intelhex
    python3Packages.click
    python3Packages.cbor2

    python3Packages.pyelftools
  ];
  ZEPHYR_BASE=builtins.getEnv "HOME" + "/src/ncs/zephyr";
  ZEPHYR_TOOLCHAIN_VARIANT="zephyr";

  # TODO: make pkg for toolchain
  GNUARMEMB_TOOLCHAIN_PATH="/nix/store/j7c1fcagcircm0p7pnqs9225jj6cgc4x-zephyr-toolchain-0.13.2";
  ZEPHYR_SDK_INSTALL_DIR="/nix/store/j7c1fcagcircm0p7pnqs9225jj6cgc4x-zephyr-toolchain-0.13.2";
}
