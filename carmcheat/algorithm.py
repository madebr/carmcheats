#!/usr/bin/env python

import argparse
import math
import typing


def cheat_length_range(hash: typing.Tuple[int, int]) -> typing.Tuple[int, int]:
    sum_numbers = hash[0] >> 21
    min_length = math.ceil(sum_numbers / char2number("z"))
    max_length = math.floor(sum_numbers / char2number("a"))
    return min_length, max_length


def char2number(char: str) -> int:
    return ord(char.lower()) - ord('a') + 22


def number2char(number: int) -> str:
    return chr(number + ord('a') - 22)


def hash_init() -> typing.Tuple[int, int, int]:
    return 0, 0, 0


def hash_update(code1: int, code2: int, sum: int, char: str) -> typing.Tuple[int, int, int]:
    lc = char2number(char)
    sum = (sum + lc) % (1 << 32)
    code1 = (code1 + (lc << 11)) % (1 << 32)
    code1 = ((code1 >> 17) + (code1 << 4)) % (1 << 32)
    code2 = ((code2 >> 29) + (code2 << 3) + lc * lc) % (1 << 32)
    return code1, code2, sum


def hash_final(code1: int, code2: int, sum: int):
    return ((code1 >> 11) + (sum << 21)) % (1 << 32), code2


def calc_hash(text: str) -> typing.Tuple[int, int]:
    state = hash_init()
    for char in text:
        state = hash_update(*state, char)
    return hash_final(*state)


def hash2str(hash: typing.Tuple[int, int]) -> str:
    return f"{hash[0]:08x}:{hash[1]:08x}"


def str2hash(text: str) -> typing.Tuple[int, int]:
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
