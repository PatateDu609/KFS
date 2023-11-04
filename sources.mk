SYSTEM_BASENAME		:=	system/panic.c							\
						\
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
                        system/boot/Memory/load.s				\
                        system/boot/Memory/init_physical.c		\
                        system/boot/Memory/paging.c				\
                        \
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
						\
                        system/CPU/mode.c						\
                        system/CPU/interrupts.c					\
						\
                        system/memory/bitmap.c					\
                        system/memory/alloc.c					\

NANOSHELL_BASENAME	:=	nanoshell/shell.c						\
                        \
                        nanoshell/commands/reboot.c				\
                        nanoshell/commands/shutdown.c			\
                        nanoshell/commands/halt.c				\
                        nanoshell/commands/stack.c				\
                        nanoshell/commands/clear.c				\
                        nanoshell/commands/lsmmap.c				\

LIBC_BASENAME		:=	libc/string/strlen.c					\
                        libc/string/strcpy.c					\
                        libc/string/strncpy.c					\
                        libc/string/strcmp.c					\
                        libc/string/strncmp.c					\
                        libc/string/strcat.c					\
                        libc/string/strncat.c					\
                        libc/string/strchr.c					\
                        libc/string/strstr.c					\
                        \
                        libc/memory/memset.c					\
                        libc/memory/memmove.c					\
                        libc/memory/memcpy.c					\
                        libc/memory/memchr.c					\
                        libc/memory/memcmp.c					\
                        \
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
                        \
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

BASENAME			:=	kernel.c								\
						multiboot.c								\
						$(SYSTEM_BASENAME)						\
						$(NANOSHELL_BASENAME)					\
						$(LIBC_BASENAME)
