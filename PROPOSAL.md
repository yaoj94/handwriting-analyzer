# Project Proposal
## Handwriting Analyzer

What does your handwriting say about you? This program will have the user write a sequence of words using a Wacom tablet and analyze the characteristics and patterns of the user’s handwriting. Similar to a personality test, it will output certain traits about the person but based off of that person’s handwriting style. 

### Collecting the data

The program will connect with a Wacom tablet using the openFrameworks addon ofxTablet, which can be found [here](https://github.com/mattebb/ofxTablet). To make things simpler, the window will display a notebook style background with lines for the user to follow, as well as give the user a sentence to write. 

The program will store an [ofPath]( http://openframeworks.cc/documentation/graphics/ofPath/) object and continuously draw the object to the screen. In order to keep track of all the points and strokes, it will store a vector of [ofPolyline](http://openframeworks.cc/documentation/graphics/ofPolyline/) objects and use methods from that class to extract data for analyzing handwriting patterns. This can be derived from examples of drawing applications, which can be found [here]( https://github.com/ofZach/drawing-examples).

Using the built in pressure sensing functionality of the tablet, it will also be able to read the pressure that the person exerts while writing, which can be factored into the analytics. In order to read the speed at which the user writes, the program will keep track of the time it takes to draw a line with a set amount of points and average the values. 

### Analyzing the data

Overall, the program will take into account certain characteristics and patterns including:
* speed of writing
* page margins
* pen pressure
* letter size
* connectedness of letters

Once the data is collected, the program should be able to tell how connected a word is by how often the pen is lifted, the size of the writing by the extreme y-values of a path, amount of spacing by checking how many lines the writing takes up, etc. However, it won’t be able to check for characteristics in specific letters, as it won’t have the ability to classify individual letters.

### How to classify handwriting?

Finally, the characteristics will be printed to the screen after collecting and analyzing the data.
There have been studies conducted on what handwriting says about one’s personality. Though not a proven science, I think it would be a fun program to design. :smiley: 

References:

https://www.businessballs.com/self-awareness/graphology-handwriting-analysis-67/ 

https://www.rd.com/advice/work-career/handwriting-analysis/
