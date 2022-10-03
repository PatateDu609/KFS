VERSION				=	0.3.0
NAME_BIN			=	kfs-${VERSION}.bin
NAME_DBG			=	kfs-${VERSION}.dbg
NAME_ISO			=	kfs-${VERSION}.iso

AS					:=	@nasm
CC					:=	@$(TARGET)-gcc
LD					:=	@$(TARGET)-ld
QEMU				:=	@qemu-system-$(TARGET:-elf=)
ECHO				:=	@/bin/echo -e

PATH_SRC			:=	src
PATH_OBJ			:=	obj
PATH_INC			:=	include
PATH_ISO			:=	iso
PATH_LIB_GCC		:=	cross-compiler/lib/gcc/i386-elf/12.1.0/
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

BASENAME			:=	kernel.c								\
						multiboot.c								\
						system/panic.c							\
						system/boot/boot.s						\
						system/boot/multiboot.s					\
						system/boot/pic.s						\
						system/boot/GDT/load.s					\
						system/boot/GDT/init.c					\
						system/boot/GDT/print_stack.c			\
						system/boot/IDT/load.s					\
						system/boot/IDT/init.c					\
						system/boot/IDT/isr.c					\
						system/boot/IDT/irq.c					\
						system/boot/IDT/wrappers.c				\
						system/boot/Paging/load.s				\
						system/boot/Paging/init_physical.c		\
						system/IO/init.c						\
						system/IO/terminal.c					\
						system/IO/write.c						\
						system/IO/cursor.c						\
						system/IO/colors.c						\
						system/IO/keyboard.c					\
						system/IO/printk/printk.c				\
						system/IO/printk/formats/binary.c		\
						system/IO/printk/formats/bool.c			\
						system/IO/printk/formats/char.c			\
						system/IO/printk/formats/hex.c			\
						system/IO/printk/formats/int.c			\
						system/IO/printk/formats/octal.c		\
						system/IO/printk/formats/percent.c		\
						system/IO/printk/formats/pointer.c		\
						system/IO/printk/formats/string.c		\
						system/IO/printk/formats/uint.c			\
						system/IO/printk/parsing.c				\
						system/CPU/mode.c						\
						system/CPU/interrupts.c					\
						\
						nanoshell/shell.c						\
						nanoshell/commands/reboot.c				\
						nanoshell/commands/shutdown.c			\
						nanoshell/commands/halt.c				\
						nanoshell/commands/stack.c				\
						nanoshell/commands/clear.c				\
						nanoshell/commands/lsmmap.c				\
						\
						libc/string/strlen.c					\
						libc/string/strcpy.c					\
						libc/string/strncpy.c					\
						libc/string/strcmp.c					\
						libc/string/strncmp.c					\
						libc/string/strcat.c					\
						libc/string/strncat.c					\
						libc/string/strchr.c					\
						libc/string/strstr.c					\
						libc/memory/memset.c					\
						libc/memory/memmove.c					\
						libc/memory/memcpy.c					\
						libc/memory/memchr.c					\
						libc/memory/memcmp.c					\
						libc/ctype/iscntrl.c					\
						libc/ctype/isalnum.c					\
						libc/ctype/isgraph.c					\
						libc/ctype/isupper.c					\
						libc/ctype/isprint.c					\
						libc/ctype/ispunct.c					\
						libc/ctype/toupper.c					\
						libc/ctype/tolower.c					\
						libc/ctype/isdigit.c					\
						libc/ctype/islower.c					\
						libc/ctype/isxdigit.c					\
						libc/ctype/isspace.c					\
						libc/ctype/isalpha.c					\
						libc/convert/to_str/from_int32.c		\
						libc/convert/to_str/from_uint32.c		\
						libc/convert/to_str/from_double.c		\
						libc/convert/to_str/from_float.c		\
						libc/convert/to_str/from_int8.c			\
						libc/convert/to_str/from_uint16.c		\
						libc/convert/to_str/from_uint64.c		\
						libc/convert/to_str/from_bool.c			\
						libc/convert/to_str/from_int64.c		\
						libc/convert/to_str/from_uint8.c		\
						libc/convert/to_str/from_int16.c		\
						libc/convert/from_str/to_uint32.c		\
						libc/convert/from_str/to_uint16.c		\
						libc/convert/from_str/to_uint64.c		\
						libc/convert/from_str/to_int64.c		\
						libc/convert/from_str/to_uint8.c		\
						libc/convert/from_str/to_double.c		\
						libc/convert/from_str/to_int8.c			\
						libc/convert/from_str/to_bool.c			\
						libc/convert/from_str/to_int32.c		\
						libc/convert/from_str/to_float.c		\
						libc/convert/from_str/to_int16.c		\

