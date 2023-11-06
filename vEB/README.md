# van Emde Boas Tree
- **Data structure:** van Emde Boas Tree.
- **Language:** C++

The implementation is divided in three main versions:

1. Preliminary (`veb_pre`): preliminary version of vEB tree. Implements basic concepts as binary size and bitwise manipulation for simplicity and speed, *summary* structure and all operations of vEB.
2. Recursive (`veb_rec`): improvement of previous implementation, defining a recursive structure inside each cluster. This optimization speeds up the operations of the tree.
3. Final (`veb`): further improvement of previous recursive implementation. These improvements aims to achieve the final complexity of $O(log\,log\,u)$ in the operations.

Furthermore, there is some variations of the cited implementations. Originally, **the **vEB** tree does not allow repeated keys** (like a `set`). So, for each version, there is an alternative version that **allows repeated keys** (like a `multiset`). These variations are named `multi_<name>`, where `<name>` is the name of the respective version.

## Testing

### Generation

Execute `gen_test.py` to generate `in` and `sol` files.
  - `in` : file containing a random generated input to be tested (file structure explained [below](#input))
  - `sol` : expected output


### Input

The first line have two positive integer numbers $U$ and $N$, the **maximum value** allowed inside the structure and the **number of operations** to be executed. Then, follows $N$ lines describing each operation.

Each operation line starts with an integer $op$, the operation type. Depending on the operation, it can be followed by a number $x$. The operations can be:

  - 1 $x$ : insert number $x$
  - 2 $x$ : delete number $x$
  - 3 : get size
  - 4 $x$ : check whether $x$ is in the structure (0 or 1)
  - 5 $x$ : get the successor of x (-1 if none)
  - 6 $x$ : get the predecessor of x (-1 if none)
  - 7 : get the minimum (-1 if empty)
  - 8 : get the maximum (-1 if empty)
  - 9 : delete and get the minimum (-1 if empty)

### Output

For each operation that returns a value ($op>=3$) print the result and break a line `\n`.

## Acknowledgments

- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). Algorithms, 3rd edition. Cambridge, MA: MIT Press.