SRC_C = $(wildcard *.c)
OBJ_C = $(SRC_C:%.c=%.rel)

SRC_ASM = $(wildcard *.s)
OBJ_ASM = $(SRC_ASM:%.s=%.rel)


all: caos.lib
	cp $< ..
	cp caos.h ..

%.rel: %.s
	@echo -n "Assemble: "
	sdasz80  -plsgff  -o  $@ $<

%.rel: %.asm
	@echo -n "Assemble: "
	sdasz80  -plsgff  -o  $@ $<

%.asm: %.c
	@echo -n "Compile: "
	sdcc     -mz80  --fomit-frame-pointer       -Wall  -S   $<   -o $@

%.lib: $(OBJ_ASM) $(OBJ_C)
	@echo -n "Library: "
	sdar  -rc $@    $^


clean:
	rm -f *.sym
	rm -f *.lst
	rm -f *.rel
