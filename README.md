# CPP-MiniSpice-project

Use the Following Command to Run the CLI Version of the Project.
```bash
g++ -std=c++14 main_CLI.cpp component.cpp circuit.cpp nodal_simulator.cpp analysis.cpp -I. -o minispice
./minispice
```

We also have made a different implementation for the same application. For a GUI under MiniSPICE_GUI.zip.
To run it just extract the zip and in a linux terminal reach the directory File/MiniSpice_frontend and run the following commands.
rm -rf build
cmake -S . -B  build
cmake --build build -j$(nproc)
./build/MiniSPICE

to run this we have a few dependencies thye are cmake 
