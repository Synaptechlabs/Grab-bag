import random

def say_Hello(name):
    print(f"Hello {name}")

def selection_sort(arr):
    #find the minimum index
    n = len(arr)
    for i in range (n):
        minIndex=i
        for j in range (i+1,n):
            if(arr[j]<arr[minIndex]):
                minIndex=j
            
        # Swap the found minimum element with the first element
        arr[i], arr[minIndex] = arr[minIndex], arr[i]
    return arr

    

#print("hello")
random_list = [random.randint(1, 100) for _ in range(1000)]
#say_Hello("Scott")
#print(random_list)
print("\n\n")
print(selection_sort(random_list))