GRUB_CFG			:=	grub.cfg

SRC					:=	$(addprefix $(PATH_SRC)/, $(BASENAME))

OBJ					:=	$(addprefix $(PATH_OBJ)/, $(BASENAME:.c=.o))
OBJ					:=	$(OBJ:.s=.o)
DEP					:=	$(addprefix $(PATH_OBJ)/, $(BASENAME:.c=.d))


################################################################################################################################################################

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

INFO				:=	${BBLUE}❯ $(BLUE)
WARNING				:=	${BYELLOW}⚠$(YELLOW)
ERROR				:=	${BRED}✗$(RED)
SUCCESS				:=	${BGREEN}✓$(GREEN)

################################################################################################################################################################

all:				$(NAME_ISO)

${PATH_OBJ}/%.o:	${PATH_SRC}/%.s
	@mkdir -p $(dir $@)
	$(ECHO) "${INFO} ${BBLUE}AS${BLUE}\t  $(subst $(PATH_SRC)/,,$<)$(RESET)"
	$(AS) $(ASFLAGS) $< -o $@

${PATH_OBJ}/%.o:	${PATH_SRC}/%.c
	@mkdir -p $(dir $@)
	$(ECHO) "${INFO} ${BBLUE}CC${BLUE}\t  $(subst $(PATH_SRC)/,,$<)$(RESET)"
	$(CC) $(CFLAGS) -c -MMD $< -o $@

-include $(DEP)

$(NAME_BIN):		$(OBJ)
	$(ECHO) "${INFO} ${BBLUE}LD${BLUE}\t  $(basename $@)$(RESET)"
	@rm -f $(NAME_DBG)
	$(LD) -o $@ $^ $(LDFLAGS)

clean:
	@rm -rf $(PATH_OBJ)

fclean: clean
	@rm -f $(NAME_BIN) $(NAME_ISO) $(NAME_DBG)
	@rm -rf $(PATH_ISO)

re:				fclean all

is_multiboot:
	@if grub-file --is-x86-multiboot2 $(NAME_BIN); then \
		/bin/echo -e "${SUCCESS} Multiboot2 confirmed ${RESET}" ; \
	else \
		/bin/echo -e "${ERROR} The file is not multiboot ${RESET}" ; \
		exit 1 ; \
	fi

$(NAME_ISO):		$(NAME_DBG) $(GRUB_CFG) is_multiboot
	@mkdir -p $(PATH_ISO)/boot/grub
	@cp $(NAME_BIN) $(PATH_ISO)/boot/
	@cp $(GRUB_CFG) $(PATH_ISO)/boot/grub/
	@sed -i 's/__VERSION__/$(VERSION)/g' $(PATH_ISO)/boot/grub/$(GRUB_CFG)
	@grub-mkrescue -o $@ $(PATH_ISO) >/dev/null 2>&1

	@if [ $$? -eq 0 ]; then \
		/bin/echo -e "${SUCCESS} ISO created ${RESET}" ; \
	else \
		/bin/echo -e "${ERROR} ISO creation failed ${RESET}" ; \
		exit 1 ; \
	fi

run_curses:			$(NAME_ISO)
	$(QEMU) -m 1G -D ./log.txt -cdrom $(NAME_ISO) -display curses

run_dist_monitor:		$(NAME_ISO)
	$(QEMU) -D ./log.txt -cdrom $(NAME_ISO) -display curses -monitor telnet:localhost:1234,server,nowait

run_gtk:			$(NAME_ISO)
	$(QEMU) -cdrom $(NAME_ISO) -display gtk

run_debug:			$(NAME_ISO)
	$(QEMU) -cdrom $(NAME_ISO) -display curses -S -s

debug:
	@gdb -x .gdbinit

monitor:
	@telnet localhost 1234

$(NAME_DBG):		$(NAME_BIN)
	@if [ -f $(NAME_DBG) ]; then \
		/bin/echo -e "${WARNING} $(NAME_DBG) already exists ${RESET}" ; \
	else \
		/bin/echo -e "${INFO} Optimizing size ${RESET}"; \
		\
		$(TARGET)-objcopy -R .gnu_debuglink $(NAME_BIN); \
		$(TARGET)-objcopy --only-keep-debug $(NAME_BIN) $(NAME_DBG); \
		$(TARGET)-objcopy --strip-all $(NAME_BIN); \
		$(TARGET)-objcopy --add-gnu-debuglink=$(NAME_DBG) $(NAME_BIN); \
	fi


.PHONY: all clean fclean re is_multiboot run_curses run_gtk run_dist_monitor run_debug debug monitor
