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
    with open(args.database, "r") as file:
        original_lines = [line.strip() for line in file.readlines() if line.strip()]

    sorted_lines = sorted(set(original_lines), key=DbLine)

    # Then open the target database
    if args.write:
        dest = args.write if isinstance(args.write, str) else args.database
        print(f"{len(sorted_lines)} entries, {len(original_lines) - len(sorted_lines)} items pruned.")
        print(f"Writing db to {dest}...")
        dest_file = open(dest, "w")
    else:
        dest_file = sys.stdout

    # Finally, write all entries to the target database
    for line in sorted_lines:
        print(line, file=dest_file)

    dest_file.close()

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
