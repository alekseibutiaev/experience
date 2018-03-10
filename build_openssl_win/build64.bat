perl Configure VC-WIN64A no-asm shared --prefix=c:\tmp\ossl\release64
nmake clean all test install
perl Configure VC-WIN64A no-asm no-shared --prefix=c:\tmp\ossl\release64-static
nmake clean all test install
perl Configure VC-WIN64A --debug no-asm shared --prefix=c:\tmp\ossl\debug64
nmake clean all test install
perl Configure VC-WIN64A --debug no-asm no-shared --prefix=c:\tmp\ossl\debug64-static
nmake clean all test install
