This program generates correct (most of the time) sentences using data files. Right now, these are simply random sentences, so it's a kind of shotgun-approach to cracking the cheat. The nouns are also Gonad cheat-specific, currently.

## Usage
Download the latest version of node and run the following command in this folder: `node index`

(There are no command line arguments, but you might be interested in changing maxSize in `index.js`)

## Data files
* sentence_structures - basic building blocks for making sentences, containing different arrangements of 'markers'
* subjects - list of subjects, you can specify the letter that needs to be added to a regular verb if the subject is used (eg. subject `maxdamage s` and verb `eat` -> `maxdamageeats`)
* adjectives - simple list of adjectives
* articles_prepositions - list of articles/prepositions, can specify if it shouldn't be used if the noun starts with a vowel (eg. article/preposition `a !firstvowel` and noun `anchor` will result in a different article being picked, because it doesn't satisfy the rule that the first letter of the noun should not be a vowel)
* nouns - simple list of nouns
* verbs_regular - simple list of regular verbs