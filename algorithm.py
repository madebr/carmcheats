#!/usr/bin/env python

import argparse


def calc_hash(text: str):
    s, c1, c2 = 0, 0, 0
    for c in text:
        lc = ord(c.lower()) - ord('a') + 22
        s = (s + lc) % (1 << 32)
        c1 = (c1 + (lc << 11)) % (1 << 32)
        c1 = ((c1 >> 17) + (c1 << 4)) % (1 << 32)
        c2 = ((c2 >> 29) + (c2 << 3) + lc * lc) % (1 << 32)
    h1 = ((c1 >> 11) + (s << 21)) % (1 << 32)
    h2 = c2
    return h1, h2


def hash2str(hash):
    return f"{hash[0]:08x}:{hash[1]:08x}"


def str2hash(text):
    result = tuple(int(s, 16) for s in text.split(":"))
    if len(result) != 2 or any(c < 0 or c & 0xffffffff != c for c in result):
        raise ValueError("text is not a valid hash")
    return result


def main():
    parser = argparse.ArgumentParser(description="Hash some cheat codes")
    parser.add_argument("cheatcodes", metavar="CHEATCODE", nargs="+", help="Cheat code to hash")
    args = parser.parse_args()

    for cheatcode in args.cheatcodes:
        print(f"{hash2str(calc_hash(cheatcode))}:{cheatcode}")


if __name__ == "__main__":
    raise SystemExit(main())