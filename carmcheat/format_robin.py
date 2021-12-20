#!/usr/bin/env python
import argparse
import re

from carmcheat.algorithm import calc_hash, str2hash, hash2str


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("hash", help="Hash")
    parser.add_argument("file", help="Path to file posted by Robin")
    args = parser.parse_args()

    hashcode_arg = str2hash(args.hash)
    hashcode_arg_str = hash2str(hashcode_arg)

    for line_i, line in enumerate(open(args.file).readlines(), 1):
        match = re.search(r"([a-z]+)$", line)
        if match:
            cheat_text = match.group(1)
            if cheat_text == "unsat":
                continue
            cheat_code = calc_hash(cheat_text)
            if cheat_code != hashcode_arg:
                raise ValueError(f"{args.file}:{line_i}:{cheat_text} hashes to {hash2str(cheat_code)}, not {hashcode_arg_str}")
            print(f"{args.hash}:{cheat_text}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
