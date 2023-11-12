; Define all needed constants for multiboot2
%define MAGIC						0xE85250D6
%define ARCH						0

%define MULTIBOOT_TAG_TYPE_END		0


%define LENGTH						(_multiboot_hdr_end - _multiboot_hdr_start)
%define CHECKSUM					-(MAGIC + ARCH + LENGTH)


section								.multiboot.data
_multiboot_hdr_start:
	align							4
	dd								MAGIC
	dd								ARCH
	dd								LENGTH
	dd								CHECKSUM

_multiboot_tags:
; Define all tags here

; End of tags
	dw								MULTIBOOT_TAG_TYPE_END
	dw								0
	dd								8

_multiboot_hdr_end:
