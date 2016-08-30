SAUCER SHOOT
By Gavin Hayes gahayes@wpi.edu
IMGD3000 A16

Saucer Shoot game from Dragonfly tutorial with additions.

Developed in Windows VS2015. Use the project in the vs-2015 directory.
To build in VS, press F7 to build and F5 to run. dragonfly and
SFML-2.4 must exist in the directory above gameTutorial. 

Code structure is almost the same as the tutorial, but all "Get" calls
are compared to be vald before using the result. Game starts in game.cpp, after initialization starts a splash screen (main menu screen) from game start. If the game is started a Hero is generated in Hero.cpp. 
The Hero is controlled in Hero.cpp by listening to keyboard events. If the Hero died, GameOver splash screen is 
played before reverting back to GameStart.

See GAME.txt for notes on how the project was expanded. 

VS project includes references to universal CRT runtime on Windows 7
since it did not correctly include that when installing VS2015 on Windows 7.
This should not affect building if UCRT is properly connected with VS. 

Makefile is the same as the one from game0 in the tutorial. With additions
of the other files this project is buildable on linux. 

