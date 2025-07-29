import itertools

def generate_anagrams(word):
    # Get all unique permutations of the letters
    perms = set(itertools.permutations(word))
    return [''.join(p) for p in perms]

# Example usage
anagrams = generate_anagrams("starfish")
for a in anagrams:
    print(a)
