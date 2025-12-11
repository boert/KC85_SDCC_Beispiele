TARGET = HELLO

# alle C-Quelldateien
SRC_C = $(wildcard *.c)
OBJ_C = $(SRC_C:%.c=%.rel)

# alle Assemblerquellen
SRC_ASM = $(wildcard *.s)
OBJ_ASM = $(SRC_ASM:%.s=%.rel)

LIBS  = caos.lib
LIBS  += printf.lib

# -l ergänzen für Compiler
LIBSLIST = $(patsubst %, -l %,$(LIBS))


all: libs $(TARGET).kcc

libs: $(LIBS)

%.rel: %.s
	@echo -n "Assemble: "
	sdasz80  -plsgff  -o  $@ $<

%.rel: %.asm
	@echo -n "Assemble: "
	sdasz80  -plsgff  -o  $@ $<

%.asm: %.c
	@echo -n "Compile: "
	sdcc     -mz80  --fomit-frame-pointer -Wall  -S   $<   -o $@


$(TARGET).ihx: $(OBJ_ASM) $(OBJ_C)
	@echo -n "Link: "
	sdldz80  -mjwx  -b _KCC_HEADER=0x180 -b _CODE=0x200 $(LIBSLIST) -i $@  $^

$(TARGET).kcc: $(TARGET).ihx
	sdobjcopy  -I ihex -O binary   $<  $@
	python3 fix_kcc_length.py  $@


printf.lib:
	make --directory lib_printf

caos.lib:
	make --directory lib_caos


clean:
	rm -f *.sym
	rm -f *.lst
	rm -f *.rel
	rm -f $(TARGET).ihx
	rm -f $(TARGET).lk
	rm -f $(TARGET).map
	rm -f $(TARGET).noi


dist-clean: clean
	rm -f $(LIBS)
	rm -f caos.h
	make clean --directory lib_printf
	make clean --directory lib_caos
