Graphics Tutorial Template Project
==================================

The goal of this template is to encourage the use of a better and cleaner directory structure than the Visual Studio Default for **INFR 1350: Intro to Computer Graphics**

*Thomas Galati 2016*


bin/
----
	This is where the project EXE is going to be built
	This is where we should put our 3rd party DLLs

build/
------
	This is our intermediate directory
	It's where temporary build files are placed

include/
--------
	This is a 3rd party include folder
	It's where we place our 3rd party header (.h and .hpp) files

lib/
----
	This is a 3rd party library folder
	This is where we place our 3rd party .lib files	

src/ 
----
	This is where your own source files go (.h and .cpp)