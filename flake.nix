{
  description = "Dein Projekt";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        packages.default = pkgs.stdenv.mkDerivation rec {
          pname = "ap-visual-sorting";
          version = "1.0.0";

          src = ./.;

          buildInputs = with pkgs; [
            gcc
            glibc.dev 
            stdenv.cc.libc
            raylib
          ];

          nativeBuildInputs = with pkgs; [
            make
          ];

          buildPhase = ''
            make
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp MySorter $out/bin/
          '';

          meta = with pkgs.lib; {
            description = "Visualize Sorting Algorithms written in C (testet only for x86_64-linux)";
            homepage = "https://github.com/cedric-star/ap-visual-sorting";
            license = licenses.mit; # oder passende Lizenz
            maintainers = with maintainers; [ cedric-star ];
            platforms = platforms.all;
          };
        };
      });
}