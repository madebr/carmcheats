#!/usr/bin/env python

from carmcheat.analyze import run_analysis


ALL_CHEATS = (
    ((0xa11ee75d, 0xf805eddd), None, "?", False),
    ((0x564e78b9, 0x99155115), None, "?", False),
    ((0x1f47e5e8, 0xa715222c), "molemode", "?", True),
    ((0x39d4c4c4, 0xf0a2c5b0), "mrcursorscool", "Final lap", True),
    ((0x2654216c, 0xf8256d15), "givemelard", "More money", True),
    ((0x4294ec89, 0xc38ad60e), "spamspamspamspam", "Pedestrians never move", True),
    ((0x2ceb2850, 0xa0c2d27e), "smalludders", "Huge pedestrians", True),
    ((0x2d5f3125, 0x9ce8a541), "superhoops", "Pedestrians explode", True),
    ((0x2169c78b, 0x7f3c9229), "igloofun", "Hot rod mode", True),
    ((0x2203c0cb, 0x79729be4), "funnyjam", "Turbo pedestrians", True),
    ((0x34f4e3ec, 0x868c534d), "spoontreason", "Invincibility", False),
    ((0x34010316, 0x591d1eb2), "spamfritters", "Free repairs", True),
    ((0x214fe3bc, 0x87285111), "inthewar", "Instant repairs", True),
    ((0x2fabc390, 0x0c93d9f7), "sexwithfish", "Toggle timer", True),
    ((0x2902e890, 0x40969f67), "googleplex", "Submarine mode", True),
    ((0x2f458288, 0x058074e2), "milkysmiles", "Time bonus", True),
    ((0x249da152, 0x8f287346), "bigbottom", "Body damage", True),
    ((0x23aae08b, 0xa668103d), "billandben", "Hidden mines", True),
    ((0x32130661, 0x56f03459), "spamaccidents", "Freeze mode", True),
    ((0x2734e944, 0xfe1e4639), "nasalsmear", "Frozen police", True),
    ((0x28341139, 0x355f6d02), "yummylard", "Fast opponents", True),
    ((0x20508831, 0x123d1961), "yakattak", "Faster police", True),
    ((0x346b8bcb, 0x4aba696c), "ihavesomespam", "Odd gravity", True),
    ((0x3fc93df0, 0x29fa9efb), "mooseontheloose", "Pinball mode", True),
    ((0x2a80b09b, 0x058516f5), "secretcows", "No physics", True),
    ((0x2f548fd1, 0x696744da), "chickenfodder", "Rubber mode", True),
    ((0x3cb74f32, 0xb915d88d), "buyournextgame", "Loose suspension", True),
    ((0x297b53ba, 0x218d4d2d), "ilovenobby", "Pedestrians on the map", True),
    ((0x351bc37d, 0xb2a63343), "russformario", "Pedestrians attack", True),
    ((0x2b624386, 0x9ba6260e), "benformario", "Worse grip", True),
    ((0x2ba4ae23, 0xc163a76c), "wehatemario", "More damage", True),
    ((0x2fb92dca, 0x4ad7d54e), "spamforrest", "Instant handbrakes", True),
    ((0x3a42191b, 0xeff70f4c), "soapytitwanks", "Super turbo", True),
    ((0x2aca3190, 0xd9004f25), "hamstersex", "Blind pedestrians", True),
    ((0x37c1f613, 0xb7faf351), "naughtytorty", "Un-dead pedestrians", True),
    ((0x2ba3f603, 0x29f2425c), "icecreamhole", "5 recovery vouchers", True),
    ((0x416eff61, 0x2667df4b), None, "?", False),
    ((0x2554125c, 0x393ca35d), "intheloft", "Drug mode", True),
    ((0x3fff84d5, 0x84a42df4), "boysfromthebush", "Better grip", True),
    ((0x37e83018, 0xb609aee6), "tramsaresuper", "Harvesting pedestrians", True),
    ((0x2db03b19, 0x924a84b7), "islandrules", "Volcano corpse", True),
    ((0x30a19fab, 0x2b0c2782), "rabbitdreamer", "Moon physics", True),
    ((0x2212d981, 0x90e8cf51), "joyrider", "Access to all cars for network play", True),
    ((0x27645433, 0x758f0015), "kevwozear", "Access to all cars and levels", True),
    ((0x33f75455, 0xc10aaaf2), None, "?", False),
)


def main():
    print("Carmageddon 1 cheat table:")
    return run_analysis(ALL_CHEATS)


if __name__ == "__main__":
    raise SystemExit(main())
