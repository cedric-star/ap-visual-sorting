{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "c-ap-dev-shell";

  buildInputs = with pkgs; [
    gcc
    glibc.dev 
    stdenv.cc.libc
    raylib
  ];

  shellHook = ''
    echo "./MySorter" &&
    echo ""
    echo "oder:"
    echo "make run"
    codium . 
  '';
}
### Ausführen: 
# nix-shell myraylib.nix
