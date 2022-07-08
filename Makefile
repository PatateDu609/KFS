VERSION				=	0.1.0
NAME_BIN			=	kfs-${VERSION}.bin
NAME_ISO			=	kfs-${VERSION}.iso

AS					:=	@$(TARGET)-as
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

CFLAGS				:=	-O2 -Wall -Werror -Wextra 	\
						-g							\
						-std=gnu99					\
						-ffreestanding				\
						-fno-exceptions				\
						-fno-stack-protector		\
						-nostdlib					\
						-nodefaultlibs				\
						-I$(PATH_INC)				\
						-I$(PATH_INC)/libc			\

ASFLAGS				:=
LDFLAGS				:=	-T $(LINKER) -L$(PATH_LIB_GCC) -l gcc -g

BASENAME			:=	kernel.c					\
						boot.s						\
						system/IO/init.c			\
						system/IO/terminal.c		\
						system/IO/write.c			\
						system/IO/read.c			\
						system/IO/cursor.c			\
						system/CPU/mode.c			\
						system/CPU/interrupts.c		\
						\
						libc/string/strlen.c		\
						libc/string/strcpy.c		\
						libc/string/strncpy.c		\
						libc/string/strcmp.c		\
						libc/string/strncmp.c		\
						libc/string/strcat.c		\
						libc/string/strncat.c		\
						libc/string/strchr.c		\
						libc/string/strstr.c		\
						libc/memory/memset.c		\
						libc/memory/memmove.c		\
						libc/memory/memcpy.c		\
						libc/memory/memchr.c		\
						libc/memory/memcmp.c		\
						libc/ctype/iscntrl.c		\
						libc/ctype/isalnum.c		\
						libc/ctype/isgraph.c		\
						libc/ctype/isupper.c		\
						libc/ctype/isprint.c		\
						libc/ctype/ispunct.c		\
						libc/ctype/toupper.c		\
						libc/ctype/tolower.c		\
						libc/ctype/isdigit.c		\
						libc/ctype/islower.c		\
						libc/ctype/isxdigit.c		\
						libc/ctype/isspace.c		\
						libc/ctype/isalpha.c		\

GRUB_CFG			:=	grub.cfg

SRC					:=	$(addprefix $(PATH_SRC)/, $(BASENAME))

OBJ					:=	$(addprefix $(PATH_OBJ)/, $(BASENAME:.c=.o))
OBJ					:=	$(OBJ:.s=.o)
# DEP					:=	$(addprefix $(PATH_OBJ)/, $(BASENAME:.c=.d))


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
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_BIN):		$(OBJ)
	$(ECHO) "${INFO} ${BBLUE}LD${BLUE}\t  $(basename $@)$(RESET)"
	$(LD) -o $@ $^ $(LDFLAGS)

clean:
	@rm -rf $(PATH_OBJ)

fclean: clean
	@rm -f $(NAME_BIN)
	@rm -rf $(PATH_ISO)

re:				fclean all

is_multiboot:
	@if grub-file --is-x86-multiboot $(NAME_BIN); then \
		/bin/echo -e "${SUCCESS} Multiboot confirmed ${RESET}" ; \
	else \
		/bin/echo -e "${ERROR} The file is not multiboot ${RESET}" ; \
		exit 1 ; \
	fi

$(NAME_ISO):		$(NAME_BIN) is_multiboot
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
	$(QEMU) -cdrom $(NAME_ISO) -display curses

run_gtk:			$(NAME_ISO)
	$(QEMU) -cdrom $(NAME_ISO) -display gtk

run_debug:			$(NAME_ISO)
	$(QEMU) -cdrom $(NAME_ISO) -display curses -S -s

.PHONY: all clean fclean re is_multiboot run_curses run_gtk
