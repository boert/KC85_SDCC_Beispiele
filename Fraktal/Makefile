TARGET = TFRAKTAL

SRC_C = $(wildcard *.c)
OBJ_C = $(SRC_C:%.c=%.rel)

SRC_ASM = $(wildcard *.s)
OBJ_ASM = $(SRC_ASM:%.s=%.rel)

#Z80LIB = -l /usr/share/sdcc/lib/z80/z80.lib
#Z80LIB = -l z80.lib
Z80LIB = 
LIBS  = -l caos.lib
LIBS  += -l printf.lib
LIBS  += -l z80_float.lib
#LIBS  += -lm	# geht nicht

CFLAGS += -D_DATESTAMP_=\"$$(date +"%d.%m.%Y")\"

all: main.kcc
	mv $< $(TARGET).KCC

%.rel: %.s
	@echo -n "Assemble: "
	sdasz80  -plsgff  -o  $@ $<

%.rel: %.asm
	@echo -n "Assemble: "
	sdasz80  -plsgff  -o  $@ $<

%.asm: %.c
	@echo -n "Compile:  "
	sdcc     -mz80  --fomit-frame-pointer       -Wall  -S $(CFLAGS)  $<   -o $@

main.ihx: $(OBJ_ASM) $(OBJ_C) $(Z80LIB)
	@echo -n "Link:     "
	sdldz80  -mjwx  -b _KCC_HEADER=0x180 -b _CODE=0x200 $(LIBS) $(Z80LIB) -i $@  $^

main.kcc: main.ihx
	@echo -n "OBJ copy: "
	sdobjcopy  -I ihex -O binary   main.ihx main.kcc

size-check: main.rel
	sdnm  --print-size --size-sort --reverse-sort --radix=dec  main.rel


clean:
	rm -f *.sym
	rm -f *.lst
	rm -f *.rel
	rm -f main.asm
	rm -f main.ihx
	rm -f main.lk
	rm -f main.map
	rm -f main.noi
