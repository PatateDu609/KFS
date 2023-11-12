def str_rev(s: str) -> str:
    rev = ""
    for c in s:
        rev = c + rev
    return rev


def tlb(addr: int) -> list[int]:
    binary = str_rev('{0:032b}'.format(addr))

    split = f'{str_rev(binary[0:12])} {str_rev(binary[12:22])} {str_rev(binary[22:])}'.split(' ')
    split.reverse()
    return [int(i, 2) for i in split]


addresses = [
    0x800,
    0xB8000
]

for addr in addresses:
    print(f"tlb for {hex(addr)} = {tlb(addr)}")
