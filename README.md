# C-Slash Programming
C-Slash (C/) is a tiny open-source programming language developed in C++. Codes in this repo are free to use and modify.
## Installation

Download the "c-slash.exe" (Windows) or "c-slash" (Linux/Mac).
(If the "c-slash" does not work, please download "c-slash.cpp" file and compile it by yourself.)

## Printing C-Slash information
```bash
c-slash --info
```

## Running the code file
The "main.csl" file can be found as an example in the repo.
```bash
c-slash <filename>.csl
```

## Comments
```bash
// This is a comment.
```
```bash
/* This is a comment
   written in more than
   just one line. */
```

## Standard output
```bash
output("Hello, World!");
```

## Standard input
The input() function accepts two arguments: variable name, and type (such as string, integer, float).
```bash
output("Enter a string:");
input(text, str);
```
```bash
output("Enter an integer:");
input(num, int);
```
```bash
output("Enter a float:");
input(float_num, float);
```

## Variables
A variable can be any of four types: string, integer, float, and boolean.

### Assigning
String
```bash
var name = "Codejapoe";
```
Integer
```bash
var age = 16;
```
Float
```bash
var net_worth = 7500000.00;
```
Boolean
```bash
var is_under_18 = true;
```

### Modifying
Please do not forget to put "var" keyword to modify a value.
```bash
var age = 15; // assign
var age = 16; // modify
```

## Arithmetic Operators
Addition:
```bash
var a = 3;
var b = 4;
var c = a + b + 3; 
// 10
```
```bash
var a = 3;
var a = a + 1;
// 4
```
Subtraction:
```bash
var a = 1;
var b = a - 2; 
// -1
```
Multiplication:
```bash
var a = 3;
var b = 4;
var c = a * b 
// 12
```
Division:
```bash
var a = 10;
var b = 2;
var c = a / b 
// 5
```

## Output
Variable:
```bash
var name = "Codejapoe";
output("Hello, I am ${name}.");
```
Expression:
```bash
var age = 16;
output("I'm turning ${age + 1}.");

>>> I'm turning 17.
```
Escape sequence:
```bash
output("\"Once upon a time, ...\"");

>>> "Once upon a time, ..."
```
```bash
output("\$1 = 3,400 MMK");

>>> $1 = 3,400 MMK
```
```bash
output("Hello, World!\\I am leaning C-Slash.");

>>> Hello, World!\I am leaning C-Slash.
```

### type() function
Friendly Reminder: This function only works with output() function.
```bash
var text = "hello"
output("Data \"${text}\" has the type of ${type(text)}.");

>>> Data "hello" has the type of str.
```
## Features

- Works on Windows, Mac, and Linux
- Fast and easy to set up and run
- Works with or without semi-colon in multiple code-lines (Semi-colons must be used in a single code-line.)

## Acknowledgements
I am not sure about the further development of this programming lanaguage. This is why I set this project as an open-source project. You may modify as you like and send the source code to my email address: codejapoe@gmail.com. You can further develope on if-else statement, loops, functions, and OOP. Anyone who updated this project will be defined as a contributor. Thank you kindly for supporting and if any error occurs, please fix it by yourself. Peace✌️

## C-Slash Information
- Version: 0.1 (Beta)
- Type: Interpreted Programming Lanaguage
- Developer: Codejapoe
- Started on: 25/09/2023
## Authors

- [@codejapoe](https://www.github.com/codejapoe)


## 🔗 Links
[![portfolio](https://img.shields.io/badge/my_portfolio-000?style=for-the-badge&logo=ko-fi&logoColor=white)](https://saunik.net/)
