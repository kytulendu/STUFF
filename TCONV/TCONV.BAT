@echo off
echo Thai character code converter
echo =============================
echo Note: Convert TIS-620 to Kaset will lose some character.
echo       Invalid character will replace with space (20h).
echo       Option settings at the end of file will be stripped out.
echo.
echo CUW2CW      Computer Union Word to CU-Writer (TIS-620)
echo DTM2STD     Kaset-DTM (Kaset Datamat, based on Kaset v2) to TIS-620
echo KU2STD      Kaset to TIS-620
echo KUCW2STD    Kaset-CW (Kaset CU-Writer) to TIS-620 CW
echo KURW2STD    Kaset-RW (Kaset Rajavithi Word PC) to TIS-620 CW
echo LY2STD      Loxley to TIS-620-CW
echo STD2KUCW    TIS-620 CW to Kaset-CW
echo STD2KURW    TIS-620 CW to Kaset-RW
echo STD2LY      TIS-620 CW to Loxley
echo STW2CW      iRC Standard Word to CU-Writer (TIS-620)
echo WS2TXT      WordStar to plain text
echo.
echo Usage: [Command] [input file] [output file]
echo.
