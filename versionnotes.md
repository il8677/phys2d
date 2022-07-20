# Changelog
## a1
First collision implementation

Bugs:
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
        - 10% frame time reduction

## a3
- Testworld
    - Better more optimised rendering
        - 10% frame time reduction
    - Sweep and prune