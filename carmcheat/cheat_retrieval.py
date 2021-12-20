#!/usr/bin/env python

import argparse
import re
import time
import z3

from carmcheat.algorithm import hash2str, str2hash, cheat_length_guess, cheat_length_range, hash_init, \
    hash_update, hash_final, char2number, number2char


def char_to_val(x):
    return ord(x.lower()) - ord("a") + 22


def z3_hash_step(code1, code2, sum, inp):
    sum += inp
    code1 += (inp << 11)
    code = z3.LShR(code1, 17) + (code1 << 4)
    code2 = z3.LShR(code2, 29) + (code2 << 3) + inp * inp
    return code, code2, sum


def z3_hash_final(code1, code2, sum):
    return z3.LShR(code1, 11) + (sum << 21), code2


def iterate_cribs_recursively(mask, remaining_cribs, keep_order):
    if not remaining_cribs:
        yield mask
        return
    this_crib = remaining_cribs[0]
    other_cribs = remaining_cribs[1:]
    if keep_order:
        try:
            start_pos = next(idx for idx, mv in enumerate(mask) if mv)
        except StopIteration:
            start_pos = 0
    else:
        start_pos = 0
    for pos_i in range(start_pos, len(mask) - len(this_crib) + 1):
        if not any(mask[pos_i:pos_i+len(this_crib)]):
            mask[pos_i:pos_i+len(this_crib)] = [c for c in this_crib]
            yield from iterate_cribs_recursively(mask, other_cribs, keep_order)
            mask[pos_i:pos_i+len(this_crib)] = [None for _ in this_crib]


def iterate_cribs(cribs, length, keep_order):
    mask_result = [None] * length
    return iterate_cribs_recursively(mask_result, cribs, keep_order)


def run(target_hash, length, crib_iterator, database, vowel_frequency=None,
        database_filename=None, check_intermediates=True, force=False):
    min_length, max_length = cheat_length_range(target_hash)
    VOWELS = ["a", "e", "i", "o", "y"]
    for crib_mask in crib_iterator:
        print(f"Trying crib mask '{''.join(c if c else '_' for c in crib_mask)}'")
        s = z3.Solver()

        # Create Z3 keycode objects
        # FIXME: Their range is [22, 22+26]=[22,48], will reducing their bit width to 6 make the algorithm faster?
        keycodes = [z3.BitVec(f"k_{i}", 32) for i in range(length)]

        # All characters are 22 + [a-z]
        for k in keycodes:
            s.add(k >= 22)
            s.add(k < 22 + 26)

        if vowel_frequency is not None:
            vowel_tests = []
            for group_start_i in range(length - vowel_frequency + 1):
                vowel_tests.append(z3.Or(*[keycodes[group_start_i + off] == char2number(vowel)
                                           for vowel in VOWELS for off in range(vowel_frequency)]))
            s.add(z3.And(vowel_tests))

        # Apply the "crib" to the input characters
        for k, c in zip(keycodes, crib_mask):
            if c:
                s.add(k == char2number(c))

        # Exclude all items from the database
        for dbitem in database:
            s.add(z3.Or(*[kc != char2number(dbi_char) for dbi_char, kc in zip(dbitem, keycodes)]))

        # Store all intermediate hash results in this list
        intermediates = []

        # Apply the Carmageddon hashing algorithm to the keycodes
        code1 = code2 = sum = z3.BitVecVal(0, 32)
        for k_i, k in enumerate(keycodes):
            if check_intermediates and (force or min_length <= k_i <= max_length):
                # Calculate the final hash for each intermediate key code ==> string is shorter
                final = z3_hash_final(code1, code2, sum)
                intermediates.append(final)
            # One step of the hash
            code1, code2, sum = z3_hash_step(code1, code2, sum, k)

        # Create the final hash, which should be added to the intermediates list anyways
        final = z3_hash_final(code1, code2, sum)
        intermediates.append(final)

        # Generate a success when an intermediate hash matches the target hash
        s.add(z3.Or(*[z3.And(intermediate[0] == target_hash[0], intermediate[1] == target_hash[1]) for intermediate in intermediates]))

        while (t := s.check()) == z3.sat:
            full_cleartext = "".join(number2char(s.model()[k].as_long()) for k in keycodes)
            if check_intermediates:
                state = hash_init()
                for c_i, char in enumerate(full_cleartext):
                    final = hash_final(*state)
                    if final == target_hash:
                        cleartext = full_cleartext[:c_i]
                        excluded_keycodes = [k for k in keycodes[:c_i]]
                        break
                    state = hash_update(*state, char)
                else:
                    cleartext = full_cleartext
                    excluded_keycodes = keycodes
            else:
                cleartext = full_cleartext
                excluded_keycodes = keycodes
            database.append(cleartext)
            s.add(z3.Or(*[k != s.model()[k].as_long() for k in excluded_keycodes]))
            print(f"{hash2str(target_hash)}:{cleartext}")
            if database_filename:
                with open(database_filename, "a") as fn:
                    fn.write(f"{hash2str(target_hash)}:{cleartext}\n")
        if t == z3.unknown:
            return 1
    return 0


