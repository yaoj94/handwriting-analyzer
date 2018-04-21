# Project Development
## TODO
- [X] Gather data from tablet
  * Successfully reads and stores pressure and lines as float and ofPolyline respectively - stored in Strokes object
  * Problem: The mapping of the tablet is off as the program doesn't read pen at correct locations unless the window is fullscreen i.e. the top left corner of the tablet corresponds to the top left corner of the screen, not the application window
  * Solution: I'll have the application be fullscreen for now

- [X] Draw background

- [X] Draw strokes to screen
  * Successfully draws lines as pen moves
  * Problem: Not important for functionality but I can't figure out how to draw line thickness with respect to pen pressure so it only draws in one thickness

- [X] Implement timer to read writing speed
  * Uses openframeworks built in time functions to keep track of how long the pen is drawing for
  * Problem: What data type should I use to store the information? Got rounding errors when I used int
  * Solution: used double for more accuracy when calculating average and for rounding but method returns uint since only a positive approximation is necessary for future use

- [ ] Come up with personality characteristics and analyze data for them
  * Stores pressure at every point vector and calculates average pressure, finds margins by leftmost and rightmost points, gets connectedness by checking how many times strokes intersect
  * Calculate connectedness by counting overlaps and subtracting from size of strokes rather than having separate variable to count both separately
  * Problem: If I write too fast, the points don't compare that quickly. i.e. crossing t's, a t would have connectedness of 2

- [ ] Implement methods to check whether or not the user wrote something before pressing done

- [ ] Print personality characteristics to screen
