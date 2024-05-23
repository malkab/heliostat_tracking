# heliostat_tracking
Basic library to simulate all types of two axis heliostat trackers.



# Development Environment Setup (for Linux)

If using Visual Studio Code, there is a **.devcontainer** definition to setup the development environment.

This project uses the GoogleTest Git repo submodule. To init:

```shell
git submodule init
git submodule update
```

CMAKE 3.39.3 or higher is required to build the project. To build the project:

```shell
cmake -S . -B build
cd build
make
```

Test the **bluesolar_angles** executable:

```shell
./bluesolar_angles 1.9 20.65 2.18 0.0 0.0 20.0 180 20

# Output:
28.3413, 2.14284, 0.446065, 0.38641
```
