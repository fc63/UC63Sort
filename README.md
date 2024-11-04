
# UC63Sort

UC63Sort is a unique counting sort implementation that efficiently sorts arrays by first identifying unique elements and counting their occurrences, then sorting these unique values. This approach aims to reduce redundant data operations, achieving optimal performance with arrays containing repeated values. The algorithm name combines "63" as the insertion sort run size and "UC" for "Unique Counting."

## Features

- **Unique Detection and Counting:** Identifies unique elements and counts their occurrences to reduce array size before sorting.
- **Hybrid Sorting Strategy:** Combines insertion sort and merge sort for handling arrays of various sizes effectively.
- **Memory Efficiency:** Uses dynamic allocation for unique elements and count arrays, freeing memory as needed.
- **Performance:** Designed for speed and efficiency by minimizing redundant operations on duplicate elements, making it well-suited for arrays with repeated values.

## How it Works

- **Unique Detection:** The algorithm iterates through the array, identifying unique elements and counting their frequencies, stored in a separate data structure.
- **Sorting Unique Elements:** Uses a hybrid sorting approach with insertion sort for smaller subarrays (up to 63 elements) and merges sort for larger segments.
- **Array Reconstruction:** Reconstructs the original array based on sorted unique elements and their frequencies.
## Examples

```
int arr[] = {63, 3, 12, 1, 5, 5, 3, 9};
int size = sizeof(arr) / sizeof(arr[0]);

UniqueData data = findUniqueAndCounts(arr, size);

sortUniqueArray(data.uniqueArr, data.uniqueSize);

reconstructArray(arr, data);

printArray(arr, size);
```

## Time Complexity
The time complexity of the UC63Sort is **O(n + u⋅log⁡(u))**, where:

- ***n*** represents the total number of elements in the input array.
- ***u*** represents the number of **unique** elements in the array.


1. **Finding Unique Elements and Counting Occurrences:** The algorithm iterates through the input array once to identify unique values and count each element's occurrences, contributing an **O(n)** complexity.
2. **Sorting Unique Elements:** The unique elements are sorted with an insertion-based sorting approach. This sorting step has a complexity of **O(u ⋅ log⁡(u))**, where ***u*** is typically much smaller than ***n*** when there are fewer unique elements.
3. **Reconstructing the Original Array:** Using the sorted unique elements and their counts, the algorithm reconstructs the sorted array in **O(n)** time.

\
Thus, the overall complexity is efficiently reduced to **O(n + u⋅log⁡(u))**.

## Space Complexity
The space complexity is **O(n)**:

- The auxiliary structures (uniqueArr, countArr, and isUnique) each allocate memory proportional to the input array size **n**, ensuring minimal memory overhead.
- Since the isUnique array only allocates up to the size of the input array, the space complexity remains **O(n)**.

This balance of time and space complexity makes the code suitable for processing large arrays with numerous duplicate entries, maintaining efficient memory usage and execution speed.

***Note:** A value of 63 for RUN is not the most efficient. I think default value should be 32. 63 is only my signature. It will probably work better with powers of 2, such as 16, 32, 64. For today, the most efficient value is probably 32. For smaller data, you can change 63 to 16, or 64 for larger numbers. Insertion Sort can become significantly less efficient after a size of 64. However, using a value of 63 does not increase time complexity.*

## Detailed for RUN size

The value of RUN (the size of the subarrays being sorted by insertion sort) can significantly affect the overall time complexity of the algorithm.

When the RUN size is small (such as 32 to 64 elements), insertion sort works efficiently because it performs well on small arrays, even though it has a time complexity of O(n^2). This keeps the overall sorting process efficient, typically running in O(n log n) time because the main sorting process is handled by merge sort.

However, as the RUN size gets larger (approaching the square root of the total array size, or n^(1/2)), insertion sort has to handle increasingly larger subarrays. Since insertion sort has a O(n^2) time complexity, it becomes slower for these larger subarrays. When RUN is too large, the quadratic time complexity of insertion sort starts to dominate, causing the overall algorithm to behave more like O(n^2) instead of O(n log n).

Example:

- If your array has 10,000 elements, and the RUN size is around 100 (which is roughly the square root of 10,000), the insertion sort's O(n^2) nature becomes noticeable and starts to slow down the sorting process.
- On the other hand, if the RUN size is small (like 32 or 64), insertion sort remains efficient, and the algorithm maintains its faster O(n log n) behavior.

In short, if the RUN size is close to the square root of the total number of elements in the array, the performance of the algorithm can degrade towards O(n^2). Keeping RUN small ensures that the faster O(n log n) performance of merge sort is maintained.
