#include "IO/printk.h"
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include <convert/from_str.h>

// Order of the format specifiers:
enum {
	ALIGNMENT,
	PREPEND,
	PADDING,
	WIDTH,
	PRECISION,
	CASTING,
	TYPE,
	END
};

typedef int (*fmt_func)(directive_args_t *fmt, int *mode, const char **str);

struct format_specifier {
	enum {
		DIGITS,
		MINUS,
		STAR,
		HASH,
		ZERO,
		SPACE,
		CHAR,
	} type;
	fmt_func func;
};

static int parse_alignment(directive_args_t *fmt, int *mode, const char **str)
{
	if (*mode > ALIGNMENT) // Alignment has nothing to do here...
		return 0;
	fmt->align = **str == '-';
	*mode = PREPEND;
	return fmt->align;
}

static int parse_hash(directive_args_t *fmt, int *mode, const char **str)
{
	if (*mode > PREPEND) // Hash has nothing to do here...
		return 0;
	fmt->hash = **str == '#';
	*mode = PADDING;
	return fmt->hash;
}

static int parse_zero(directive_args_t *fmt, int *mode, const char **str)
{
	if (*mode > PADDING) // Zero has nothing to do here...
		return 0;
	if (fmt->space) // Space and zero are mutually exclusive
		return 0;
	fmt->zero = **str == '0';
	*mode = WIDTH;
	return fmt->zero;
}

static int parse_space(directive_args_t *fmt, int *mode, const char **str)
{
	if (*mode > PADDING) // Space has nothing to do here...
		return 0;
	if (fmt->zero) // Mutually exclusive with zero
		return 0;
	fmt->space = **str == ' ';
	*mode = WIDTH;
	return fmt->space;
}

static int parse_width(directive_args_t *fmt, int *mode, const char **str)
{
	if (*mode > WIDTH) // Width has nothing to do here...
		return 0;
	fmt->fwidth = isdigit(**str) || **str == '*';
	if (!fmt->fwidth)
		goto end;

	if (**str == '*')
	{
		fmt->width = -1;
		// (*str)++;
	}
	else
	{
		fmt->width = str_to_int32(*str);
		while (isdigit(**str))
			(*str)++;
		*str -= 1;
	}

end:
	*mode = PRECISION;
	return fmt->fwidth;
}

static int parse_precision(directive_args_t *fmt, int *mode, const char **str)
{
	if (*mode > PRECISION) // Precision has nothing to do here...
		return 0;
	fmt->fprecision = isdigit(**str) || **str == '*';

	if (!fmt->fprecision)
		goto end;

	if (**str == '*')
	{
		fmt->precision = -1;
		// (*str)++;
	}
	else
	{
		fmt->precision = str_to_int32(*str);
		while (isdigit(**str))
			(*str)++;
		*str -= 1;
	}

end:
	*mode = CASTING;
	return fmt->fprecision;
}

static int parse_casting(directive_args_t *fmt, int *mode, const char **str)
{
	if (*mode > CASTING) // Casting has nothing to do here...
		return 0;
	int set = 1;
	if (**str == 'g' || **str == 'G')
		fmt->cast = PRINTK_CAST_DOUBLEWORD;
	else if (**str == 'h' || **str == 'H')
		fmt->cast = PRINTK_CAST_HALFWORD;
	else if (**str == 'B') // 'b' is already used for boolean
		fmt->cast = PRINTK_CAST_BYTE;
	else if (**str == 'w' || **str == 'W')
		fmt->cast = PRINTK_CAST_WORD;
	else
		set = 0;

	*mode = TYPE;
	return set;
}

static int parse_type(directive_args_t *fmt, int *mode, const char **str)
{
	if (*mode > TYPE) // Type has nothing to do here...
		return 0;
	if (**str == PRINTK_TYPE_BINARY ||
		**str == PRINTK_TYPE_OCTAL ||
		**str == PRINTK_TYPE_DECIMAL ||
		**str == PRINTK_TYPE_HEX ||
		**str == PRINTK_TYPE_UNSIGNED ||
		**str == PRINTK_TYPE_STRING ||
		**str == PRINTK_TYPE_CHAR ||
		**str == PRINTK_TYPE_POINTER ||
		**str == PRINTK_TYPE_PERCENT ||
		**str == PRINTK_TYPE_BOOL)
		fmt->type = **str;
	else
		return 0;
	*mode = END;
	return 1;
}

static struct format_specifier specifiers[] = {
	{ MINUS, parse_alignment },
	{ HASH, parse_hash },
	{ ZERO, parse_zero },
	{ SPACE, parse_space },
	{ DIGITS, parse_width },
	{ DIGITS, parse_precision },
	{ CHAR, parse_casting },
	{ CHAR, parse_type },
};

void printk_parse_fmt(const char **fmt_str, directive_args_t *fmt)
{
	int mode = ALIGNMENT;
	const size_t max = sizeof(specifiers) / sizeof(struct format_specifier);

	memset(fmt, 0, sizeof(directive_args_t));
	for (; **fmt_str && mode != END; (*fmt_str) += 1)
	{
		for (size_t j = 0; j < max; j++)
		{
			if (specifiers[j].func(fmt, &mode, fmt_str))
				break;
		}
	}
}
