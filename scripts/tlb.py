def tlb(addr):
    binary = '{0:032b}'.format(addr)
    split = f'{binary[0:12]} {binary[12:22]} {binary[22:]}'.split(' ')
    split.reverse()
    return [int(i, 2) for i in split]


addresses = [
    0x800,
    0xB8000
]

for addr in addresses:
    print(f"tlb for {hex(addr)} = {tlb(addr)}")
