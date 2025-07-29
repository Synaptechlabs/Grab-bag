def swap(a,i,s):
    tmp=a[i]
    a[i]=a[s]
    a[s]=tmp
    return a

def find_smallest(arr,start):
    smallest=arr[start] # 8
    smallest_index =start # 0
    for i in range(start+1,len(arr)): # 7
        if arr[i]<smallest: # 5<8 
            smallest=arr[i] #smallest = 5{1},2{4},1{6}
            smallest_index=i # 1,
    return smallest_index

def selection_sort(arr):
    for i in range(0,len(arr)):
        smallest=find_smallest(arr,i)
        arr=swap(arr,i,smallest)
        print(arr)
    return arr

def selection_sort2(arr):
    for i in range(len(arr)):
        smallest=arr[i]
        smallest_index=i
        print("LOOP:"+str(i))
        for j in range(i+1,len(arr)):
            if arr[j]<smallest:
                smallest=arr[j]
                smallest_index=j
                #now do the swap
        arr=swap(arr,i,smallest_index)
        print("Smallest:"+str(smallest))
    return arr


arr=[8,5,6,7,2,3,1]

print(selection_sort2(arr))