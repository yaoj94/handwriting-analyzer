# Project Development
## TODO
- [X] Gather data from tablet
  * Successfully reads and stores pressure and lines as float and ofPolyline respectively - stored in Strokes object
  * Problem: The mapping of the tablet is off as the program doesn't read pen at correct locations unless the window is fullscreen i.e. the top left corner of the tablet corresponds to the top left corner of the screen, not the application window
  * Solution: I'll have the application be fullscreen for now

- [X] Draw background
  * Changed background lines from vector of ofPolyline to a single ofPath object
  * Made a Quote object to keep track of the quote, number of words, and letters that get called throughout files

- [X] Draw strokes to screen
  * Successfully draws lines as pen moves
  * Problem: Not important for functionality but I can't figure out how to draw line thickness with respect to pen pressure so it only draws in one thickness
  * Changed cursor to photo of a pen
  * Problem: Draws from the top left corner of the image but it needs to be the bottom left
  * Solution: Shifted the image up by adding the image height to the y coordinate when drawing

- [X] Implement timer to read writing speed
  * Uses openframeworks built in time functions to keep track of how long the pen is drawing for
  * Problem: What data type should I use to store the information? Got rounding errors when I used int
  * Solution: used double for more accuracy when calculating average and for rounding but method returns uint since only a positive approximation is necessary for future use

- [X] Come up with personality characteristics and analyze data for them
  * Stores pressure at every point vector and calculates average pressure, finds margins by leftmost and rightmost points, gets connectedness by checking how many times strokes intersect
  * Calculate connectedness by counting overlaps and subtracting from size of strokes rather than having separate variable to count both separately
  * Question: Store pressures in vector to calculate average of later or count number of points and add up pressures as the program goes?
  * Problem: If I write too fast, the points don't compare that quickly. i.e. crossing t's, a t would have connectedness of 2
  * Problem: Needed data structure for all the factors in the handwriting
  * Solution: Created a struct for one factor that contains a level and bounds to classify the factor. Created another struct for all of the factors used throughout the program.

- [X] Implement methods to check whether or not the user wrote something before pressing done
  * Split up draw function to make draw method neater, added AnalysisState enum to switch between states - only changes if the number of strokes are around the number of words in the quote

- [X] Print personality characteristics to screen
  * Need way to store attributes and descriptions! Created separate file for attribute descriptions and stored each in Attribute struct
  * Data wasn't being updated and I realized I needed to pass by reference so I only need to change one HandwritingFactors object throughout the duration of the program
  * Problem: couldn't call the constructor of other classes in the ofApp header
  * Solution: have a setup method in the classes to initialize member variables - removed because I decided Classifier should contain the Factors since it is most directly related to the classifying
  * Had it display the characteristics as a list, which was unappealing so added ofxAVString to display text in a cooler way
  * Added FactorBubble object to draw background that depicted relative strengths/weaknesses in each attribute. So each Factor is associated with a color and the number of bubbles that get drawn depend on the level of the Factor.

- [X] Write tests for file IO and Classifier
  * Problem: Tests don't run through XCode and it can't find ofMain.h file
  * Solution: Copied the files and edited it so that the files don't depend on ofMain.h. Ran tests on CLion.


