# CS 126 Final Project Proposal
## A manifesto by Grant Garrett-Grossman


## Aims
### Overview
The aim of this final project is to enable and empower the purest of artistic expressions—shoddy dinosaur doodles.


More specifically, this project will provide a drawing application and a dinosaur themed source of artistic inspiration.

### Objectives
#### Core
- A drawing canvas.
- A usable interface to change settings such as brush color.
- The ability to save an image.
- The ability to clear the screen.
- An interface to ply the user with a random dinosaur's name and some of its information.
- Keyboard shortcuts for obvious actions (save).

#### Nice to haves, pick at least one
- Different types of brushes.
- An eraser
- The ability to change the brush stroke thickness.
- The ability to overlay the drawn image over a background.
- Displaying a sample dinosaur image alongside the dinosaur information.
- Ability to save the panel layout configuration.

## Libraries
- OpenFrameworks: the base of the windowing for the project.
- ofxGui: OpenFrameworks addon for the GUI panel interface.
- [ofxJSONElement](https://github.com/jeffcrouse/ofxJSON) and [jsonCPP](https://github.com/open-source-parsers/jsoncpp): for parsing the dinosaur JSON data.

## Additional Resources
- [The OpenFrameworks book graphics section](https://openframeworks.cc/ofBook/chapters/intro_to_graphics.html): contains a section on drawing that will hopefully be handy.
- [Dinosaur-facts-api](https://github.com/shultztom/dinosaur-fact-api/blob/master/dinosaurs.json): a json file with numerous dinosaur names and a short fact for each, still does not contain the majority of what would need to be stored for each dinosaur though.
- [ASCII Art Archive](https://www.asciiart.eu/animals/reptiles/dinosaurs): a website with text art of dinosaurs and other animals, a possible source of illustrations.
```
Dimetrodon
                          _._
                        _/:|:
                       /||||||.
                       ||||||||.
                      /|||||||||:
                     /|||||||||||
                    .|||||||||||||
                    | ||||||||||||:
                  _/| |||||||||||||:_=---.._
                  | | |||||:'''':||  '~-._  '-.
                _/| | ||'         '-._   _:    ;
                | | | '               '~~     _;
                | '                _.=._    _-~
             _.~                  {     '-_'
     _.--=.-~       _.._          {_       }
 _.-~   @-,        {    '-._     _. '~==+  |
('          }       \_      \_.=~       |  |
`======='  /_         ~-_    )         <_oo_>
  `-----~~/ /'===...===' +   /
         <_oo_>         /  //
                       /  //
                      <_oo_>
```
