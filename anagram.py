def permute(s):
    if len(s) == 1:
        return [s]
    
    result = []
    for i in range(len(s)):
        # Choose the current character
        current = s[i]
        # Remaining string without the current character
        remaining = s[:i] + s[i+1:]
        # Recurse on the remaining string
        for p in permute(remaining):
            result.append(current + p)
    
    return result

def permute2(s, prefix=""):
    if len(s) == 0:
        print(prefix)
    else:
        for i in range(len(s)):
            remaining = s[:i] + s[i+1:]
            permute2(remaining, prefix + s[i])



# Example usage
perms = permute("xylophone")
print(sorted(perms))

permute2("abcdefghijkl")
