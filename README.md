# externalsort
External sort for big data on disk

## Problem
Sort 2^31 intergers on the disk (16 GB) with 2 GB memeroy.

## Solution
### generate.h:
generate 2^31 intergers and store them on the disk

### dataio.h:
exchange data between disk and memory

### Loserheap.h:
uesed for merged sort

### externalsort.cpp:
main
