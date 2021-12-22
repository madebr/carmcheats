#!/usr/bin/env python

import argparse
import bisect
import itertools
import math
import pathlib
import time
import typing

from carmcheat.algorithm import char2number, str2hash, hash2keycodeSum


DATA_DIR = pathlib.Path(__file__).resolve().parent / "data"


# # FIXME: use `bisect.bisect_right` if python version >= 3.10
# def bisect_right(a, x, lo=0, hi=None, *, key=None):
#     """Return the index where to insert item x in list a, assuming a is sorted.
#     The return value i is such that all e in a[:i] have e <= x, and all e in
#     a[i:] have e > x.  So if x already appears in the list, a.insert(i, x) will
#     insert just after the rightmost x already there.
#     Optional args lo (default 0) and hi (default len(a)) bound the
#     slice of a to be searched.
#     """
#
#     if lo < 0:
#         raise ValueError('lo must be non-negative')
#     if hi is None:
#         hi = len(a)
#     # Note, the comparison uses "<" to match the
#     # __lt__() logic in list.sort() and in heapq.
#     if key is None:
#         while lo < hi:
#             mid = (lo + hi) // 2
#             if x < a[mid]:
#                 hi = mid
#             else:
#                 lo = mid + 1
#     else:
#         while lo < hi:
#             mid = (lo + hi) // 2
#             if x < key(a[mid]):
#                 hi = mid
#             else:
#                 lo = mid + 1
#     return lo


def find_index_le(a, x):
    'Find rightmost value less than or equal to x'
    i = bisect.bisect_right(a, x)
    if i:
        return i-1
    raise ValueError


def calculate_keycode_sum(word: str) -> int:
    return sum(char2number(c) for c in word)


class WordList:
    def __init__(self, words: typing.List[str]):
        self.words = words
        self.words.sort(key=calculate_keycode_sum)
        self.keyCodeSums = [calculate_keycode_sum(word) for word in self.words]

    def lookupRange(self, value: int) -> typing.Tuple[int, int]:
        try:
            upper_index = find_index_le(self.keyCodeSums, value)
            return (0, upper_index + 1)
        except:
            return (0, 0)


def read_datafile(path: pathlib.Path) -> typing.List[str]:
    return [line.strip() for line in path.open().readlines() if not line.startswith("#")]


def read_wordlist(path: pathlib.Path) -> WordList:
    return WordList(read_datafile(path))


def print_matching_words_recurse(wordLists: typing.List[WordList], keyCodeSumRemaining: int, parts: typing.List[typing.Optional[str]], index: int):
    if index >= len(wordLists):
        return iter(())
    if keyCodeSumRemaining < 20:
        return iter(())
    wordlist = wordLists[index]
    minIndex, maxIndex = wordlist.lookupRange(keyCodeSumRemaining)
    for w_i in range(minIndex, maxIndex):
        word = wordlist.words[w_i]
        wordKeyCodeSum = wordlist.keyCodeSums[w_i]
        parts[index] = word
        if keyCodeSumRemaining == wordKeyCodeSum:
            print("".join(parts[:index+1]))
        elif keyCodeSumRemaining > wordKeyCodeSum:
            print_matching_words_recurse(wordLists, keyCodeSumRemaining - wordKeyCodeSum, parts, index + 1)


def print_matching_words(wordlists: typing.List[WordList], keyCodeSum: int):
    print_matching_words_recurse(wordlists, keyCodeSum, [None] * len(wordlists), 0)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--stats", action="store_true", help="Print statistics")
    parser.add_argument("hash", nargs="?", help="Target hash")
    args = parser.parse_args()

    sentence_structures = read_datafile(DATA_DIR / "sentence_structures.txt")

    subjects = read_wordlist(DATA_DIR / "subjects.txt")
    adjectives = read_wordlist(DATA_DIR / "adjectives.txt")
    articles_prepositions = read_wordlist(DATA_DIR / "articles_prepositions.txt")
    nouns = read_wordlist(DATA_DIR / "nouns.txt")
    verbs_regular = read_wordlist(DATA_DIR / "verbs_regular.txt")

    markers = {
        "s": subjects,
        "a": adjectives,
        "r": articles_prepositions,
        "n": nouns,
        "v": verbs_regular,
    }

    running_nb = 0

    for sentence_structure in sentence_structures:
        time_start_sentence_structure = time.time()
        selection_data = [markers[c] for c in sentence_structure]
        nb = math.prod([len(wl.words) for wl in selection_data])

        running_nb += nb

        if args.stats:
            print(f"sentence structure: {sentence_structure} -> {nb} items")
        else:
            if args.hash:
                hash = str2hash(args.hash)
                keyCodeSum = hash2keycodeSum(hash)
                print_matching_words(selection_data, keyCodeSum)
            else:
                for combo in itertools.product(*[wl.words for wl in selection_data]):
                    print("".join(combo))

        time_end_sentence_structure = time.time()
        with open("progress.txt", "a") as fn:
            print(f"{sentence_structure},{time_end_sentence_structure-time_start_sentence_structure:2.1f}", file=fn)


    if args.stats:
        print(f"Total: {running_nb}")


if __name__ == "__main__":
    raise SystemExit(main())
