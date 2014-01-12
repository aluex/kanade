Project Kanade
===

##Overview
---
Kanade is a cross-platform collaborative drawing platform supporting **Wacom Tablets with Pressure**.

This is a project for the course assignment of Fundamentals of Programming and Algorithm.

The Kanade Project is composed of 3 parts:

+ Kanade-Air (Server End)
	+ Written in Node.js
	+ Provide service for Kanade-Air and Kanade-Sonic.
+ Kanade-Air (Browser Client End)
	+ Written in HTML5, CSS3, Javascript
	+ Provide real cross-platform experience.
+ Kanade-Sonic (Native Client End)
	+ Written in Qt5, currently compatible only in Windows.
	+ Provide better rendering performance and offline functions.

##Authors
---

- Aluex (Sever-End, Browser-End, Protocol Design)

- Nestle (Client-End, Brush Optimization).

##Client-End Compilation
---
Before you compile, please edit /Kanade-Sonic/Kanade/mainwindow.ui, and replace '$Path_Root$' with the path you place this repository.


##Server-End Usage
---
Assume you've installed **node.js**

To run the server, simply run

	node index.js [port]

*port* is the port number for the service, 8201 by default.

##Browser-End Usage
---
Simply visit the server with your favorite browser.

## Protocol
---
Please see */BrowserEnd/Kanade Protocol.txt* (Written in **Chinese**)

## Brower Compatibility
----
+ Linux
	+ Chrome : Well done
	+ Firefox : Well done
+ Mac
	+ Chrome : Well done
	+ Safari : Well done
	+ Firefox : Well done
+ Windows
	+ Chrome : No Wacom Support (May fix later)
	+ Other Webkit-based browser: Maybe Well done
	+ Firefox : Well done
	+ IE9+ : Well done
	+ IE7-8 : Unknown


## Acknowledgements
---
Super thanks to @CR(Jingran Chu), @Umi and @Bamboo!

Many thanks to the authors of:

 + Bootstrap
 + Font-Awesome
 + Bootstrap-Slider
 + Bootstrap-Switch
 + jQuery
 + jQuery-Colorwheel
 + JSON
 + Node.js
 + Node-Static
 + Notify.js
 + Raphael.js
 