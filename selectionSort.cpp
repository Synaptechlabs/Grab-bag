#include<iostream>
#include<vector>

// Use a macro that works with templates — define it using 'auto' or template param
#define exch(a, b) { auto t = a; a = b; b = t; }


template<typename T>
void selectionSort(std::vector<T>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        size_t min = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[min]) min = j;
        }
        exch(arr[i], arr[min]);
        //std::swap(arr[i], arr[min]);
    }
}

int main(){
    std::vector<int> a = {7, 3, 5, 1, 9};
    selectionSort(a);

    for (auto x : a) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}
