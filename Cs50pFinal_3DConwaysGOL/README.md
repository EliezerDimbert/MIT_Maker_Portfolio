# 3D Conway's Life
#### Video Demo:  https://youtu.be/nYCoh-rT5bQ
#### Description: A rendition of the popular cellular automota Conway's Game of Life. 

# The project can be spit into 2 parts: 
## Player Controls
### processKeys
This function is the gate between the user and the project. VPython comes with a function keysdown() which returns a list of all the keys pressed. However, this does not work anywhere but the main() function. Thus, I have to pass it in as a paramter at all times. <br>
You may also notice how some if statements look odd. This is because vPython, when parsing keyboard input, will understand 'upArrow + shift' as '(' and 'shift'. <br>
There is little to note in this function besides the box action (used by pressing 'b'). This will check if the sphere which repersents the first poition is on the board or not. If not it will place it at your current position. If it is, it will go through the process of using min/max  to create a box of live cells. <br>
### Binds
Next are all the binds for all the buttons. Because vPython has a problem with sticky keys, I wanted a user to have a way to bypass it. These functions are small and are just smaller peices of the <i>processKeys</i> function.
## Simulation
### My system
To begin, my system for this project revolved around a 3D array of spheres. Since there is no way to delete a vPython object, I decided the best way to differentiate between a alive and dead cell would be through the visible attribute. When a cell is alive, it is assigned a value of true and given a color. If it is dead, the value is flipped and the user no longer sees it. <br>
On another note, neighbors are defined as all the cells surrounding the target cell when looked at from all three axies. What this means is we end with a mishapen "sphere" and miss the corners if I had just made a box. <br>
On another note, this project was made with X repersenting L/R, Y as Up/Down, and Z as Forward/Backwards. I understand that this is unlike any other typical 3D (ex lefthand and righthand) rendering but I was going for the most simple way to intergrate this with a 3D array.
### findNeighborsOnAxis/findNeighborsOnAllAxis
This simple problem soon became a headache of implimentation. In the end, I took a page out of the cs50x filter project had 2 loops go through -1, 0, and 1. These two values became "relitiveX/Y". I call them relitive because now the wording makes sense no matter the axis you are veiwing. For example, when veiwing from the X axis (that being straight ahead) relitiveX is the x axis and relitiveY is the y axis. Simple right? But when you look on the y axis (from the side), now your relitiveX is now the z axis and the relitiveY is the Y axis.<br>
Now there was the problem that a single neighbor could be counted twice if in the right spot. Thus, an array called <i>alreadyCountedNeighbors</i> was made to keep track of what has been been counted yet and what hasen't.
### runGeneration
This is the meat of the project since it is what drives the simulation. However, it is as inefficient as can be. The reason for this is the eaisist way to update a board is to go through the entire matrix twice which is O(n^3 * n^3). This brute force meathod is required because the first time around you need to decide if in the next generation this cell should be alive or not then add them to the corresponding list. The next loop then looks through both lists and actually updates the values of the cell.<br>
This double loop is used because if it was done in the same loop, the updated cells would influence cells that have not been update thus "poisoning" the generation and getting incorrect results.
### Threads
Having used threads before in my cs50x final project, I decided to use them again here. When the user presses the button (or s), a new thread is created that runs <i>runGeneration</i> until a stop eventt is created.

## Known Issues
<ol>
<li>This does not run in VsCode Web. I have no idea why but vPython simply wont work no matter what. I had to (on a mac) create a virtual space for Python in order for it to even create a simple 3D object
<li>Pressing s or start will create multiple threads simultaneously. I attempted to fix it but I was already so far on I decided it wasen't worth the bother.
<li>The simulation won't follow the rules. Sometimes, with no warning, th simulation will just break. Wheather it be my shotty programming or some stroke of god I will never know why.
</ol>

## Reach me
If you have any (hopefully good) comments, feel free to reach out at eliezer@dimbert.net.