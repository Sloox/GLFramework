# GLFramework
A minimalistic GL framework for use in my university projects,
It is built using codeblocks in windows.
http://www.codeblocks.org/


## Basic Usage:
## Steps to get it all running


* Call Constructor To Init Winodw
* Call Glinit and place ur own GLinit function in the function call, must be void function ATM
* Add key handler, rezier, mousehandler functions to the classes
* Call Mainloop function, add glMainloop function of ur own or just call with no param

## Basic .dll includes and other prerequisets
### Please ensure the following is included
* glut32.dll is in bin folder-->omp
* libgomp-1.dll is in bin folder -->omp
* Check file locations so that there are no errors in linking

### Compiler Options
* fexpensive-optimizations 
* msse4.1 
* fopenmp //OMP enable
* mstackrealign //for SSE

### Linker Options
			<Add library="opengl32" />
			<Add library="gdi32" />
			<Add library="Glu32" />
			<Add library="glut32" />
			<Add library="gomp" />


## Last Update
V0.1--2014/May/25
_________________________________________________________________________
-Basic creation,
-Support for "glut" like constructs, 
-MouseHandler,KeyHandler,ResizerHandler all done basically,
-added support for Window sizes, titles and positions of glcontext,
-New file and folder structer,
