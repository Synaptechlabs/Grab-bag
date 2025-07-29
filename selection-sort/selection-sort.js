let arr = [3, 6, 4, 1, 7, 8, 9, 5];

let n = arr.length;

for (i = 0; i < n; i++) {
  console.log(arr[i]);
}

for (let i = 0; i < n - 1; i++) {
  let minIndex = i;
  for (let j = i + 1; j < n; j++) {
    if (arr[j] < arr[minIndex]) {
      minIndex = j;
    }
  }
  if (minIndex !== i) {
    [arr[i], arr[minIndex]] = [arr[minIndex], arr[i]];
  }
}

for (i = 0; i < n; i++) {
  console.log(">" + arr[i]);
}
