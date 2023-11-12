SHELL := /bin/bash

VERSION				=	0.3.0
NAME_BIN			=	kfs-${VERSION}.bin
NAME_DBG			=	kfs-${VERSION}.dbg
NAME_ISO			=	kfs-${VERSION}.iso

AS					:=	@nasm
CC					:=	@$(TARGET)-gcc
LD					:=	@$(TARGET)-ld
OBJCOPY				:=	$(TARGET)-objcopy
QEMU				:=	@qemu-system-$(TARGET:-elf=)
PRINTF				:=	@printf

PATH_SRC			:=	src
PATH_OBJ			:=	obj
PATH_INC			:=	include
PATH_ISO			:=	iso
PATH_LIB_GCC		:=	/kfs/cross-compiler/lib/gcc/i386-elf/${GCC_VERSION}/
PATH_LOG			:=	log

LINKER				:=	$(PATH_SRC)/linker.ld

CFLAGS				:=	-Wall -Werror -Wextra 			\
						-ggdb -g3						\
						-ffreestanding					\
						-std=gnu99						\
						-nostdlib						\
						-nodefaultlibs					\
						-ffunction-sections				\
						-fdata-sections					\
						-I$(PATH_INC)					\
						-I$(PATH_INC)/libc				\

ASFLAGS				:=	-f elf32 -g -F dwarf
LDFLAGS				:=	-T $(LINKER) -L$(PATH_LIB_GCC) -lgcc --gc-sections

RAM_SIZE			:=	1G								# size in MB
QEMU_FLAGS			:=	-m $(RAM_SIZE) #-no-reboot -no-shutdown

include sources.mk

GRUB_CFG			:=	grub.cfg

SRC					:=	$(addprefix $(PATH_SRC)/, $(BASENAME))

OBJ					:=	$(addprefix $(PATH_OBJ)/, $(BASENAME:.c=.o))
OBJ					:=	$(OBJ:.s=.o)
DEP					:=	$(addprefix $(PATH_OBJ)/, $(BASENAME:.c=.d))


########################################################################################################################

RED					:=	\e[0;31m
GREEN				:=	\e[0;32m
YELLOW				:=	\e[0;33m
BLUE				:=	\e[0;34m
MAGENTA				:=	\e[0;35m
CYAN				:=	\e[0;36m
RESET				:=	\e[0m

BRED				:=	\e[1;31m
BGREEN				:=	\e[1;32m
BYELLOW				:=	\e[1;33m
BBLUE				:=	\e[1;34m
BMAGENTA			:=	\e[1;35m
BCYAN				:=	\e[1;36m
BYELLOW				:=	\e[1;33m

INFO				:=	${BBLUE} ❯ $(BLUE)
WARNING				:=	${BYELLOW} ⚠$(YELLOW)
ERROR				:=	${BRED} ✗$(RED)
SUCCESS				:=	${BGREEN} ✓$(GREEN)

########################################################################################################################

all:				run

run:
	@cd docker && source setup.sh && ${MAKE} -C .. $(NAME_ISO) TARGET=$$TARGET GCC_VERSION=$$GCC_VERSION

-include $(DEP)

${PATH_OBJ}/%.o:	${PATH_SRC}/%.s
	@mkdir -p $(dir $@)
	$(PRINTF) "${INFO} ${BBLUE}AS${BLUE}\t  $(subst $(PATH_SRC)/,,$<)$(RESET)\n"
	$(AS) $(ASFLAGS) $< -o $@

${PATH_OBJ}/%.o:	${PATH_SRC}/%.c
	@mkdir -p $(dir $@)
	$(PRINTF) "${INFO} ${BBLUE}CC${BLUE}\t  $(subst $(PATH_SRC)/,,$<)$(RESET)\n"
	$(CC) $(CFLAGS) -c -MMD $< -o $@

$(NAME_BIN):		$(OBJ) $(LINKER)
	$(PRINTF) "${INFO} ${BBLUE}LD${BLUE}\t  $(basename $@)$(RESET)\n"
	rm -f $(NAME_DBG)
	$(LD) -o $@ $(filter-out $(LINKER),$(OBJ)) $(LDFLAGS)

build: $(NAME_DBG)

clean:
	@rm -rf $(PATH_OBJ)

fclean: clean
	@rm -f $(NAME_BIN) $(NAME_ISO) $(NAME_DBG)
	@rm -rf $(PATH_ISO)

re:				fclean all

is_multiboot: $(NAME_BIN)
	@if grub-file --is-x86-multiboot2 $(NAME_BIN); then \
		printf "${SUCCESS} Multiboot2 confirmed ${RESET}\n" ; \
	else \
		printf "${ERROR} The file is not multiboot ${RESET}\n" ; \
		exit 1 ; \
	fi

$(NAME_ISO):		$(NAME_DBG) $(GRUB_CFG) is_multiboot
	@mkdir -p $(PATH_ISO)/boot/grub
	@cp $(NAME_BIN) $(PATH_ISO)/boot/
	@cp $(GRUB_CFG) $(PATH_ISO)/boot/grub/
	@sed -i 's/__VERSION__/$(VERSION)/g' $(PATH_ISO)/boot/grub/$(GRUB_CFG)
	@grub-mkrescue -o $@ $(PATH_ISO) >/dev/null 2>&1

	@if [ $$? -eq 0 ]; then \
		printf "${SUCCESS} ISO created ${RESET}\n" ; \
	else \
		printf "${ERROR} ISO creation failed ${RESET}\n" ; \
		exit 1 ; \
	fi

run_curses:
	$(QEMU) -D ./log.txt -cdrom $(NAME_ISO) -display curses $(QEMU_FLAGS)

run_dist_monitor:		DISPLAY := curses
run_dist_monitor:
	$(QEMU) -D ./log.txt -cdrom $(NAME_ISO) -display $(DISPLAY) -monitor telnet:localhost:1234,server,nowait $(QEMU_FLAGS)

run_monitor:			DISPLAY := curses
run_monitor:
	$(QEMU) -D ./log.txt -cdrom $(NAME_ISO) -display $(DISPLAY) -monitor $(shell tty) $(QEMU_FLAGS)

run_gtk:			$(NAME_ISO)
	$(QEMU) -cdrom $(NAME_ISO) -display gtk $(QEMU_FLAGS)

run_cocoa:
	$(QEMU) -cdrom $(NAME_ISO) -display cocoa $(QEMU_FLAGS)

run_debug: 			DISPLAY := curses
run_debug:
	$(QEMU) -D ./log.txt -cdrom $(NAME_ISO) -display $(DISPLAY) -S -s $(QEMU_FLAGS)

debug:
	@gdb -x .gdbinit

monitor:
	@telnet localhost 1234

$(NAME_DBG):		$(NAME_BIN)
	@if [ -f $(NAME_DBG) ]; then \
		printf "${WARNING} $(NAME_DBG) already exists ${RESET}\n" ; \
	else \
		printf "${INFO} Optimizing size ${RESET}\n"; \
		\
		$(OBJCOPY) -R .gnu_debuglink $(NAME_BIN); \
		$(OBJCOPY) --only-keep-debug $(NAME_BIN) $(NAME_DBG); \
		$(OBJCOPY) --strip-all $(NAME_BIN); \
		$(OBJCOPY) --add-gnu-debuglink=$(NAME_DBG) $(NAME_BIN); \
	fi


.PHONY: all clean fclean re is_multiboot run_curses run_gtk run_dist_monitor run_debug debug monitor
