# Mercenaries
    This program will simulate a match of Mercenaries from Resident Evil 3. It will read
    in a file to get the names of the mercenaries players that will compete, then it will read another
    where each line is an event in the game (mercenary defeated enemy or saved civilian). The program
    uses an priority queue in maxheap order to maintain the list of mercenaries and their current point
    rankings. Every time a mercenary earns points, the heapArray that holds all of the point values will
    be updated, and the priority queue will use bubbleUp to switch the places of mercenaries in case one
    gains more points than another. Finally, the program will output the priority queue and rank the mercenaries.
    Point Values:
    - Zombies × 1.0
    - Spiders × 1.1
    - Drain Deimos × 1.2
    - Zombie Dogs × 1.3
    - Hunters × 1.4
    - Nemesis × 1.5
    - Civilians Rescued × 2.0
    Output: Instances where there is a new leader in the rankings, then the overall rankings once the simulation file
    is read.
