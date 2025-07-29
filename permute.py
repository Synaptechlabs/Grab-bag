word = "bird"
st = sorted(word)  # ['b', 'd', 'i', 'r']
l = len(st)
output=[]

print("Original:", st)

for i in range(l * l):
    # Rotate right
    last = st[-1]            # Save last
    for j in range(l - 1, 0, -1):  # Shift right
        st[j] = st[j - 1]
    st[0] = last             # Put last in first position
    exp=''.join(st)
    if exp not in output:
        output.append(exp)
    print("Step", i + 1, ":", ''.join(st))


print(output)