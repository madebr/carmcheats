#!/usr/bin/env python

import argparse
import bisect
import itertools
import math
import pathlib
import sys
import threading
import time
import typing

from carmcheat.algorithm import char2number, str2hash, hash2keycodeSum


DATA_DIR = pathlib.Path(__file__).resolve().parent / "data"


def find_index_le(a, x):
    'Find rightmost value less than or equal to x'
    i = bisect.bisect_right(a, x)
    if i:
        return i-1
    raise ValueError


def find_index_eq(a, x):
    'Locate the leftmost value exactly equal to x'
    i = bisect.bisect_left(a, x)
    if i != len(a) and a[i] == x:
        return i
    raise ValueError


def find_index_gt(a, x):
    'Find leftmost value greater than x'
    i = bisect.bisect_right(a, x)
    if i != len(a):
        return i
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


class DictionaryGeneratorState:
    def __init__(self, wordLists: typing.List[WordList]):
        self.wordLists = wordLists
        self.parts: typing.List[typing.Optional[str]] = [None] * len(wordLists)


class StateWatcher:
    def __init__(self, interval: int=2):
        self.state: typing.Optional[DictionaryGeneratorState] = None
        self.structure: typing.Optional[str] = None
        self.timer = None
        self.interval = interval

    def set_state(self, state:DictionaryGeneratorState):
        self.state = state

    def set_structure(self, structure: str):
        self.structure = structure

    def start(self):
        self.timer = threading.Timer(interval=self.interval, function=self._run_retrigger)
        self.timer.start()

    def _run_retrigger(self):
        if self.state:
            print(f"structure={self.structure} parts:{self.state.parts}", file=sys.stderr)
        self.timer = threading.Timer(interval=self.interval, function=self._run_retrigger)
        self.timer.start()

    def stop(self):
        if self.timer:
            self.timer.cancel()


def print_matching_words_recurse(state: DictionaryGeneratorState, keyCodeSumRemaining: int, index: int):
    if index >= len(state.wordLists):
        return
    if keyCodeSumRemaining < 20:
        return
    wordList = state.wordLists[index]
    if index == len(state.wordLists) - 1:
        try:
            minIndex = find_index_eq(wordList.keyCodeSums, keyCodeSumRemaining)
        except ValueError:
            return
        try:
            maxIndex = find_index_gt(wordList.keyCodeSums, keyCodeSumRemaining)
        except ValueError:
            maxIndex = len(wordList.keyCodeSums)
    else:
        minIndex, maxIndex = wordList.lookupRange(keyCodeSumRemaining)
    parts = state.parts
    for w_i in range(minIndex, maxIndex):
        word = wordList.words[w_i]
        wordKeyCodeSum = wordList.keyCodeSums[w_i]
        parts[index] = word
        if keyCodeSumRemaining == wordKeyCodeSum:
            print("".join(parts[:index+1]))
        elif keyCodeSumRemaining > wordKeyCodeSum:
            print_matching_words_recurse(state, keyCodeSumRemaining - wordKeyCodeSum, index + 1)


def print_matching_words(state: DictionaryGeneratorState, keyCodeSum: int):
    print_matching_words_recurse(state, keyCodeSum, 0)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--stats", action="store_true", help="Print statistics")
    parser.add_argument("--no-status", action="store_false", dest="status", help="Don't print status reports to stderr")
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

    watcher = StateWatcher()
    if args.status:
        watcher.start()
    try:

        for sentence_structure in sentence_structures:
            watcher.set_structure(sentence_structure)
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
                    state = DictionaryGeneratorState(selection_data)
                    watcher.set_state(state)
                    print_matching_words(state, keyCodeSum)
                else:
                    for combo in itertools.product(*[wl.words for wl in selection_data]):
                        print("".join(combo))

            time_end_sentence_structure = time.time()
            with open("progress.txt", "a") as fn:
                print(f"{sentence_structure},{time_end_sentence_structure-time_start_sentence_structure:2.1f}", file=fn)

        if args.stats:
            print(f"Total: {running_nb}")
    finally:
        watcher.stop()


if __name__ == "__main__":
    raise SystemExit(main())
