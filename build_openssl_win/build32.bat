perl Configure VC-WIN32 no-asm shared --prefix=c:\tmp\ossl\release32
nmake clean all test install
perl Configure VC-WIN32 no-asm no-shared --prefix=c:\tmp\ossl\release32-static
nmake clean all test install
perl Configure VC-WIN32 --debug no-asm shared --prefix=c:\tmp\ossl\debug32
nmake clean all test install
perl Configure VC-WIN32 --debug no-asm no-shared --prefix=c:\tmp\ossl\debug32-static
nmake clean all test install
