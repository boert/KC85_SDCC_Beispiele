
ones8k.rom:
	tr '\0' '\001' < /dev/zero | dd bs=1k count=8 of=$@

FFs8k.rom:
	tr '\0' '\377' < /dev/zero | dd bs=1k count=8 of=$@

55_8k.rom:
	tr '\0' '\125' < /dev/zero | dd bs=1k count=8 of=$@

zero8k.rom:
	cat /dev/zero | dd bs=1k count=8 of=$@

crc16: FFs8k.rom zero8k.rom ones8k.rom 55_8k.rom
	jacksum -a crc:16,1021,ffff,false,false,0 -X *.rom

adler32: FFs8k.rom zero8k.rom ones8k.rom 55_8k.rom
	jacksum -a adler-32 -X *.rom
