def permute(elements):
    if len(elements) == 0:
        return [[]]
    result = []
    for i in range(len(elements)):
        rest = elements[:i] + elements[i+1:]
        for p in permute(rest):
            result.append([elements[i]] + p)
    return result

# Example usage:
items = ['A', 'B', 'C']
permutations = permute(items)
for p in permutations:
    print(p)
