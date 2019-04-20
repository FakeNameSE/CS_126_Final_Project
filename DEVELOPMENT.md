# Development Log

## Things to fix

## Things to add
### Core
- [x] Finish exploratory work with the interface and JSON parsing.
- [x] Create a basic canvas to draw on.
- [x] Create a basic drawing pen.
- [x] Mitigate issues with gaps left in trail of pen with linear interpolation.
- [x] Create an interface to change brush color.
- [x] Add interface to change stroke thickness.
- [x] Add methods to parse and load the JSON data.
- [] Cleanly handle absent data in the JSON file if necessary.
- [] Implement useful error handling for these methods.
- [x] Create a dinosaur information label.
- [x] Reduce text overflow issues in label.
- [x] Add a method to convert the JSON data into a beautified string to display in the label.
- [x] Add a button to toggle the visibility of a dinosaur information label.
- [x] Implement a method to randomly select a dinosaur to display information on.
- [] Modify MakeFile to be able to run Catch2 tests.
- [] Add tests for JSON parsing.
- [] Work on theming to make the interface look better.
- [] Refactor the different UI components into groups if it would clean up the code.
- [] Implement basic keyboard shortcuts.
- [] Flesh out the JSON file with a useful amount of dinosaur facts.
- [x] Split app into window for canvas and window for GUI.
- [x] Make closing one window close both.
- [x] Add titles to windows.
- [] Create an interface to save the image.
- [] Integrate  popup file browser to select where to save the image.
- [] Implement saving the image.
### Nice to haves, pick at least one
- [] Add multiple brushes to toggle between.
- [] Add an eraser.
- [] Restructure drawing logic to enable switching brushes.
- [] Add the ability to overlay the drawn image over a background.
- [] Add the ability to load an image file to edit.
- [] Display a sample image of the dinosaur along with its textual information.
- [] Ability to save the panel layout configuration.
---

## A Journey into the Abyss, Volume II
### Annales Grantus

### Week of April 1st
- The final expedition has begun. First signs are ominous with storm clouds brewing and great difficulties overcoming the first obstacle: the dreaded installation of OpenFrameworks. After a lengthy battle with numerous failed offensives from the package repository (AUR) and the provided tarball, this challenge was overcome, albeit only with the Nightly Build.
- The installation now overcome, example project compilation is a beast to tame in its own right. A protracted clash with the barbaric projectGenerator ended with a narrow victory; most examples compile, but only when make is run as root.
- All hope has not been lost, however. Unlike Intellij, Atom has seamless Markdown support, making the journey's preparation with the Project Proposal significantly less painful.

### April 5th, 6th, and 7th
- Compilation issues required a rapid return to the base station in order to recompile OpenFrameworks, after several attempts the projectGenerator GUI seems to have perished along with much of the expiditions morale, but the command-line version appears to work as desired.
- The discovery that multicore compilation with `make -j8` surprisingly works out of the box with the OpenFrameworks has provided a much needed speed boost to the expedition.
- A scouting mission was sent ahead and returned bruised and battered by the unforgiving cliffs of insufficient documentation. The OpenFrameworks website contains numerous references to dated builds (Eclipse and Code::Blocks namely), and an inconsistent coding style in the different addons. Worse, the online documentation is largely limited to method signatures with no description of what a given method does or how it uses its parameters.
- Another unknown looming over this mission is the role of `ofParameter` variables which wrap simple types and are ostensibly good practice, but whose actual utility remains elusive.
- Despite these setbacks, the trip to test JSON parsing was relatively painless, a welcomed development for the expedition.
- This victory was tempered by attempts to build a GUI user interface. The all but absent documentation has made this an arduous task. Moreover, since the behavior of methods is difficult to ascertain without time consuming spelunking into OpenFrameworks source code, even determining viable paths and destinations has been nearly impossible. Particularly gruesome is the apparent absence of documentation for the `add()` method of `ofxPanels`, making creating an interface with textual information for the user difficult to accomplish.
- This last challenge was at last overcome by taking the well worn path of trying something, then changing one little thing, recompiling, and checking if it is still broken, in addition to refining expectations to be better in line with the resources available.
- Specifically, rather then placing the dinosaur information in a panel, it will instead by placed in a label on the canvas with a toggle-able visibility. A possible avenue to adding images has also presented itself by saving ASCII text art into files with their paths referenced in the JSON file (since JSON does not support multi-line strings).
- Success! The exploratory mission has reported that a label can be hidden and shown with information from a parsed JSON file.

### April 12 and 13th.
- The expedition's JSON parsing code was refactored to be cleaner and support failures.
- The initial success with displaying dinosaur information in a label was met with
numerous setbacks. First, the expedition encountered excessive padding in the label,
rendering it useless to display data. Numerous attempts to use API calls to configure
this failed.
- However, just as Hannibal was forced to choose a road less charted to bring fiery
vengeance upon the impudent Rome, so must we (albeit much less dramatically) traverse
the treacherous slopes of a non-core GUI addon. The addon ofxGuiExtended has better
support for these labels, and so after a length hike, the project has been ported
to use this incompatible library instead. Of particular note was the difficulty in
setting up a toggle and listener to modify the visibility of the panel. After the
mysterious `floating point runtime error` was discovered to be a JSON error and
cryptic compilation messages shed light on the expected method signature of
listener functions for boolean parameters (different from other listeners, they
must take the new value as an argument), displaying dinosaur data with a toggle
at last works.

### April 14th.
- A new day downs upon us, and with it the need to completely rethink the
expedition's structure. A study of the tradeoffs of vector and bitmap graphics
has concluded that bitmap is more suitable from the perspective of having
differently styled lines, since while vector graphics takes care of drawing lines,
the exact parameters used to style each line would need to be stored alongside its
vertexes. Unfortunately, two steps forward, one step back. Bitmap art requires
disabling repainting the background, which prevents GUI panels from being properly
rendered in the same window. Some experimentation and an example led to a pivot
towards having two windows, one for the GUI panels and another as a canvas to
solve this problem.
- The issue of closing the entire app when one window is closed, while its technical
underpinnings remain relatively opaque (which exit function is called), was
solved from a helpful forum post.
- However, much like the cold and unforgiving mountain face that Hannibal defiantly
stared down and traversed, bitmap line drawing has many of its own pitfalls. Using
a single circle to trace the cursor gives a choppy appearance with a low thickness,
while placing an additional circle at the previous location and one in between
the current and previous is insufficient. The cursor can move faster than the
draw cycle, leaving gaps in lines. Calculating the slope between the old and new
positions and using linear interpolation to place additional circles has reduced,
but not entirely solved this problem for which there does not seem to be a good
solution for low thickness lines.
- Alas, an old fiend has returned from beyond the grave with text in the labels.
Changing the text in the labels can lead to it overflowing, an obstacle that was
largely overcome by preloading at long label into the label's ofParameter (but
not displaying it) at program launch.

### April 19th, 20th, and 21st
- Rapid progress has been made in making the brush parameters user modifiable.
The pen brush already took the radius and color as arguments, so it was a matter
of creating ofParamters for these values and hooking them up to UI elements
(trial and error and copying short snippets from examples). Conveniently, OF has
an object that wraps around ints to store a color and the UI handles this very
nicely automatically.
