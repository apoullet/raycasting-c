with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "raycasting";

  buildInputs = [
    pkgs.gcc
    pkgs.allegro5
    pkgs.gnumake
  ];
}
