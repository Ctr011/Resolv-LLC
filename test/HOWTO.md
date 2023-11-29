# Using Google Test with CMake and Visual Studio Code

This guide outlines the steps to use Google Test with CMake and Visual Studio Code for testing your C++ code.

## Prerequisites

- CMake installed on your system.
- Visual Studio Code with the C/C++ extension installed.
- Google Test source code in your project directory or installed globally.

## Project Structure

Assuming the following project structure:

project-root/
|-- CMakeLists.txt
|-- main.cpp
|-- mymath.cpp
|-- mymath.h
|-- tests/
| |-- CMakeLists.txt
| |-- tests.cpp
|-- build/
|-- googletest/


## Steps

### 1. Navigate to the Build Folder

Open a terminal and navigate to the build folder in your project.

```cd path/to/your/project/build```

### 2. Add Tests

To add tests:

 - Create a new source file in the tests/ directory. For example, test_mynewfeature.cpp.
 - Write your test cases using Google Test macros (e.g., TEST, EXPECT_EQ, etc.).
 - Update the tests/CMakeLists.txt to include the new test file.

#### Example:
```
#include <gtest/gtest.h>

TEST(MyNewFeature, Test1) {
    // Your test logic here
    EXPECT_EQ(1 + 1, 2);
}

TEST(MyNewFeature, Test2) {
    // Your test logic here
    EXPECT_TRUE(true);
}
```

<b>Test Types</b>: http://google.github.io/googletest/primer.html

 ### 3. Run CMake

Run CMake to generate build files.

```
cmake ..
````

### 4. Run Tests in Visual Studio Code
In Visual Studio Code:

- Open your project folder.
- Press Ctrl + Shift + P to open the command palette.
- Type and select "CMake: Run Tests".
- This command will build and run your tests, and the output will be displayed in the Visual Studio Code output panel.

<b>NOTE:</b> Ensure that your CMakeLists.txt includes the necessary configurations for Google Test, and the necessary include and library directories are specified.
