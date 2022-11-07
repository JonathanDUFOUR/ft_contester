# ft_contester
![Project illustration](./illustration.png "Objection !")<br>
This is my own bunch of tests for the 42 School ft_containers project.<br>
They are designed to be run on a supposed finished project (for example, during a correction, or before set as finished).

## Configuration
Once you've cloned the repository, make sure to edit the `INC_DIR` variable in the Makefile to your own header files location.<br>
Then, because the project allowed us to name some header files as we wish, please also edit each relative path in the `private/headers.hpp` file.<br>

## Usage
Once you've configured the previous files, run the following command:
```
make unit_test.out
./unit_test.out
```

If you want to run tests with valgrind, and have the debug flag `-g` active, run:
```
make re DEBUG=1
valgrind ./unit_test.out
```
