 with import <nixpkgs> {}; {
     brainEnv = stdenv.mkDerivation {
       name = "brain";
       buildInputs = [ stdenv mesa mesa_glu scons glew glfw sfml ffmpeg scons ];
       LD_LIBRARY_PATH="${glew}/lib";
     };
   }
