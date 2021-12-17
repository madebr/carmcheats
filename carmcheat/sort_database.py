#!/usr/bin/env
import argparse
import sys


class DbLine:
    def __init__(self, line: str):
        self.hash, self.cheatcode = line.rsplit(":", 1)

    def __lt__(self, other: "DbLine"):
        if self.hash == other.hash:
            if len(self.cheatcode) == len(other.cheatcode):
                return self.cheatcode < other.cheatcode
            else:
                return len(self.cheatcode) < len(other.cheatcode)
        else:
            return self.hash < other.hash


def main():
    parser = argparse.ArgumentParser(description="Sort a database + remove duplicates", allow_abbrev=False)
    parser.add_argument("database", help="database file to sort")
    parser.add_argument("--write", nargs="?", default=None, const=True, metavar="DB", help="database to write")
    args = parser.parse_args()

    # Read all entries from the source database, and close it
    lines = sorted(set(line.strip() for line in open(args.database, "r").readlines() if line.strip()), key=DbLine)

    # Then open the target database
    if args.write:
        dest = args.write if isinstance(args.write, str) else args.database
        print(f"Writing db to {dest} ({len(lines)} entries)")
        dest_file = open(dest, "w")
    else:
        dest_file = sys.stdout

    # Finally, write all entries to the target database
    for line in lines:
        print(line, file=dest_file)


if __name__ == "__main__":
    raise SystemExit(main())
