import re
from cs50 import get_string

def words(sentence):
    words = text.split(' ')
    return words

text = get_string("Input some text: ")

# Regex to split sentences 

# robust re for spliting sentences
sentences = re.split(r"(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s", text)

# A less robust re for same thing but this works as p sets discription
# sentences = re.split(r"\.|\!|\?", text)

words = text.split()

letters = 0

for letter in range(len(text)):
    if text[letter].isalpha():
        letters = letters + 1

L = letters
S = len(sentences)
W = len(words)

print(f"Letters: {L}\nWords: {W}\nSentences: {S}")

CLI = round(0.0588 * ((100 * L) / W) - 0.296 * ((100 * S) / W) - 15.8)

print(f"Grade {'16+' if CLI > 16 else CLI if CLI > 1 else 1}")
