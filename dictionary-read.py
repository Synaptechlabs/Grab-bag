from nltk.corpus import words
import nltk

# First-time use? Uncomment the next line to download the word list:
#nltk.download('words')

# Get the list
word_list = sorted(words.words())
count=1
for word in word_list:
    print(str(count)+". "+word)
    count+=1

# Print the first 20
#print(word_list[:20])


'''
with open("/usr/share/dict/words") as f:
    english_words = set(w.strip().lower() for w in f)
    print(sorted(english_words))
'''