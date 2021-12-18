#!/usr/bin/env python

import argparse
import itertools
import math
import pathlib
import typing


DATA_DIR = pathlib.Path(__file__).resolve().parent / "data"


def read_datafile(path: pathlib.Path) -> typing.List[str]:
    return [line.strip() for line in path.open().readlines() if not line.startswith("#")]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--stats", action="store_true", help="Print statistics")
    args = parser.parse_args()

    sentence_structures = read_datafile(DATA_DIR / "sentence_structures.txt")

    subjects = read_datafile(DATA_DIR / "subjects.txt")
    adjectives = read_datafile(DATA_DIR / "adjectives.txt")
    articles_prepositions = read_datafile(DATA_DIR / "articles_prepositions.txt")
    nouns = read_datafile(DATA_DIR / "nouns.txt")
    verbs_regular = read_datafile(DATA_DIR / "verbs_regular.txt")

    markers = {
        "s": subjects,
        "a": adjectives,
        "r": articles_prepositions,
        "n": nouns,
        "v": verbs_regular,
    }

    running_nb = 0

    for sentence_structure in sentence_structures:
        selection_data = [markers[c] for c in sentence_structure]
        nb = math.prod([len(s) for s in selection_data])

        running_nb += nb

        if args.stats:
            print(f"sentence structure: {sentence_structure} -> {nb} items")
        else:
            for combo in itertools.product(*selection_data):
                print("".join(combo))

    if args.stats:
        print(f"Total: {running_nb}")


if __name__ == "__main__":
    raise SystemExit(main())
