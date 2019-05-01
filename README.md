# README
 * Overview
 * Requirements
 * Installation
 * Citations

## Overview
The aim of this final project is to enable and empower the purest of artistic expressions—shoddy dinosaur doodles.

More specifically, this project will provide a drawing application and a dinosaur themed source of artistic inspiration.

It provides the user with numerous features including:
- Saving and loading images, including via drag and drop
- An eraser.
- Multiple brushes.
- The ability to clear the screen.
- The ability to change brush color (including transparency) and thickness.
- Information on a random dinosaur when a button is toggled.

## Requirements
* OpenFrameworks version 0.10.1 or higher. OpenFrameworks has changed quite a bit in recent years, so no guarantees about this working on past versions. To install OpenFrameworks, follow the instructions [here](http://openframeworks.cc/download/).

You will also need to add [ofxGuiExtended](https://github.com/frauzufall/ofxGuiExtended), [ofxJSONElement](https://github.com/jeffcrouse/ofxJSON) and [jsonCPP](https://github.com/open-source-parsers/jsoncpp). Follow their instructions on installation and either manually add them to the `addons.make` or use the `projectGenerator` to add them.

## Installation
Installation is quite straightforward.
Steps:
1. `git clone`.
2. run `make`, or use Visual Studio or XCode depending on your environemnt.
3. Run using an IDE or `make RunRelease`.

## Code Style
This was written to the best of my ability following Google C++ Style Guide (https://google.github.io/styleguide/cppguide.html). Note that methods required by OpenFrameworks tragically deviate from this style.

## Demo
Below is a demo of the app in action. Notice that the app supports both Save and Save-As functionality. 
<p align="center">
  <img width="419" height="247" src="demo.gif">
</p>

## Citations
I used the graphics chapter of the [ofBook](https://openframeworks.cc/ofBook/chapters/intro_to_graphics.html) as an inspiration for creating brushes from geometric shapes.


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
