import argparse
import sys

from carmcheat.algorithm import calc_hash, hash2str, cheat_length_guess, cheat_length_range


def run_analysis(all_cheats):
    parser = argparse.ArgumentParser(description="Print a list of all known cheat codes with hash and its action")
    parser.add_argument("--display", choices=["action", "hashstats", "wordstats"], default="action",
                        help="What information to print for each cheat code")

    args = parser.parse_args()

    for i, (code, cheat, action, final) in enumerate(all_cheats):
        if cheat:
            calc_code = calc_hash(cheat)
            if calc_code != code:
                print(f"WARNING! cheat invalid: expected {hash2str(code)}, got {hash2str(calc_code)}", file=sys.stderr)
        if args.display == "action":
            display_data = f"{action if action else ''}"
        elif args.display == "hashstats":
            min_pw, max_pw = cheat_length_range(code)
            guess_len = cheat_length_guess(code)
            if final:
                factor = (len(cheat) - min_pw) / (max_pw - min_pw)
                len_str = f"{len(cheat):<2}"
                factor_str = f"{factor*100:3.1f}%"
            else:
                len_str = f"?"
                factor_str = f"?"
            guess_factor = (guess_len - min_pw) / (max_pw - min_pw)
            guess_factor_str = f"{guess_factor*100:3.1f}%"
            display_data = f"len={len_str:2s} guess_len={guess_len:<2} min_pw={min_pw:<2} max_pw={max_pw:<2} f={factor_str:5s} gf={guess_factor_str:5s}"
        elif args.display == "wordstats":
            VOWELS = ["a", "e", "i", "o", "u", "y"]
            if final:
                previous_type = None
                cons_count = {
                    "vowel": 0,
                    "cons": 0,
                }
                current_count = 0
                for char in cheat:
                    current_type = "vowel" if char in VOWELS else "cons"
                    if current_type == previous_type:
                        current_count += 1
                    else:
                        current_count = 1
                    if cons_count[current_type] < current_count:
                        cons_count[current_type] = current_count
                    previous_type = current_type
                display_data = f"vowel={cons_count['vowel']:1} conson={cons_count['cons']:1}"
            else:
                display_data = "n/a"

        print(f"{i:>2}: {hash2str(code)} {cheat if cheat else '':<35} {display_data}")
    return 0
