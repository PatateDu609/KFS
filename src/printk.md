# printk format (usable in panics).

The printk format can contain strings and format specifiers that always begin
with a '%' and ends with a "printer directive" that will dictate how the
corresponding argument should be printed. Each format can also contain some
specifiers that indicates how each variable needs to be processed.

## Printing directives

| Directive | Printing style                    |
| --------- | --------------------------------- |
| %         | The symbol '%' itself             |
| d         | Signed decimal                    |
| x         | Hexadecimal                       |
| o         | Octal                             |
| t         | Binary                            |
| b         | Boolean                           |
| u         | Unsigned decimal                  |
| s         | String                            |
| c         | A single character                |
| p         | Hexadecimal formated as a pointer |

## Casting directive

Each format can contain casting directive to enforce a specific type depending
of the wanted printing style. However, it works only with numeral types.

| Directive | Size                         |
| --------- | ---------------------------- |
| g         | double word (8 bytes)        |
| w         | word (4 bytes)               |
| h         | halfword (2 bytes - Default) |
| b         | byte                         |

## Formatting specifiers

Several specifier can be passed within the format string to enforce a specific display.

| Order | Specifier                      | Effect                                                        |
| ----- | ------------------------------ | ------------------------------------------------------------- |
| 1     | -                              | Alignment to the right                                        |
| 2     | #                              | Prepend number depending of printing style                    |
| 3     | 0 or space                     | If type is a number then it will be padded with 0 (or space). |
| 4     | width (positive integer)       | Width of the field                                            |
| 5     | .precision (comes after a dot) | Specifies how many characters should be displayed.            |

Width and precision can also be replaced by a '*' that will take its value from
the argument list.

## Order of specifiers

1) '%': Start of the format, **It is mandatory**
2) '-': Alignment to the right
3) '#': Prepend 0, 0b or 0x depending of what should be printed
4) 0 or space: Specifies if output should be padded with zeroes or spaces
5) width: Width of the field (digits or star)
6) .precision: How many characters should be printed (takes digits or star)
7) casting: As explained above
8) printing directive: As explained above **It is mandatory**
