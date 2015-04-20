# Final-Project

Looking to rewrite/expand the hash table program to include 'perfect' hashing with a singly nested secondary hash table instead of a linked list. However, since that seems kinda boring, I'll probably expand this as I find inspiration of what to do. Also, this is most likely going to be on a list of 14ers since those are much more interesting than movies. And have more information.

After long (read... a few moments) deliberation, I've decided that it would be a lot more fun to implement the 14ers as nested graphs, ordered by range with perfect hashing lookup. If this is too time consuming, unweighted edges are always super easy. The real schtickler will be modifying algorithms to go between peaks. Going between ranges is the exact same thing that was done before.

Also, this means that my .csv file now needs edges. Meh.


So far expanding ideas include...

1. Send primary and secondary table locations to arduino to either print or print in binary with LED's.

2. Read in the file initially and then 'compile' it to a binary file for primary use.

3. Construct a graph from the 14er locations as the bird flies.

  - As nodes are created, they could be hashed into the table but this may make a secondary data structure useless.

  - The main advantage of that is that accessing graph elements would take O(1) (or 2 if each hash function is an operation per say) instead of O(n) but who knows how relevant that is to this at the moment.

4. Create a color-blot (that's what I'm calling it anyways) .png or .jpeg file from binary where the locations are printed over a not-so-pretty rendering of colorado.

  - has the advantage of being mostly complete from the get-go as coordinates are easy to convert into a more localized cartesian plot.

5. I just want to get back to working on 'my' parser, really.



### Project Summary
It takes data and nibbles on it.

### How To Run
Use your legs.

### Dependencies
A computer.

### System Requirements
Ability to download RAM. Steep, I know.

### Group Members
Yours truly

### Contributors
[14ers](14ers.com) for generating the initial ranked .csv file. Nobody likes to type out 53 lines of CSV.

### Open Issues/bugs
- There doesn't seem to be any code to run.
