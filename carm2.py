#!/usr/bin/env python
import argparse
import sys

from carmcheat.algorithm import calc_hash, hash2str, cheat_length_range


ALL_CHEATS = (
    ((0xa11ee75d, 0xf805eddd), "sblqhpsyngswyrzzynbdcpppjnwvzyedtvj", "Edit mode (also for multiplayer)", False),
    ((0x398da28c, 0x44339dd4), "lapmylovepump", "Edit mode", True),
    ((0x7dc510f3, 0x65c61537), "iwishicouldflyrightuptothesky", "Flight mode", True),
    ((0x309e4f55, 0xecc7daaf), "smartbastard", "Finish race", True),
    ((0x1bcbe148, 0x040161b1), "wetwet", "Credit bonus", True),
    ((0x1d5e7725, 0x0ed62a70), "gluglug", "Mega bonus", True),
    ((0x22c65063, 0xe4331bc8), "stickits", "Pedestrians are stuck", True),
    ((0x1a37d28a, 0x139787e4), "megabum", "Giant pedestrians", True),
    ((0x1dcba360, 0x1e38bfa1), "twatoff", "Explosive pedestrians", True),
    ((0x24c99afb, 0xd908f952), "clintonco", "Hot rod", True),
    ((0x200c1bd4, 0x663de391), "fastbast", "Fast pedestrians", True),
    ((0x252a2e6b, 0x3304d647), "supacocks", "Invincibility", True),
    ((0x218f555c, 0xe2d3ac58), "tingting", "Free repairs", True),
    ((0x1fc7655b, 0xa12f9258), "mingming", "Instant Repairs", True),
    ((0x2b2e6891, 0x4bd611c2), "stopsnatch", "Toggle timer", True),
    ((0x2db8b34a, 0x4418ac58), "watersport", "Underwater capability", True),
    ((0x3001467e, 0xb323f944), "timmytitty", "Time bonus", True),
    ((0x23968eda, 0x9259246e), "clangclang", "Trashed bodywork", True),
    ((0x1f3baa55, 0x56c505a9), "bluebalz", "Frozen opponents", True),
    ((0x214a2558, 0x56cbf421), "bluepigz", "Frozen police", True),
    ((0x373ae69a, 0xef8c998f), "swiftyshifty", "Turbo opponents", True),
    ((0x327ebd75, 0x605a9e3e), "pigsmightfly", "Turbo police", True),
    ((0x350c0384, 0x73e576d2), "mooningminnie", "lunar gravity", True),
    ((0x17f03c24, 0x0071650c), "tilty", "Pinball mode", True),
    ((0x32aeca21, 0x689d3168), "stickytyres", "Wall climbing", True),
    ((0x191841aa, 0x10fbd770), "jigajig", "Bouncy mode", True),
    ((0x26026896, 0x630e5fa9), "mrwobbley", "Jelly suspension", True),
    ((0x2440ca1b, 0x2e68304c), "dotaction", "Pedestrians on map", True),
    ((0x37a11b1b, 0x6820b87d), "fryingtonight", "Pedestrian electric ray", True),
    ((0x2f2ea509, 0x6bb804b7), "wotatwatami", "Slippery tires", True),
    ((0x28f522f1, 0x2f52f8c0), "stuffitup", "Damage magnifier", True),
    ((0x26c15553, 0xba19a354), "eyepopper", "Instant handbrake", True),
    ((0x3964b52b, 0x40c94648), "angelmolesters", "Immortal pedestrians", True),
    ((0x18bf123a, 0x0080c0a9), "whizz", "Turbo", True),
    ((0x2a439e13, 0x3356c0b0), "supawhizz", "Mega-turbo", True),
    ((0x28769902, 0x50a5d8d1), "lemmingize", "Disable pedestrian AI", True),
    ((0x2d5aa4e5, 0x427f9d82), "takemetakeme", "Suicidal pedestrians", True),
    ((0x1e73b354, 0x17741619), "pillpop", "Five Recovery Vouchers", True),
    ((0x1cac0a7c, 0x0a461bb1), "bigtwat", "Solid granite car", True),
    ((0x1e3c613a, 0x6b56e92c), "duffride", "Rock springs", True),
    ((0x2f4c3519, 0x082321f8), "bloodyhippy", "Drug mode", True),
    ((0x21f0d261, 0xdae090b9), "rubberup", "Gripomatic tires", True),
    ((0x1c727344, 0x78f65c91), "goodhead", "Pedestrians have stupid heads", True),
    ((0x2f574845, 0x75ff1428), "stiffspasms", "Mutant corpses", True),
    ((0x1f0601e3, 0x9455c4c8), "ledsleds", "Jupiter gravity", True),
    ((0x26219ff3, 0xfdfd8b46), "easypeasy", "Slow motion pedestrians", True),
    ((0x26afbb31, 0xe3275e40), "tinytoss", "Mini-pedestrians", True),
    ((0x25205546, 0xcf86a14c), "furkinell", "Turbo Bastard Nutter Nitros", True),
    ((0x1a0a8e5b, 0x02035340), "hotass", "After burner", True),
    ((0x1bdea925, 0x5d98fd0c), "didedodi", "Lay mines", True),
    ((0x2d4dd2a9, 0xf01ba696), "liquidlunge", "Oil slicks", True),
    ((0x2e7a7505, 0x8920e4f6), "skippypoos", "Kangaroo on command", True),
    ((0x17290940, 0x00901801), "zazaz", "Pedestrian annihilator", True),
    ((0x1d4e7a9c, 0x030e2650), "powpow", "Repulse opponents", True),
    ((0x3579d64a, 0x3d2e34c3), "oohmessymess", "Dismemberfest", True),
    ((0x28f4d49c, 0xb3418148), "xrayspeks", "Ethereal pedestrians", True),
    ((0x1d6ba9c3, 0x0e017749), "getdown", "Grooving pedestrians", True),
    ((0x310971ab, 0xcb973702), "mrmainwaring", "Panicked pedestrians", True),
    ((0x28451eeb, 0x30ff63cb), "fartsuits", "Helium pedestrians", True),
    ((0x1ebfa5ba, 0x92e034ec), "largeone", "Angry pedestrians", True),
    ((0x27079773, 0xd1ef511c), "hippotart", "Fat pedestrians", True),
    ((0x388de72c, 0x047a8dca), "bloodyartists", "Stick insects", True),
    ((0x1a0da9fc, 0x0180e010), "cowcow", "Pedestrian repulsificator", True),
    ((0x2975a10c, 0xefd65f5d), "osostrong", "Extra armor", True),
    ((0x1e5cc6ca, 0x17b76391), "osofast", "Extra power", True),
    ((0x250c6f99, 0xbdda24cc), "osonasty", "Extra offensive", True),
    ((0x33950e49, 0x2890738c), "osoversatile", "Extra everything", True),
    ((0x4e5f487a, 0x3dc635b8), "osostrongsostrong", "Double extra armor", True),
    ((0x3815584c, 0x91bbc26e), "osofastsofast", "Double extra power", True),
    ((0x459732b2, 0xb571e010), "osonastysonasty", "Double extra offensive", True),
    ((0x62871003, 0x79b15084), "osoversatilesoversatile", "Double extra everything", True),
    ((0x2d72ebb4, 0x5fd4d3ca), "stringvest", "Maximum armour", True),
    ((0x2c3be2aa, 0x90e0eb9c), "vastnesses", "Maximum power", True),
    ((0x2b2be28b, 0x30e0eb7b), "fistnesses", "Maximum offensive", True),
    ((0x29be089d, 0x635ceb96), "skegnesses", "Maximum everything", True),
    ((0x4897982d, 0x06c4fa99), "thatsalotofarmour", "Extra armor slot", True),
    ((0x44d50f49, 0x010edb42), "thatsalotofpower", "Extra power slot", True),
    ((0x403afae5, 0x0104a7d2), "thatsalotofoffal", "Extra offensive slot", True),
    ((0x45c19e5e, 0x011b2cf9), "thatsalotofslots", "Extra slots all around", True),
    ((0x2f790ebd, 0x2fd87f6b), "strongbones", "Bonus armor slots", True),
    ((0x244f60c9, 0x31f4fda3), "fastbones", "Bonus power slots", True),
    ((0x2b0794d3, 0x12927dc9), "nastybones", "Bonus offensive slots", True),
    ((0x2a44b628, 0x0c3e7edb), "loadsabones", "Bonus slots all around", True),
    ((0x2998e46d, 0x1360a63e), "randypandy", "Random APO", True),
    ((0x23248728, 0xc84d9d51), "randypot", "Random APO potential", True),
    ((0x289c1822, 0x136e9fc3), "randyquaid", "Random good APO", True),
    ((0x35abb7d0, 0xa08da57c), "eveningoccifer", "Drunk driving", True),
    ((0x1c1fdd92, 0x01dd060c), "fryfry", "Pedestrian flamethrower", True),
    ((0x253069c1, 0x4972796a), "ineedapill", "Pedestrian valium", True),
    ((0x33ca4873, 0x3b005b24), "oypowerupno", "No power-ups", True),
    ((0x1f56cde5, 0x8f213aae), "bigdangle", "Mutant tail", True),
    ((0x1784995b, 0x0163c389), "bonbon", "Slaughter mortar", True),
    ((0x3003eccb, 0x1d74f36f), "gotoinfrared", "Cloaking device", True),
    ((0x4b054b60, 0x6b6736cb), "ezpzkballxxewazon", "Steel Gonad O’ Death", False),
    ((0x616fb8e4, 0x7c6100a8), "mwucuzysfuyhtqwxepvu", "All cars + races (from main menu)", False),
)


def main():
    parser = argparse.ArgumentParser(description="Print a list of all known cheat codes with hash and its action")
    parser.add_argument("--display", choices=["action", "hashstats"], default="action",
                        help="What information to print for each cheat code")

    args = parser.parse_args()

    for i, (code, cheat, action, final) in enumerate(ALL_CHEATS):
        if cheat:
            calc_code = calc_hash(cheat)
            if calc_code != code:
                print(f"WARNING! cheat invalid: expected {hash2str(code)}, got {hash2str(calc_code)}", file=sys.stderr)
        if args.display == "action":
            display_data = f"{action if action else ''}"
        elif args.display == "hashstats":
            min_pw, max_pw = cheat_length_range(code)
            factor = (len(cheat) - min_pw) / (max_pw - min_pw)
            if final:
                len_str = f"{len(cheat):<2}"
                factor_str = f"{factor*100:.1f}"
            else:
                len_str = f"? "
                factor_str = f"??.?"
            display_data = f"len={len_str} min_pw={min_pw:<2} max_pw={max_pw:<2} factor={factor_str}"

        print(f"{i:>2}: {hash2str(code)} {cheat if cheat else '':<35} {display_data}")


if __name__ == "__main__":
    raise SystemExit(main())
