const pluralize = require('pluralize')
const fs = require('fs');
const path = require('path');

const vowelCheck = {
  a: true,
  e: true,
  i: true,
  o: true,
  u: true
};

const adjectives = readData('adjectives');
const articlesPrepositions = readData('articles_prepositions');
const nouns = readData('nouns');
const sentenceStructures = readData('sentence_structures');
const subjects = readData('subjects');
const verbsRegular = readData('verbs_regular');

const n =
  adjectives.length * articlesPrepositions.length * nouns.length *
  sentenceStructures.length * subjects.length * verbsRegular.length;

console.log(n + ' combinations');

const maxSize = 1000000000;
const buffer = [];
for (let i = 0; i < maxSize; i++) {
  buffer.push(generateRandomSentence());
  console.log(buffer);
  if (buffer.length > 250000) {
    fs.appendFileSync(path.join(__dirname, 'out.dic'), buffer.join('\r\n'));
    buffer.length = 0;
    console.log(`Flushed dict buffer (${Math.round(i / maxSize * 100)}% complete)`);
  }
}

if (buffer.length > 0) {
  fs.appendFileSync(path.join(__dirname, 'out.dic'), buffer.join('\r\n'));
  buffer.length = 0;
  console.log(`Flushed dict buffer (Done!)`);
}

function generateRandomSentence() {
  const structure = randomItem(sentenceStructures);
  const subject = randomItem(subjects);
  let verb = randomItem(verbsRegular);
  if (subject.length > 1) {
    verb = verb + subject[1];
  }
  const noun = randomItem(nouns);
  let article = randomItem(articlesPrepositions);
  if (article.length > 1) {
    let needsVowel = article[1] === 'firstvowel';
    const hasVowel = !!vowelCheck[noun[0]];
    while (needsVowel !== hasVowel) {
      article = randomItem(articlesPrepositions);

      if (article.length < 2) {
        break;
      }

      needsVowel = article[1] === 'firstvowel';
    }
  }

  const adjective = randomItem(adjectives);

  return makeSentence(structure, subject[0], verb, noun, article[0], adjective);
}

function randomItem(arr) {
  return arr[Math.floor(Math.random() * arr.length)];
}

/*function* nounGenerator() {
  for (let noun of nouns) {
    yield noun;
    yield pluralize(noun);
  }
}

function* subjectGenerator() {
  for (let subject of subjects) {
    yield subject;
  }
}

function* articlePrepositionGenerator() {
  for (let articleProposition of articlesPrepositions) {
    yield articleProposition;
  }
}

function* adjectiveGenerator() {
  for (let adjective of adjectives) {
    yield adjective;
  }
}

function* verbGenerator(subject) {
  for (let verb of verbsRegular) {
    if (subject.length > 1) {
      yield verb + subject[1];
    } else {
      yield verb;
    }
  }
}*/

/*for (let sentenceStructure of sentenceStructures) {
  const buffer = [];
  let sc = 0;
  let vc = 0;

  for (let subject of subjects) {
    sc++;

    for (let verb of verbsRegular) {
      vc++;

      if (subject.length > 1) {
        verb = verb + subject[1];
      }

      for (let noun of nouns) {
        for (let articlePreposition of articlesPrepositions) {
          for (let adjective of adjectives) {
            buffer.push(makeSentence(sentenceStructure, subject[0], verb, noun, articlePreposition, adjective));
          }
        }
      }

      console.log('verb ' + vc + '/' + verb.length);
    }

    console.log('subject' + sc);
  }
}*/

function makeSentence(structure, subject, verb, noun, article, adjective) {
  return structure.replace('$SUBJECT', subject)
    .replace('$VERB', verb)
    .replace('$NOUN', noun)
    .replace('$ARTICLE', article)
    .replace('$ADJECTIVE', adjective);
}

function readData(file) {
  let splitMode = 'none';

  return fs.readFileSync(path.join(__dirname, 'data', file + '.txt'))
    .toString()
    .split('\n')
    .reduce((acc, line) => {
      const trimmedLine = line.trim();

      if (trimmedLine.startsWith('!')) {
        splitMode = trimmedLine.split(' ')[2];
      }

      if (!!trimmedLine && !trimmedLine.startsWith('#') && !line.startsWith('!')) {
        if (splitMode === 'all') {
          acc.push(trimmedLine.split(' ').map((ent) => ent.trim()));
        } else if (splitMode === 'last') {
          const splitLine = trimmedLine.split(' ').map((ent) => ent.trim());
          let lastWord;

          if (splitLine.length > 1) {
            lastWord = splitLine.pop();
          }

          acc.push([splitLine.join(' '), lastWord].filter(ent => !!ent));
        } else {
          acc.push(trimmedLine);
        }
      }

      return acc;
    }, []);
}