C Data Structure Trade-offs: Array vs Linked List
Analyzes algorithmic trade-offs (search vs. insertion complexity) of a fixed-capacity ordered array and a dynamic linked list in C.

This project implements two generic (void*) and sorted data structures from scratch to empirically analyze and demonstrate the fundamental trade-offs of each approach.

The main.c executes a stress test that includes:

Initial data loading from .csv files.

Insertions at the beginning, middle, and end of the structures.

Removals from the head and middle of the structures.

Complete memory cleanup (malloc/free) to demonstrate zero memory leaks.

------------------------------------------------------------------------------------------------------------------

Trade-Off Analysis
The goal of this project was to demonstrate the performance and memory differences between an ordered array and a linked list.

Feature	OrderedArray (Sorted Array)	LinkedList (Sorted Linked List)
Search	O(log n) - Very Fast	O(n) - Slow
Insertion	O(n) - Slow	O(n)* - Slow (to find position)
Removal	O(n) - Slow	O(n)* - Slow (to find position)
Memory	Static (Single Block)	Dynamic (Per-Node)
Key Advantage	Unbeatable search speed.	No capacity limit; O(1) insert/remove if pointer is already held.
Key Disadvantage	Costly O(n) insertion/removal (shifting). Fixed capacity.	Very slow O(n) linear search.


*While the "re-wiring" for a list insert/remove is O(1), finding the correct position in a sorted list still requires an O(n) traversal, making the total operation O(n).

-----------------------------------------------------------------------------------------------------------------

How to Compile and Run
This project is built using Code::Blocks.

1. Clone the repository.

2. Open the Tradeoffs_v2.cbp file with Code::Blocks.

3. Ensure the sample .csv file are in the data/ folder.

4. Click "Build and Run" (F9).

-----------------------------------------------------------------------------------------------------------------
Project Structure

.
├── data/
│   ├── products.csv      # Example product data
│   └── students.csv      # Example student data
├── include/
│   ├── linkedList.h      # Public interface for the LinkedList module
│   ├── orderedArray.h    # Public interface for the OrderedArray module
│   ├── product.h         # Definition of the Product struct
│   └── student.h         # Definition of the Student struct
├── src/
│   ├── linkedList.c      # Implementation of the generic linked list
│   ├── main.c            # Entry point, file loading, and stress test
│   ├── orderedArray.c    # Implementation of the generic ordered array
│   ├── product.c         # Product helper functions (create, print, etc.)
│   └── student.c         # Student helper functions (create, print, etc.)
├── .gitignore
├── Tradeoffs_v2.cbp      # Code::Blocks project file
└── README.md             # This documentation

