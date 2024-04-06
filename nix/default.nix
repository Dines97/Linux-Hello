inputs:
inputs.flake-parts.lib.mkFlake {inherit inputs;} {
  systems = ["x86_64-linux"];
  perSystem = {
    pkgs,
    system,
    lib,
    self',
    ...
  }: {
    _module.args.pkgs = import inputs.nixpkgs {
      inherit system;
      overlays = [
        # inputs.rust-overlay.overlays.default
      ];
      config = {
        allowUnfree = true;
      };
    };
    packages = {
      default = pkgs.callPackage ./package.nix {};
    };

    devShells = {
      default = self'.packages.default.overrideAttrs (old: {
        nativeBuildInputs = with pkgs;
          old.nativeBuildInputs
          ++ [
            cmake

            cargo-flamegraph
          ];
      });
    };
  };
}
