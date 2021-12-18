#!/usr/bin/env python

import argparse
import sys

from carmcheat.algorithm import calc_hash, hash2str, cheat_length_range


def main():
    parser = argparse.ArgumentParser(description="Verify a database")
    parser.add_argument("database")
    args = parser.parse_args()

    nb_total = 0
    nb_bad = 0
    for line_i, line in enumerate(open(args.database, "r").readlines()):
        nb_total += 1
        db_hashcode_str, text = line.strip().rsplit(":", 1)
        real_hashcode = calc_hash(text)
        realhashcode_str = hash2str(real_hashcode)

        min_length, max_length = cheat_length_range(real_hashcode)
        if not min_length <= len(text) <= max_length:
            print(f"{args.database}:{line_i} BUG: length of string is not in range [{min_length},{max_length}]")

        if db_hashcode_str != realhashcode_str:
            print(f"{args.database}:{line_i} '{text}' hashes to {realhashcode_str} (not {db_hashcode_str})", file=sys.stderr)
            nb_bad += 1

    print(f"{nb_total} items were found.")

    if nb_bad:
        print(f"{nb_bad} bad items were found!")
    else:
        print(f"Database OK!")

    return nb_bad


if __name__ == "__main__":
    raise SystemExit(main())
