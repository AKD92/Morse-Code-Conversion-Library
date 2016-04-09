# Morse Library (libmorse)
<b><i>C library for very fast conversion of Morse codes to other forms like Ascii Text</i></b>

This library is written in C language. It uses data structures and algorithms from my previous projects <a href="https://github.com/AKD92/Tree-Based-Dictionary-ADT">Tree Based Dictionary ADT</a>, <a href="https://github.com/AKD92/Stack-Queue-ADT">Stack Queue ADT</a> and <a href="https://github.com/AKD92/Linked-List-ADT">Linked List ADT</a>. The primary purpose of this project is to convert morse code from it's DOT DASH representation to ASCII Text and Binary representation, and vice versa.

### Background
It is a very useful library when working with Morse code. And I should not forget to mention that, it is a byproduct of my Digital System Design (DSD) project "Secret message tranmitter and receiver via Morse Code". On that project, we were a group of 4 team members to develop a microcontroller based solution by which Morse code can be sent digitally from one place to another wirelessly, and at the receiver end the person will see the actual ASCII text of the message converted from sender's morse code. Wireless transfer, Morse code input and conversion of Morse code to Binary and ASCII Text form is done by the microcontroller we've used. I had to program that microcontroller (an Arduino) for Morse conversion routines, and here this project is slightly modified version of that original work in order to bring broader range of capabilities and performance.

### Implemented Algorithms so far:
  * Conversion from Morse Code to ASCII Text format.
  * Conversion from ASCII Text to Morse Code format.
  * Conversion from Morse Code to Binary representation.
  * Conversion from Binary representation to Morse Code.

All these four operations return 0 for successful completion, and -1 for error. Their respective function prototypes and other information can be found in "MorseLib.h" header file. To incorporate this project into your own code, the header "MorseLib.h" must be included.

For example, well knows SOS message can be converted to it's Morse Code format
  * ASCII Text "SOS"		->		Morse Code format "... --- ..." (DOT DOT DOT DASH DASH DASH DOT DOT DOT)
  * Reverse operation of the above is also available, from Morse Code to ASCII Text

<code>include BST.h
        int main() {
         sol
         return -1;
        }</code>

<code>Panel</code> constructor:</p>
<pre><code>function Panel(element, canClose, closeHandler) {
  this.element = element;
  this.canClose = canClose;
  this.closeHandler = function () { if (closeHandler) closeHandler() };
}</code></pre>

### Dependencies
This project has 3 dependecies:
  * <a href="https://github.com/AKD92/Tree-Based-Dictionary-ADT">libbst.a</a>						General purpose Dictionary ADT implementation using Binary Search Tree (BST)
  * <a href="https://github.com/AKD92/Stack-Queue-ADT">libstq.a</a>			General purpose Stack and Queue data structure
  * <a href="https://github.com/AKD92/Linked-List-ADT">liblinkedlist.a</a>			General purpose Linked List data structure

### Notes
These dependency projects and their source codes were already hosted to my GitHub account.

Code written for this project and for their dependency projects are ISO C90 compliant.

All the projects listed above including this one is compiled using GCC 4.8 32 bit (MinGW port)

### License
<a rel="license" href="http://www.gnu.org/licenses/lgpl-3.0-standalone.html"><img alt="LGPLv3 License" style="border-width:0" src="http://www.gnu.org/graphics/lgplv3-147x51.png" /></a><br />This software is licensed under <a rel="license" href="http://www.gnu.org/licenses/lgpl-3.0-standalone.html">GNU Lesser General Public License, Version 3</a>.
