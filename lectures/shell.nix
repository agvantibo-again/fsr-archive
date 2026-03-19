{
  pkgs ? import <nixpkgs> {}
}:

pkgs.mkShell {
  buildInputs = with pkgs; [
    readline
  ];
  CFLAGS = "-lreadline";
}
