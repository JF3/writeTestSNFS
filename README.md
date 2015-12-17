A write test for Quantum SNFS inspired by the style with which BoxLib (https://ccse.lbl.gov/BoxLib/) codes write files. Made neccessary by the fact, that this seems to be the only filesystem on which writing is not possible. This test does reproduce the full error as seen with BoxLib, showing that there is a huge issue whith metadata inconsistencies among nodes.

There are a few differences compared to BoxLib:
 * We only write to one file with one process at a time. Same behaviour as with nOutFiles = 1.
 * We only write out the beginning of the first "FAB" each process write, not of every "FAB".

A sample result at GWDG looks like:
```
% ./check 
Seeking to 0
Seeking to 33555072
Seeking to 51905138
Expected 'F', got Y
Expected 'A', got Y
Expected 'B', got Y
Seeking to 105383222
Expected 'F', got Y
Expected 'A', got Y
Expected 'B', got Y
```

For license see BoxLibs license.txt .
