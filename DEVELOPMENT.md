# Project Development
## TODO
- [X] Gather data from tablet
⋅⋅⋅⋅⋅⋅ Successfully reads and stores pressure and lines as float and ofPolyline respectively - stored in Strokes object
⋅⋅⋅⋅⋅⋅ Problem: The mapping of the tablet is off as the program doesn't read pen at correct locations unless the window is fullscreen i.e. the top left corner of the tablet corresponds to the top left corner of the screen, not the application window
⋅⋅⋅⋅⋅⋅ Solution: I'll have the application be fullscreen for now
- [X] Draw background
- [X] Draw strokes to screen
⋅⋅⋅⋅⋅⋅ Successfully draws lines as pen moves
⋅⋅⋅⋅⋅⋅ Problem: Not important for functionality but I can't figure out how to draw line thickness with respect to pen pressure so it only draws in one thickness
- [ ] Implement timer to read writing speed
- [ ] Come up with personality characteristics and analyze data for them
- [ ] Print personality characteristics to screen
