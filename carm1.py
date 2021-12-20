#!/usr/bin/env python

from carmcheat.analyze import run_analysis


ALL_CHEATS = (
    ((0xa11ee75d, 0xf805eddd), None, "?", False),
    ((0x564e78b9, 0x99155115), "ibetyoucantprintcunt", "Edit Mode", True),
    ((0x1f47e5e8, 0xa715222c), "molemode", "Flight Mode", True),
    ((0x39d4c4c4, 0xf0a2c5b0), "mrcursorscool", "Final lap", True),
    ((0x2654216c, 0xf8256d15), "givemelard", "More Money", True),
    ((0x4294ec89, 0xc38ad60e), "spamspamspamspam", "Pedestrians With Greased Shoes", True),
    ((0x2ceb2850, 0xa0c2d27e), "smalludders", "Giant Pedestrians", True),
    ((0x2d5f3125, 0x9ce8a541), "superhoops", "Explosive Pedestrians", True),
    ((0x2169c78b, 0x7f3c9229), "igloofun", "Hot Rod", True),
    ((0x2203c0cb, 0x79729be4), "funnyjam", "Turbo Pedestrians", True),
    ((0x34f4e3ec, 0x868c534d), "spoontreason", "Invulnerability", False),
    ((0x34010316, 0x591d1eb2), "spamfritters", "Free Repairs", True),
    ((0x214fe3bc, 0x87285111), "inthewar", "Instant Repair", True),
    ((0x2fabc390, 0x0c93d9f7), "sexwithfish", "Timer Frozen", True),
    ((0x2902e890, 0x40969f67), "googleplex", "Underwater Ability", True),
    ((0x2f458288, 0x058074e2), "milkysmiles", "Time Bonus", True),
    ((0x249da152, 0x8f287346), "bigbottom", "Oh Dear, Bodywork Trashed!", True),
    ((0x23aae08b, 0xa668103d), "billandben", "Hidden mines", True),
    ((0x32130661, 0x56f03459), "spamaccidents", "Frozen Opponents", True),
    ((0x2734e944, 0xfe1e4639), "nasalsmear", "Frozen Cops", True),
    ((0x28341139, 0x355f6d02), "yummylard", "Turbo Opponents", True),
    ((0x20508831, 0x123d1961), "yakattak", "Turbo Cops", True),
    ((0x346b8bcb, 0x4aba696c), "ihavesomespam", "Lunar Gravity", True),
    ((0x3fc93df0, 0x29fa9efb), "mooseontheloose", "Pinball Mode", True),
    ((0x2a80b09b, 0x058516f5), "secretcows", "Wall Climber", True),
    ((0x2f548fd1, 0x696744da), "chickenfodder", "Bouncy Bouncy", True),
    ((0x3cb74f32, 0xb915d88d), "buyournextgame", "Jelly Suspension", True),
    ((0x297b53ba, 0x218d4d2d), "ilovenobby", "Pedestrians Shown on Map", True),
    ((0x351bc37d, 0xb2a63343), "russformario", "Pedestrian Electro-bastard Ray", True),
    ((0x2b624386, 0x9ba6260e), "benformario", "Greased Tyres", True),
    ((0x2ba4ae23, 0xc163a76c), "wehatemario", "Acme Damage Magnifier", True),
    ((0x2fb92dca, 0x4ad7d54e), "spamforrest", "Instant Handbrakes", True),
    ((0x3a42191b, 0xeff70f4c), "soapytitwanks", "Mega-turbo", True),
    ((0x2aca3190, 0xd9004f25), "hamstersex", "Stupid Pedestrians", True),
    ((0x37c1f613, 0xb7faf351), "naughtytorty", "Pedestrian Respawn", True),
    ((0x2ba3f603, 0x29f2425c), "icecreamhole", "Free Recovery Vouchers", True),
    ((0x416eff61, 0x2667df4b), "kneepithappiness", "Solid Granite Car", True),
    ((0x2554125c, 0x393ca35d), "intheloft", "Drugs", True),
    ((0x3fff84d5, 0x84a42df4), "boysfromthebush", "Grip-o-matic Tyres", True),
    ((0x37e83018, 0xb609aee6), "tramsaresuper", "Pedestrian Harvest", True),
    ((0x2db03b19, 0x924a84b7), "islandrules", "Vesuvian Corpses", True),
    ((0x30a19fab, 0x2b0c2782), "rabbitdreamer", "Gravity From Jupiter", True),
    ((0x2212d981, 0x90e8cf51), "joyrider", "Access to all cars for network play", True),
    ((0x27645433, 0x758f0015), "kevwozear", "Access to all cars and levels", True),
    ((0x33f75455, 0xc10aaaf2), "iwanttofiddle", "Decrypt game data files", True),
)


def main():
    print("Carmageddon 1 cheat table:")
    return run_analysis(ALL_CHEATS)


if __name__ == "__main__":
    raise SystemExit(main())
