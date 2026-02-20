{ lib
, stdenv
, fetchFromGitHub
, gcc
, glibc.dev
, stdenv.cc.libc 
, raylib 
# weitere Dependencies hier
}:

stdenv.mkDerivation rec {
  pname = "ap-visual-sorting";
  version = "1.0.0";

  src = fetchFromGitHub {
    owner = "cedric-star";
    repo = "ap-visual-sorting";
    rev = "main";
    hash = "sha256-1z9zrb2hkkgl5x71d1w88qchg66pznvxsarvgs4khlhqw0s7n8pp="; # wird berechnet
  };

  buildInputs = with pkgs; [
    glibc.dev 
    stdenv.cc.libc
    raylib
  ];

  nativeBuildInputs = with pkgs; [
    gcc
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
}