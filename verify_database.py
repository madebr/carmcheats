#!/usr/bin/env python

import argparse
import algorithm
import sys


def main():
    parser = argparse.ArgumentParser(description="Verify a database")
    parser.add_argument("database")
    args = parser.parse_args()

    nb_total = 0
    nb_bad = 0
    for line_i, line in enumerate(open(args.database, "r").readlines()):
        nb_total += 1
        db_hashcode, text = line.strip().rsplit(":", 1)
        realhashcode = algorithm.hash2str(algorithm.calc_hash(text))
        if db_hashcode != realhashcode:
            print(f"{args.database}:{line_i} '{text}' hashes to {realhashcode} (not {db_hashcode})", file=sys.stderr)
            nb_bad += 1

    print(f"{nb_total} items were found.")

    if nb_bad:
        print(f"{nb_bad} bad items were found!")
    else:
        print(f"Database OK!")

    return nb_bad


if __name__ == "__main__":
    raise SystemExit(main())