def main():
    parser = argparse.ArgumentParser(allow_abbrev=False,
                                     description="Use SAT solver to find cheat codes hashing to a target")
    parser.add_argument("target", help="Target hash (format=XXXXXXXX:XXXXXXXX), where X is hexadecimal")
    parser.add_argument("length", type=int,
                        help="Length(s) of cheat code to check/find. Or maximum length when checking intermediates.")
    parser.add_argument("--cribs", default=None,
                        help="Find only cheat codes that contain all the 'cribs'. Use ',' as a separator.")
    parser.add_argument("--crib-order", dest="criborder", default="keep", choices=["keep", "dontcare"],
                        help="Allowed order of the 'cribs'.")
    parser.add_argument("--vowels", action="store_true", help="Require frequent occurrence of a vowel")
    parser.add_argument("--database", metavar="DB", help="Append found cheat codes to this database")
    parser.add_argument("--intermediates", action="store_true", help="Match intermediates")
    parser.add_argument("--force", action="store_true", help="Force search")
    parser.add_argument("--seed", nargs=argparse.OPTIONAL, const="time", help="Initial z3 seed")
    args = parser.parse_args()

    hash_target_str = args.target.strip()

    try:
        target_hash = str2hash(hash_target_str)
    except ValueError:
        parser.error("Invalid target. It needs to be in the XXXXXXXX:XXXXXXXX format.")

    if args.seed:
        if args.seed == "time":
            z3_seed = int(time.time())
        else:
            try:
                z3_seed = int(args.seed)
            except ValueError:
                parser.error("Seed value must be a decimal integer")
        z3.set_param("smt.random_seed", z3_seed)

    database = []
    if args.database:
        try:
            for line in open(args.database, "r").readlines():
                hash_str, cleartext = line.strip().rsplit(":", 1)
                if hash_str == hash_target_str:
                    database.append(cleartext)
        except FileNotFoundError:
            pass
        print(f"Found {len(database)} entries in the database.")

    print(f"Looking for cheat codes hashing to {hash_target_str}. Maximum length: {args.length}")
    cheat_min_length, cheat_max_length = cheat_length_range(target_hash)
    print(f"Heuristics: length range=[{cheat_min_length}, {cheat_max_length}] length={cheat_length_guess(target_hash)}")

    cribs = re.split("[:,;]", args.cribs) if args.cribs else []
    if cribs:
        length_range_cribs = cheat_length_range(target_hash, cribs)
        if length_range_cribs != (cheat_min_length, cheat_max_length):
            cheat_min_length, cheat_max_length = length_range_cribs
            print(f"Heuristics: cribs narrowed the length range=[{cheat_min_length}, {cheat_max_length}]")
        crib_nbletters = sum(len(crib) for crib in cribs)
        if crib_nbletters >= args.length:
            parser.error("The crib is too long")
        matched_dbitems = [dbitem for dbitem in database if all(crib in dbitem for crib in cribs)]
        print(f"{len(matched_dbitems)} database entries match the crib.")
    crib_iterator = iterate_cribs(cribs, args.length, args.criborder == "keep")

    if not args.force:
        if not args.intermediates and not cheat_min_length <= args.length <= cheat_max_length:
            print(f"Length={args.length} is out of range [{cheat_min_length},{cheat_max_length}] => skipping search (use --force to override)")
            return

    time_start = time.time()
    try:
        result = run(target_hash, args.length, crib_iterator, database,
                     vowel_frequency=4 if args.vowels else None,
                     database_filename=args.database, check_intermediates=args.intermediates, force=args.force)
    except KeyboardInterrupt:
        result = 1
    time_finish = time.time()
    time_delta = time_finish - time_start

    if result == 0:
        print(f"Search finished ({time_delta:.1f}s)")
    else:
        print(f"Search aborted ({time_delta:.1f}s)")
    return result


if __name__ == "__main__":
    raise SystemExit(main())
