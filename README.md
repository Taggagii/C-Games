# General Description
This repository contains games coded in C utilizing the SDL2 Graphics Library. The games are far from perfect and provide only simple examples of different C coding techniques and concepts.
My goal in creating these graphical masterpieces was to further my understanding and increase my comfort in C. It was not my intent to take credit for any of these titles, nor was it to slander the original creators. Anyway, enjoy these pixelated abominations. 

Anyone harmed in the making of these games can contact me...somehow...and explain their complaint directly. I'm sure I can help mitigate the pain I have caused.
<p>&nbsp;</p>

# How to make
###### *For windows*
### Setting up SDL2
1. Download [Visual Studios for Windows](https://visualstudio.microsoft.com/downloads/)
2. Download [SDL2](https://www.libsdl.org/release/SDL2-devel-2.0.12-VC.zip) for Visual Studios (Visual C++) 
3. Unzip the SDL2 file and put the resulting folder somewhere safe do **NOT** leave it in your downloads folder
4. Create a Visual Studios project and add all the game files into the folder named after your project (**make sure the files show up under _source files_ in your solution explorer or the following steps won't work**)
5. Click on _project_, then, at the bottom, properties
6. Now, in properties, select _VC++ directories_
7. Select _include directories_, press the downward arrow (on the far right), press <Edit...>
8. Now, editing, you should see _Include Directories_ at the top of a window which has just appeared. Press the new file button (looks like a file with a plus sign) and then click the three dots next to the resulting line
9. By pressing the three dots you have now entered into your file system. Navigate to your SDL folder which you saved in a safe place from step 3.
10. Enter the SDL folder and select _include_. This is the folder you want
11. After selecting this folder, click _ok_ on the _Include Directories_ pop up.
12. Now, select _Library Directories_ and do steps 8 and 9.
13. In you SDL folder, enter into your _lib_ file, and select _x86_. This is the folder you want. 
14. Click _ok_ on the _Library Directories_ pop up which should close the pop up. 
15. Now, select _linker_ and go to _General_ under it. 
16. Find _Additional Library Directories_ and press the downward arrow, then <Edit...>
17. Perform step 13. (you should end up with the _lib/x86_ path at the end of your selection)
18. Under _linker_, locate _input_
19. Press _Additional Dependencies_, click the downward arrow, then <Edit...>
20. Under the pop up _Additional Dependencies_ type:<br/>
                SDL2.lib<br/>
                SDl2main.lib<br/>
21. Click __Apply__ then __ok__
22. Navigate to your SDL folder from step 3, and enter into _lib/x86_, you should see a .dll file, copy this file into the same folder (in your Visual Studio project folder) you used in step 4
22. Finally, for each game, enter the _Game_Values.h_ file and find the `#include <SDL2/SDL.h>` line, change this to be `#include <SDL.h>`
23. Run the code by pressing f5, _Debug_ > _Start Debugging_, or by clicking the green "play button" at the top.

### Game Alterations
#### Tetis
The block will fail to fall, change the line `int speedUpInterval = 90000;` to `int speedUpInterval = 1000;`
#### Connect Four
Is broken. It uses includes which are only usable on Mac. This was a poor choice on my part and is the only game which seems not to run
<p>&nbsp;</p>


###### *For mac*
#### REQUIREMENTS
- [SDL2](https://www.libsdl.org/download-2.0.php)
- [Clang](https://releases.llvm.org/download.html)
<p>&nbsp;</p>

## Make Commands
#### Navigate to the proper folder
```console
cd where/you/store/the/folder
```
#### Create executable file
```console
clang "GameName".c -std=gnu17 -lSDL2 -o play
```

#### Run the executable
```console
./play
```
