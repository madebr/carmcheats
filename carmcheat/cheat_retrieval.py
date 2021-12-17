#!/usr/bin/env python
import argparse
import z3

from carmcheat.algorithm import hash2str, str2hash


def char_to_val(x):
    return ord(x.lower()) - ord("a") + 22


def step(code, code2, sum, inp):
    sum += inp
    code += (inp << 11)
    code = z3.LShR(code, 17) + (code << 4)
    code2 = z3.LShR(code2, 29) + (code2 << 3) + inp * inp
    return code, code2, sum


def final(code, code2, sum):
    return z3.LShR(code, 11) + (sum << 21), code2


def run(target_codes, length, crib, database, database_filename=None):
    for offset in range(length - len(crib) + 1):
        keycodes = [z3.BitVec(f"k_{i}", 32) for i in range(length)]
        s = z3.Solver()

        # All characters are [a-z]
        for k in keycodes:
            s.add(k >= 22)
            s.add(k < 22 + 26)

        # Apply the Carmageddon hashing algorithm on the keycodes
        code = code2 = sum = z3.BitVecVal(0, 32)
        for k in keycodes:
            code, code2, sum = step(code, code2, sum, k)
        for c, k in zip(crib, keycodes[offset:]):
            s.add(k == char_to_val(c))
        code, code2 = final(code, code2, sum)
        s.add(code == target_codes[0])
        s.add(code2 == target_codes[1])
        for dbitem in database:
            s.add(z3.Or(*[k != char_to_val(dbitem[ki]) for ki, k in enumerate(keycodes)]))
        while (t := s.check()) == z3.sat:
            cleartext = "".join(chr(s.model()[k].as_long() + ord('a') - 22) for k in keycodes)
            print(f"{hash2str(target_codes)}:{cleartext}")
            s.add(z3.Or(*[k != s.model()[k].as_long() for k in keycodes]))
            if database_filename:
                with open(database_filename, "a") as fn:
                    fn.write(f"{hash2str(target_codes)}:{cleartext}\n")
        if not crib:
            break  # don't needlessly loop when no crib


def main():
    parser = argparse.ArgumentParser(allow_abbrev=False,
                                     description="Use SAT solver to find cheat codes hashing to a target")
    parser.add_argument("target", help="Target hash (format=XXXXXXXX:XXXXXXXX), where X is hexadecimal")
    parser.add_argument("length", type=int, help="Length of cheat code")
    parser.add_argument("--crib", default="", help="Find only cheat codes that contain the 'crib'")
    parser.add_argument("--database", metavar="DB", help="Append found cheat codes to this database")
    args = parser.parse_args()

    hash_target_str = args.target.strip()

    try:
        target_codes = str2hash(hash_target_str)
    except ValueError:
        parser.error("Invalid target. It needs to be in the XXXXXXXX:XXXXXXXX format.")

    database = []
    if args.database:
        try:
            for line in open(args.database, "r").readlines():
                hash_str, cleartext = line.strip().rsplit(":", 1)
                if hash_str == hash_target_str and len(cleartext) == args.length:
                    database.append(cleartext)
        except FileNotFoundError:
            pass

    print(f"Looking for cheat codes hashing to {hash_target_str}:")

    if database:
        print(f"Found {len(database)} entries in the database:")
        for entry in database:
            print(f"{hash_target_str}:{entry}")

    print("Starting search...")

    run(target_codes, args.length, args.crib, database, database_filename=args.database)

    print(f"Search finished")


if __name__ == "__main__":
    raise SystemExit(main())
