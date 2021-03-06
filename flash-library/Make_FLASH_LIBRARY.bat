REM EXPECT THE FOLLOWING LINE TO CREATE AN S29 FILE WITH OFFSETS BEGINNING AT $F4000 (APPARENT ADDRESS OF $8000 WITH PPAGE=$3D)
REM WHEN CODE COMPILED BEGINNING AT ORG $8000 ($EC000+$8000=$F4000)
sreccvt -m c0000 fffff 32 -of EC000 -o FLASH_LIBRARY.s29 FLASH_LIBRARY.s19
copy FLASH_LIBRARY.s29 FLASH_LIBRARY.s2
copy FLASH_LIBRARY.s29 FLASH_LIBRARY.s29.TXT

REM EXPECT THE FOLLOWING LINE TO CREATE AN S29 FILE WITH OFFSETS BEGINNING AT $FC000 (APPARENT ADDRESS OF $8000 WITH PPAGE=$3F)
REM WHEN CODE COMPILED BEGINNING AT ORG $8000 ($F4000+$8000=$FC000)
rem sreccvt -m c0000 fffff 32 -of F4000 -o FLASH_LIBRARY.s29 FLASH_LIBRARY.s19
rem copy FLASH_LIBRARY.s29 FLASH_LIBRARY.s2
rem copy FLASH_LIBRARY.s29 FLASH_LIBRARY.s29.TXT

REM EXPECT THE FOLLOWING LINE TO CREATE AN S29 FILE WITH OFFSETS BEGINNING AT $DC000 (APPARENT ADDRESS OF $8000 WITH PPAGE=$37)
REM WHEN CODE COMPILED BEGINNING AT ORG $8000 ($D4000+$8000=$DC000)
REM sreccvt -m c0000 fffff 32 -of D4000 -o FLASH_LIBRARY.s29 FLASH_LIBRARY.s19
REM copy FLASH_LIBRARY.s29 FLASH_LIBRARY.s2
REM copy FLASH_LIBRARY.s29 FLASH_LIBRARY.s29.TXT

REM EXPECT THE FOLLOWING LINE TO CREATE AN S29 FILE WITH OFFSETS BEGINNING AT $C0000 (APPARENT ADDRESS OF $8000 WITH PPAGE=$30)
REM WHEN CODE COMPILED BEGINNING AT ORG $0000
REM sreccvt -m c0000 fffff 32 -of C0000 -o FLASH_TEST_D12_2.s29 FLASH_TEST_D12_2.s19
REM copy FLASH_TEST_D12.s29 FLASH_TEST_D12_2.s2

REM REM EXPECT THE FOLLOWING LINE TO CREATE AN S29 FILE WITH OFFSETS BEGINNING AT $FB000 (APPARENT ADDRESS OF $7000)
REM REM WHEN CODE COMPILED BEGINNING AT ORG $0000
REM sreccvt -m c0000 fffff 32 -of fb000 -o FLASH_TEST_D12_2.s29 FLASH_TEST_D12_2.s19
REM copy FLASH_TEST_D12.s29 FLASH_TEST_D12_2.s2
