# springSim

Real-time application for basic soft-body simulation using a spring-based model.

Uses my custom math library: [gMath](https://github.com/eqdiag/gMath)

All dependencies are self-contained in this project using git's submodule system.

## Installation

```
git clone https://github.com/eqdiag/springSim
cd springSim
mkdir build
cd build
cmake ..
make
```


## Keyboard Controls
  * `SPACE` Toggle Start/Pause simulation
  * `r` Reset simulation
  * `ESC` Exit program

## Mouse Controls
  * `mouseDrag` Rotates camera
  * `mouseScroll` Zoom camera in/out

## Physical Parameters
  *  `Time Step` Controls the time step per frame.
  *  `Stiffness`  Strength of spring force.
  *  `Dampening`  Strength of dampening spring force.
  *  `Gravity`  Controls strength of gravity force.
  *  `Mass`  Controls mass of all points of the mesh.


# Screenshots
![Simulation Paused](/screenshots/pause.PNG "Paused Simulation")
![Simulation Playing](/screenshots/play.gif "Playing Simulation")


## Potential Future Improvements
  * Mouse interactivity with soft-body mesh
  * A GPU-based simulation to handle larger meshes
                       
## Copyright and Attribution
Copyright (c) 2023 eqdiag. Released under the [MIT License](https://github.com/eqdiag/springSim/blob/main/LICENSE.md).
