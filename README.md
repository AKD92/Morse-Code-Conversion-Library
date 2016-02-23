# Morse-Code-Library
This library is written in C language. It uses data structures and algorithms from my previous project BST, Stack &amp; Queue and Linked List. The primary purpose of this project is to convert morse code from it's DOT DASH representation to ASCII Text and Binary representation, and vice versa.

It is a very useful library when working with Morse code. And I should not forget to mention that, it is a byproduct of my Digital System Design (DSD) project "Secret message tranmitter and receiver via Morse Code". On that project, we were a group of 4 team members to develop a microcontroller based solution by which Morse code can be sent digitally from one place to another wirelessly, and at the receiver end the person will see the actual ASCII text of the message converted from sender's morse code. Wireless transfer, Morse code input and conversion of Morse code to Binary and ASCII Text form is done by the microcontroller we've used. I had to program that microcontroller (an Arduino) for Morse conversion routines, and here this project is slightly modified version of that original work in order to bring broader range of capabilities and performance.

Implemented operations so far:
  * Conversion from Morse Code to ASCII Text format
  * Conversion from ASCII Text to Morse Code format
  * Conversion from Morse Code to Binary representation.
  * Conversion from Binary representation to Morse Code.

All these four operations return 0 for successful completion, and -1 for error. Their respective function prototypes and other information can be found in "MorseLib.h" header file. To incorporate this project into your own code, the header "MorseLib.h" must be included.

For example, well knows SOS message can be converted to it's Morse Code format
  * ASCII Text "SOS"  ->  Morse Code format "... --- ..." (DOT DOT DOT DASH DASH DASH DOT DOT DOT)
  * Reverse operation of the above is also available, from Morse Code to ASCII Text

This project has 3 dependecy:
  * libbst.a            General purpose Dictionary implementation using Binary Search Tree
  * libstackqueue.a     General purpose Stack and Queue data structure
  * liblinkedlist.a     General purpose Linked List data structure

These dependency projects and their source codes were already hosted to my GitHub account.

Code written for this project and for their dependency projects are ISO C90 compliant.

All the projects listed above including this one is compiled using GCC 4.8 32 bit (MinGW port)
