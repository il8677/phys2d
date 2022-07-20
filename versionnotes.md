# Changelog
## a1
First collision implementation

### Bugs
Objects sink into each other and hence get "stuck" and experience magnetic attraction

## a2
Fixed sinking bug from a1, objects are now pushed away from each other during collision to ensure seperation

## a2.2
Testworld improvements
    - Scene categories
    - View 
        - Standardised units
        - Movable camera
### Peformance notes
sfml circles taking up a lot of memory. Or maybe broadphase contact allocs? (3.19GiB)

## a3pre1
- Testworld
    - Better more optimised rendering
        - 28% frame time reduction (900->650)

## a3pre2
- Early sweep and prune

### Bugs:
Sorting done by center. Causing small objects to come before bigger objects even though the bigger objects extent might start first. Meaning objects that are colliding aren't always registered.

## a3pre3
- Sweep and prune functional
- Slower than brute force

### Optimization:


## a3
- Testworld
    - Better more optimised rendering
        - 28% frame time reduction (900->650)
 - Sweep and prune