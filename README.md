# CPP-MiniSpice-project

Use the Following Command to Run the CLI Version of the Project.
```bash
g++ -std=c++14 -D_USE_MATH_DEFINES main_CLI.cpp component.cpp circuit.cpp nodal_simulator.cpp analysis.cpp -I . -o minispice.exe
```
(Updating Command to new One to support the usage of M_PI)

For reference, this is the old Command: g++ -std=c++14 main_CLI.cpp component.cpp circuit.cpp nodal_simulator.cpp analysis.cpp -I. -o minispice

We also have made a different implementation for the same application. For a GUI under MiniSPICE_GUI.zip.
To run it just extract the zip and in a linux terminal reach the directory File/MiniSpice_frontend and run the following commands.
```bash
rm -rf build
cmake -S . -B  build
cmake --build build -j$(nproc)
./build/MiniSPICE

```


