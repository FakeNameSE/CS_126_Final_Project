# Development Log

## Things to fix

## Things to add
### Core
- [] Finish exploratory work with the interface and JSON parsing.
- [] Create a basic canvas to draw on.
- [] Implement saving the image.
- [] Create an interface to change brush color.
- [] Add methods to parse and load the JSON data.
- [] Cleanly handle absent data in the JSON file if necessary.
- [] Implement useful error handling for these methods.
- [] Create a dinosaur information label.
- [] Add a method to convert the JSON data into a beautified string to display in the label.
- [] Add a button to toggle the visibility of a dinosaur information label.
- [] Implement a method to randomly select a dinosaur to display information on.
- [] Work on theming to make the interface look better.
- [] Refactor the different UI components into groups if it would clean up the code.
- [] Implement basic keyboard shortcuts.
- [] Flesh out the JSON file with a useful amount of dinosaur facts.
### Nice to haves, pick at least one
- [] Add multiple brushes to toggle between.
- [] Add the ability to change the brush stroke thickness.
- [] Add the ability to overlay the drawn image over a background.
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
