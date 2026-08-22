import sys
import numpy as np


operations = {"nop": 0,
              "mov": 1, 
              "ld": 2,
              "st": 3,
              "jmp": 4,
              "push": 5,
              "pop": 6,
              "ldi": 7}


def read_file(fname: str) -> list[str]:
    file = open(fname, "r")
    lines = file.read().splitlines()
    file.close()
    lines = [s for s in lines if s] # remove empty lines
    return lines


def parse_instr(instr: str):
        instr = instr.replace(",", "") # remove commas
        parts = instr.split(" ")
        operation = parts[0]
        operands = parts[1:]
        print(f"operation: {operation}, operands: {operands}")
        return (operation, operands)


def add_forward_ref_target(address: int, label: str, targets: dict):
    address += 1 # 2nd uint16 of instruction is address
    if label not in targets.keys():
        targets[label] = [address]
    else:
        targets[label].append(address)


def set_addrImm(opr: str, r1: int, r2: int, addrImm1: int,
                addrImm2: int, isHex: tuple[bool], targets: dict,
                address: int, operands: list[str]):
    out = 0
    if opr == "nop":
        pass
    elif opr == "mov":
        pass
    elif opr == "ld":
        pass
    elif opr == "st":
        pass
    elif opr == "jmp":
        out = addrImm1
        if not isHex[0]:
            add_forward_ref_target(address, operands[0], targets)
    elif opr == "push":
        pass
    elif opr == "pop":
        pass
    elif opr == "ldi":
        out = addrImm2
    return out


def instr_bytes(parsed: tuple[str, list[str]], targets: dict,
                address: int) -> tuple[int, int]:
    opr = parsed[0]
    operands = parsed[1]

    # not necessarily well defined. must pick correct vars
    # based on the operation
    r1 = r2 = 0
    addrImm1 = addrImm2 = 0
    outAddrImm = 0

    isHex = [False, False]
    if len(operands) >= 1 and operands[0][0:2] == "0x":
        isHex[0] = True
    if len(operands) == 2 and operands[1][0:2] == "0x":
        isHex[1] = True
    if len(operands) >= 1 and operands[0][0] == "r":
        r1 = int(operands[0][1:])
    if len(operands) == 2 and operands[1][0] == "r":
        r2 = int(operands[1][1:])
    if len(operands) >= 1 and isHex[0]:
        addrImm1 = int(operands[0], 16)
    if len(operands) == 2 and isHex[1]:
        addrImm2 = int(operands[1], 16)




    instr1 = operations[opr]
    instr1 |= (r1 << 12) | (r2 << 8)
    instr2 = set_addrImm(opr, r1, r2, addrImm1, addrImm2, isHex, targets, address, operands)

    return (instr1, instr2)


def assemble(fname):
    oname = fname[:-3] + "bin"
    print(f"oname: {oname}")
    instructionOffset = 0 # in words
    instrs = read_file(fname)
    labels = dict()
    labelTargets = dict()

    binary = np.zeros(0x4000, dtype=np.uint16)

    for i in range(len(instrs)):
        parsed = parse_instr(instrs[i])
        opr = parsed[0]

        if opr[-1] != ":": # isn't label
            bytecode = instr_bytes(parsed, labelTargets, instructionOffset)
            binary[instructionOffset] = bytecode[0]
            binary[instructionOffset+1] = bytecode[1]

            instructionOffset += 2 # 2 cells per instr
        else:
            labels[opr[:-1]] = instructionOffset

    print(labels)
    # solve forward (actually, all) references
    for key in labelTargets:
        for offset in labelTargets[key]:
            binary[offset] = labels[key]

    ofile = open(oname, "wb")
    binary.tofile(ofile)
    ofile.close()


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("invalid params")
        sys.exit(1)

    assemble(sys.argv[1])
