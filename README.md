# Sorting Visualizer in C

This is a sorting visualizer program written in C using the SDL2 library.
It allows you to see how different sorting algorithms work
by visualizing the sorting process in real-time.

This project was inspired by
[sorting algorithms visualizer](https://www.youtube.com/watch?v=kPRA0W1kECg)
videos on youtube.

## Installation

### Prerequesites

To install and run the program,
you will need to have the SDL2 library installed on your system.
You can download the library from the official SDL website [here](https://wiki.libsdl.org/SDL2/Installation).

#### Windows

1. Download the SDL2 development libraries from the official website: https://github.com/libsdl-org/SDL/releases/
2. Extract the downloaded archive and navigate to the "lib" folder.
3. Copy the contents of the "lib" folder to your project's lib directory.
4. Copy the contents of the "include" folder to your project's include directory.

#### MacOS

Installing through homebrew

```bash
brew install sdl2
```

#### GNU/Linux

##### Ubuntu/Debian

```bash
sudo apt-get install libsdl2-dev
```

##### CentOS/Fedora

```bash
sudo dnf install SDL2-devel
```

##### Arch Linux

```bash
sudo pacman -S sdl2
```

##### Gentoo Linux

```bash
sudo emerge -av media-libs/libsdl2
```

### Compile and run the project

Once you have downloaded and installed the SDL2 library,
you can clone this repository and run the program using the following commands:


```bash
git clone https://github.com/ShellTux/Sorting-Visualizer-in-C
cd Sorting-Visualizer-in-C
make
```

`make` compiles and run the executable.
After compiling to just run the program, just:

```bash
./main.o
```

## Usage

The following sorting algorithms are currently supported by the program:

1. Bubble Sort
2. Cocktail Sort
3. Comb Sort
4. Cycle Sort
5. Gnome Sort
6. Heap Sort
7. Insertion Sort
8. Merge Sort
9. Odd-Even Sort
10. Quick Sort
11. Radix Sort
12. Selection Sort
13. Shell Sort

At the moment, there are 2 ways to methods to visualize sorting:

1. Bars

![Bars](images/sorting-bars.gif)

2. Colored Circle

![Colored Circle](images/sorting-colored-circle.gif)

## Contributing

If you would like to contribute to this project,
please fork the repository and submit a pull request.
