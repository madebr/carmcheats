# Finding cheatcodes for Carmageddon 1/2

The scripts in this repo can be used to decipher cheat codes of carmageddon.

## List all known cheat codes

Run:
```
python carm2.py
```

## Calculate the hash of cheat codes

```cmd
$ python -m carmcheat.algorithm -h
usage: algorithm.py [-h] CHEATCODE [CHEATCODE ...]

Hash some cheat codes

positional arguments:
  CHEATCODE   Cheat code to hash

options:
  -h, --help  show this help message and exit
```

Example usage:
```cmd
python -m carmcheat.algorithm helloworld carmageddon
29cee8d4:8830c0d6:helloworld
278d1b49:aac7ec2e:carmageddon
```

## Use SAT solver to find cheat codes resulting in a certain hash

This requires [z3-solver package](https://pypi.org/project/z3-solver/).

```cmd
$ python -m carmcheat.cheat_retrieval -h
usage: cheat_retrieval.py [-h] [--crib CRIB] [--database DB] target length

Use SAT solver to find cheat codes hashing to a target

positional arguments:
  target         Target hash (format=XXXXXXXX:XXXXXXXX), where X is hexadecimal
  length         Length of cheat code

options:
  -h, --help     show this help message and exit
  --crib CRIB    Find only cheat codes that contain the 'crib'
  --database DB  Append found cheat codes to this database
```

Example usage:
```cmd
$ python -m carmcheat.cheat_retrieval 29cee8d4:8830c0d6 10 --database dummy.potfile
Looking for cheat codes hashing to 29cee8d4:8830c0d6:
Starting search...
29cee8d4:8830c0d6:helloworld
Search finished
```

## Sort and remove duplicates from a database
```cmd
$ python -m carmcheat.sort_database -h
usage: sort_database.py [-h] [--write [DB]] database

Sort a database + remove duplicates

positional arguments:
  database      database file to sort

options:
  -h, --help    show this help message and exit
  --write [DB]  database to write
```

Example usage:
```cmd
$ python -m carmcheat.sort_database dummy.potfile --write
Writing db to dummy.potfile (1 entries)
```

## Verify a database
```cmd
$ python -m carmcheat.verify_database -h
usage: verify_database.py [-h] database

Verify a database

positional arguments:
  database

options:
  -h, --help  show this help message and exit
```
Example usage:
```cmd
$ python -m carmcheat.verify_database dummy.potfile
1 items were found.
Database OK!
```
