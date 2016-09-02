SAUCER SHOOT
By Gavin Hayes gahayes@wpi.edu
IMGD3000 A16

Saucer Shoot game from Dragonfly tutorial with additions.

Developed in Windows VS2015. Use the project in the vs-2015 directory.
To build in VS, press F7 to build and F5 to run. dragonfly and
SFML-2.4 must exist in the directory above gameTutorial. The VS
version loads sprites and sounds from the directories inside of the
vs-2015 directory.

Code structure is simular to the tutorial with major changes to Hero.
Due to expanding to coop (see GAME.txt). Input reading has moved 
to SSManager. Nukes were moved too as they are usuable by anyone.
In order to get rid of a lot of duplicate calls in Hero and Hero2,
base functionality has been moved to HeroBase. with only Hero and Hero2
having custom constructors, destructors, and fire functions.

All "Get" calls are compared to be vald before using the result. Game starts in game.cpp, after initialization starts a splash screen (main menu screen) from gameStart and SSManager. In coop modes, GameOver is only set
if both players died or quit is pressed.

See GAME.txt for notes on how the project was expanded. 

VS project includes references to universal CRT runtime on Windows 7
since it did not correctly include that when installing VS2015 on Windows 7.
This should not affect building if UCRT is properly connected with VS. 

Makefile is the same as the one from game0 in the tutorial. With additions
of the other files this project is buildable on linux. 

