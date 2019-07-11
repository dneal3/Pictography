# Application Created by Derrick Neal, Daniel Loyd, and Holly Hardin

## Motivation
	
  Our main motivation was to learn the fundamental principles of cryptography. In particular, we wanted to expand our 
  knowledge of concealing data through encryption and decryption  so that interceptors cannot read a message - that is, 
  unless they possess the unique key to decrypt the message. We also wanted to integrate our knowledge of Cybersecurity 
  with material from our Computer Graphics class to create a unique program. In doing so, we challenged ourselves to 
  blend two courses together. To create this program, we used the Visualization Toolkit (VTK 8.1.2) software to generate 
  images from encrypted datasets and we used QT for creating the graphical user interface.

## Objectives
	
  The objective of this project was to write a program that successfully confused and diffused information from a 
  string across a set of pixels. We created an encryption algorithm that encrypted each letter of the plaintext 
  into data values between 0 and 1, which were written to a .vtk file. This data was used as color values for various 
  triangles, which were read and rendered by VTK to create a colorful image of triangles. The input parameters for the 
  encryption program is an image name, a message, and a vtk file name, and the output is a a vtk file, and a symmetric key. 
  This vtk file is used to render the image through the VTK toolkit. Using VTK allowed us to generate an image, while still 
  maintaining the information in a parsable format for decryption. The input parameters for the decryption program is a vtk 
  file name and a key, and the output of the encryption program is the original plaintext. 
	We successfully confused information by shifting the values used in encryption and changing it to a value between 0-1. 
  We also achieve confusion by changing values in the protocol depending on if the key is odd or even. Diffusion is achieved 
  by changing the positions of letters before transforming into colors, splitting the total value amongst three triangle 
  vertices, and changing which triangles a vertex is a part of. This diffuses the string info across the vertex set, 
  then the vertex set is diffused across the triangle set.

## Accomplishments

Before the midterm, we discussed and analyzed different ways to approach encryption and decryption rules. We also created a C++ program that takes in a string through the standard input stream and verifies that the string meets the predefined requirements. That is, the program checks that the length of the string is smaller than 999 characters and bigger than 0, and that all of the ASCII values are within range (minimum 32 and maximum 126). Test files have been created to make sure that the program exits when appropriate, and the program passes these tests.
After the midterm, we have advanced the program to be a fully functional program that has a graphical user interface, encrypts and decrypts correctly, and produces an image and a vtk file from an encrypted message. We’ve created (and enhanced) the encryption and decryption algorithms to confuse and diffuse information more effectively.  We’ve successfully integrated the encryption, decryption, manager, and validateData into a final program that has a user interface. 

## Demostration

A demonstration of the final build in action can be found at: https://www.youtube.com/watch?v=WVgc0yYsEbg

## References

- Slash, Black. 6 September 2018. URL: https://null-byte.wonderhowto.com/how-to/steganography-hide-secret-data-inside-image-audio-file-seconds-0180936/ 
 -Qt Documentation URL: https://doc.qt.io/ 

