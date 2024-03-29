# simpleGL
Yet another opengl wrapper in C++

#### Example
```c++
#include <simpleGL.hpp>

int main()
{
    // Initialize sgl
    // This initializes glew and glfw and sets all the defaults
    sgl::init();

    // Create an 800x800 window with the name "SimpleGL Window"
    // The `true` here starts the window 
    // otherwise would have to explicitly initialize window
    sgl::Window window("SimpleGL Window", 800, 800, true);
    window.set_exit_key(GLFW_KEY_Q); // Self explanatory

    // Create a renderable rectangle with dimensions 0.5x0.5
    // Give it an initial position of (0, 0)
    sgl::Rectangle rectangle(glm::vec2(0, 0), 0.5, 0.5);

    // Start the main loop which runs the given lambda every tick 
    window.loop([&] {
        // Render the rectangle every tick
        rectangle.render();
    });

    return 0;
}
```
Pretty Simple right?

## Installation

### Dependencies

- cmake
- opengl 3.3+
- glew
- glfw

You can install these with your OS' respective package managers easily.

#### Linux
Run the following commands -
```
git clone https://github.com/vaimer9/simpleGL
cd simpleGL
./install.sh
```
The install script simply builds the dynamic library and copies the headers to their respective
targets.
#### Windows
TODO

## Project's Aim
The above example may feel a bit too opaque but this project's aim is to provide multiple levels of abstraction so that the user is free to chose the amount of control they want. You can always mix and match. There are several abstract classes for you to implement and create your own parts. This approach may feel bloated and thats true. The DLL or .so file for this project may be bloated but the application built won't be.

Another thing is transparency with the state. If there's going to be a triangle on the screen you need to create some variables for it, the API is not designed to have a single function call for drawing/rendering. There will be a setup phase and a rendering/update phase in your program and all future API updates will follow this code style. If you do not preffer this an alternative would be [raylib](https://github.com/raysan5/raylib).

### Track Progress
You can track the progress of the project on this [trello board](https://trello.com/b/dqzaBc15/graphic#). 
