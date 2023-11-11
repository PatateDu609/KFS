from typing import TypedDict

from lldb import SBDebugger, SBCommandReturnObject, SBFrame, SBValueList, SBValue


class Flag(TypedDict, total=True):
    name: str
    description: str


FLAGS: dict[str, dict[int, Flag]] = {
    "cr0": {
        0: {
            "name": "PE",
            "description": "Protection Enable",
        },
        1: {
            "name": "MP",
            "description": "Math Present",
        },
        2: {
            "name": "EM",
            "description": "Emulation",
        },
        3: {
            "name": "TS",
            "description": "Task Switched",
        },
        4: {
            "name": "ET",
            "description": "Extension Type",
        },
        5: {
            "name": "NE",
            "description": "Numeric Error",
        },
        16: {
            "name": "WP",
            "description": "Write Protect",
        },
        18: {
            "name": "AM",
            "description": "Alignment Mask",
        },
        29: {
            "name": "NW",
            "description": "Not Write Through",
        },
        30: {
            "name": "CD",
            "description": "Cache disable",
        },
        31: {
            "name": "PG",
            "description": "Paging",
        },
    },
    "eflags": {
        0: {
            "name": "CF",
            "description": 'Carry Flag',
        },
        2: {
            "name": "PF",
            "description": 'Parity Flag',
        },
        4: {
            "name": "AF",
            "description": 'Adjust Flag',
        },
        6: {
            "name": "ZF",
            "description": 'Zero Flag',
        },
        7: {
            "name": "SF",
            "description": "Sign Flag",
        },
        8: {
            "name": "TF",
            "description": "Trap Flag",
        },
        9: {
            "name": "IF",
            "description": "Interrupt Enable Flag",
        },
        10: {
            "name": "DF",
            "description": "Direction Flag",
        },
        11: {
            "name": "OF",
            "description": "Overflow Flag",
        },
        12: {
            "name": "IOPL_H",
            "description": "I/O privilege level High bit",
        },
        13: {
            "name": "IOPL_L",
            "description": "I/O privilege level Low bit",
        },
        14: {
            "name": "NT",
            "description": "Nested Task Flag",
        },
        16: {
            "name": "RF",
            "description": "Resume Flag",
        },
        17: {
            "name": "VM",
            "description": "Virtual 8086 mode flag",
        },
        18: {
            "name": "AC",
            "description": "Alignment Check / Access Control",
        },
        19: {
            "name": "VIF",
            "description": " Virtual Interrupt Flag",
        },
        20: {
            "name": "VIP",
            "description": "Virtual Interrupt Pending",
        },
        21: {
            "name": "ID",
            "description": "Identification Flag",
        }
    },
}


def parse_flags(reg: str, val: int) -> list[Flag]:
    """ Returns list of set flags """
    set_flags: list[Flag] = []

    if reg not in FLAGS:
        return set_flags

    flags = FLAGS[reg]

    for bit in range(32):
        if val & (1 << bit) and bit in flags:
            set_flags.append(flags[bit])

    return set_flags


def flag_list_to_str(flags: list[Flag]) -> str:
    return ' '.join([flag["name"] for flag in flags])


def get_needed_regs(frame: SBFrame) -> list[SBValue]:
    grs = list()

    registers: SBValueList = frame.GetRegisters()
    rs: SBValue
    for rs in registers:
        if rs.GetName().lower() == 'general':
            grs = rs
            break

    res = []
    reg: SBValue
    for reg in grs:
        name = reg.GetName()
        if 'cr' in name or name == 'eflags':
            res.append(reg)

    return res


def fmt_lst(result: SBCommandReturnObject, fl_reg: list[SBValue], lst: list[str]):
    for flag in fl_reg:
        if flag.GetName().lower() not in lst:
            continue

        val: int = flag.GetValueAsUnsigned()
        reg_print_width = flag.GetByteSize() * 2
        parsed = parse_flags(flag.GetName(), val)

        if len(parsed) == 0:
            ln = ("%s: 0x%.*x\n" % (
                flag.GetName(),  # register name
                reg_print_width,  # how many hex digits to print
                val,  # value
            ))
        else:
            ln = ("%s: 0x%.*x [%s]\n" % (
                flag.GetName(),  # register name
                reg_print_width,  # how many hex digits to print
                val,  # value
                flag_list_to_str(parsed)  # parsed value (list of set flags)
            ))
        result.Print(ln)


def fmt_all(result: SBCommandReturnObject, fl_reg: list[SBValue]):
    for flag in fl_reg:
        val: int = flag.GetValueAsUnsigned()
        reg_print_width = flag.GetByteSize() * 2
        parsed = parse_flags(flag.GetName(), val)

        if len(parsed) == 0:
            ln = ("%s: 0x%.*x\n" % (
                flag.GetName(),  # register name
                reg_print_width,  # how many hex digits to print
                val,  # value
            ))
        else:
            ln = ("%s: 0x%.*x [%s]\n" % (
                flag.GetName(),  # register name
                reg_print_width,  # how many hex digits to print
                val,  # value
                flag_list_to_str(parsed)  # parsed value (list of set flags)
            ))
        result.Print(ln)


def regs_cmd(debugger: SBDebugger,
             command: str,
             result: SBCommandReturnObject,
             internal_dict: dict):
    """ This command prints a formatted output of control and flag registers """
    target = debugger.GetSelectedTarget()
    process = target.GetProcess()
    thread = process.GetSelectedThread()
    frame: SBFrame = thread.GetSelectedFrame()

    fl_reg = get_needed_regs(frame)
    if fl_reg is None:
        print("ERROR: Cant find flags register!")
        return

    if len(command) == 0:
        fmt_all(result, fl_reg)
    else:
        fmt_lst(result, fl_reg, command.lower().split(" "))


def __lldb_init_module(debugger: SBDebugger, internal_dict: dict):
    debugger.HandleCommand("command script add -f registers.regs_cmd regs")
