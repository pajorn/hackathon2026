import sys

def read_file(fname: str) -> list[str]:
    file = open(fname, "r")
    lines = file.read().splitlines()
    file.close()
    return lines


def parse_instr(instr: str):
        instr = instr.replace(",", "") # remove commas
        parts = instr.split(" ")
        operation = parts[0]
        operands = parts[1:]
        print(f"operation: {operation}, operands: {operands}")


def assemble(fname):
    oname = fname[:-3] + "bin"
    print(f"oname: {oname}")
    instrs = read_file(fname)
    for instr in instrs:
        print(instr)
        parse_instr(instr)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("invalid params")
        sys.exit(1)

    assemble(sys.argv[1])
