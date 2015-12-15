A write test for Quantum SNFS inspired by the style with which BoxLib (https://ccse.lbl.gov/BoxLib/) codes write files. Made neccessary by the fact, that this seems to be the only filesystem on which writing is not possible. This test does not reproduce the full error seen with BoxLib, but still shows, that there is a huge issue whith metadata inconsistencies among nodes.

There are a few differences compared to BoxLib:
 * We only write to one file with one process at a time. Same behaviour as with nOutFiles = 1.
 * We only write out the beginning of the first "FAB" each process write, not of every "FAB".

For license see BoxLibs license.txt .
