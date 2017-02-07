======
README
======

The .java file contains the source code.
.jar is a compiled runnable file. To run it, type in console:

	`$ java -jar -Dsun.java2d.xrender=false Lissajous.jar`

The argument '-Dsun.java2d.xrender=false' has to be specified due to a bug in jre version 8.
Withot it the rendering is extremely slow.

To compile it from source use:

	`$ javac Lissajous.java`
	`$ java -Dsun.java2d.xrender=false Lissajous`


