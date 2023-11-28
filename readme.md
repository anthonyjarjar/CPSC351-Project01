# Project 1

## Overview

This project consists of C scripts designed to perform specific tasks using data from input files. The scripts leverage the Ubuntu C compiler and are meant to be compiled and run on a Linux environment.

## Team Information

- **Team Member:** Anthony Jarjour
- **Team Number:** 1

## Input Files

### 1. locations.txt

This file contains latitude and longitude coordinates for different locations.

### 2. string.txt

This file contains strings of fruit names.

## Script Rundown

1. Shell Script
This interactive shell script allows users to execute commands entered in the terminal. It uses fork() and exec() functions to create child processes for command execution and waits for their completion.

2. Linear Search Script
This C script performs a parallelized linear search on a list of strings, using multiple processes to search for a specified key. It reads input from a file, dividing the search task among different processes and reports whether the key was found or not.

3. Weather API Script
This C script fetches weather data from an API for multiple locations in parallel. It utilizes fork() to create child processes for each location, fetching weather information and saving it to individual JSON files.

4. Weather API Script with Output Redirection
Similar to the previous weather script, this version redirects the standard output and error of child processes to /dev/null. It demonstrates the use of exec() to replace the child process's image with a new program.

## Compilation 

After using gcc to compile each file simply run the output file that you created using the -o flag, the output will either be displayed in the terminal or saved into a file in the same directory

## Usage

```bash
gcc -o shell shell.c
./shell