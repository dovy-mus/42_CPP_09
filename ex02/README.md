# PmergeMe - Ford-Johnson Sort Implementation

This project implements the **Ford-Johnson algorithm** (also known as merge-insertion sort) in C++98 to sort a sequence of positive integers. It demonstrates the algorithm's application using two different containers: `std::vector` and `std::list`.

## The Algorithm: Ford-Johnson (Merge-Insertion)

The Ford-Johnson algorithm is designed to minimize the number of comparisons required to sort a collection. It works in three main phases:

1.  **Pairing and Comparison**:
    - The input elements are grouped into pairs.
    - Each pair is compared, and the larger element is distinguished from the smaller one.
    - If there is an odd element ("straggler"), it is set aside.

2.  **Recursive Sorting**:
    - The "larger" elements from step 1 are recursively sorted. This continues until the base case (1 or 0 elements) is reached.
    - Once the recursion unwinds, we have a sorted sequence of the "larger" elements, which forms our "main chain".

3.  **Insertion (The "Merge" Phase)**:
    - The "smaller" elements associated with the sorted "larger" elements are inserted into the main chain.
    - To minimize comparisons, these insertions are performed using **binary search**.
    - **Crucial Optimization**: The order of insertion is not sequential. Instead, elements are inserted in groups determined by the **Jacobsthal sequence**.

### The Jacobsthal Sequence

The Jacobsthal sequence is defined as:
$J_n = J_{n-1} + 2J_{n-2}$
Sequence: 0, 1, 1, 3, 5, 11, 21, 43, 85, 171...

In Ford-Johnson sort, this sequence dictates the order in which pending "smaller" elements are inserted into the main chain. 
Specifically, we insert elements in chunks:
- First, the element paired with the smallest element of the main chain.
- Then, we take the next group of elements up to index $J_k$, and insert them in **descending order** of their indices (e.g., insert index 3, then 2; insert index 5, then 4).

**Why?**
By inserting elements in this specific order, we ensure that the size of the "main chain" (the search space for binary search) is always close to a power of 2 minus 1 ($2^k - 1$). This allows the binary search to utilize its maximum theoretical efficiency, ensuring the worst-case comparison count is minimal.

## Containers and Performance

The project implements the exact same logic for two containers to compare performance:

### 1. `std::vector`
- **Characteristics**: Contiguous memory, $O(1)$ random access.
- **Binary Search**: `std::lower_bound` is efficient ($O(\log n)$ comparisons and steps).
- **Insertion**: Expensive ($O(n)$) because elements must be shifted.
- **Performance**: Despite expensive insertions, `std::vector` is often surprisingly fast due to excellent **cache locality**. The CPU can prefetch data efficiently.

### 2. `std::list`
- **Characteristics**: Doubly linked list, non-contiguous memory.
- **Binary Search**: `std::lower_bound` performs $O(\log n)$ comparisons but requires $O(n)$ iterator increments to traverse the list.
- **Insertion**: Cheap ($O(1)$) as it only involves pointer updates.
- **Performance**: Generally slower than `std::vector` for this algorithm. The traversal cost during binary search and the poor cache locality (pointer chasing) usually outweigh the benefit of cheap insertions.

## Build and Run

**Compilation:**
```bash
make
```

**Usage:**
```bash
./PmergeMe <sequence of positive integers>
```

**Example:**
```bash
./PmergeMe 3 5 9 7 4
```

**Output:**
- Shows the sequence before and after sorting.
- Displays the time taken for each container (in microseconds).
- Displays the number of comparisons performed.
