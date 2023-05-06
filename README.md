## Platte

Platte is a C++ implementation of linear regression using stochastic gradient
descent. It contains a binary demo named `Platte` but the code was designed to
be used as a library.

### Build
```bash
cd src/
cmake ../CMakeLists.txt
make
```
### Run demo
```bash
./Platte
```
### Expected output
```bash
Demo 1
Prediction of x: 100, y : 250.495 
Demo 2
Prediction of x: 7, y : 13.9941 
```
Two data points not found in the dataset are predicted.

---
## Capstone project information

This is a Capstone option #1 project (project of your choice)

### Project structure

The `src` directory contains:
* `dataset.cpp` - responsible for reading CSV files and convert them to a suitable data structure.
* `linear_regression.cpp` - computes weights used for linear regression given a dataset.
* `main.cpp` - contains two demos on how to use dataset and linear regression together.

### Rubric points addressed

#### Loops, functions, I/O

| Criteria                                                                                       | Example                                                                       |  
|------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------|
| The project demonstrates an understanding of C++ functions and control structures.             | [code](https://github.com/daviduvalle/platte/blob/master/src/dataset.cpp#L23-L59) |
| The project reads data from a file and process the data, or the program writes data to a file. | [code](https://github.com/daviduvalle/platte/blob/master/src/dataset.cpp#L23-L59)                                                                               |
| The project accepts user input and processes the input.                                        | N/A                                                                           |

#### Object Oriented Programming

| Criteria                                                                                 | Example                                                                                                                                                                                        |  
|------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| The project uses Object Oriented Programming techniques.      | See [linear_regression.cpp](https://github.com/daviduvalle/platte/blob/master/src/linear_regression.cpp)  and [dataset.cpp](https://github.com/daviduvalle/platte/blob/master/src/dataset.cpp) |
| Classes use appropriate access specifiers for class members. | See [headers](https://github.com/daviduvalle/platte/tree/master/include)                                                                                                                       |
| Class constructors utilize member initialization lists.                                  | [code](https://github.com/daviduvalle/platte/blob/master/include/dataset.h#L15-L18)                                                                                                            |
| Classes abstract implementation details from their interfaces.     | See [linear_regression.cpp](https://github.com/daviduvalle/platte/blob/master/src/linear_regression.cpp)  and [dataset.cpp](https://github.com/daviduvalle/platte/blob/master/src/dataset.cpp) |
| Classes encapsulate behavior. | See [linear_regression.cpp](https://github.com/daviduvalle/platte/blob/master/src/linear_regression.cpp)  and [dataset.cpp](https://github.com/daviduvalle/platte/blob/master/src/dataset.cpp) |
| Classes follow an appropriate inheritance hierarchy.                                   | See [ml_algorithm](https://github.com/daviduvalle/platte/blob/master/include/ml_algorithm.h)                                                                                                   |
| Overloaded functions allow the same function to operate on different parameters.     | N/A                                                                                                                                                                                            |
| Derived class functions override virtual base class functions.| See [predict](https://github.com/daviduvalle/platte/blob/master/src/linear_regression.cpp#L136)                                                                                                |
| Templates generalize functions in the project.                                 | N/A                                                                                                                                                                                            |
