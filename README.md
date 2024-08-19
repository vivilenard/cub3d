# Preview

https://github.com/vivilenard/cub3d/assets/78664024/a181dbbc-7bf9-4786-8760-a2d49b082012

# Resources

- https://lodev.org/cgtutor/raycasting.html
- https://www.youtube.com/watch?v=gYRrGTC7GtA&t=2s&ab_channel=3DSage
- https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/

# Install

Prerequesite: You need to have glfw installed.

```bash
git clone git@github.com:vivilenard/cub3d.git
```
```bash
cd cub3d
```
Find the MLX variable withing the Makefile, e.g.: MLX=...-L "/opt/homebrew/Cellar/glfw/3.4/lib"

Now replace the path behind -L with your own path leading to your glfw directory. Then make it point to the /lib directory.

Finally build the MLX library by running this command in the /cub3d directory:
```bash
make build
```

# Run

```bash
make && ./cub3d maps/simple.cub
```
you can choose a different map by calling it from the /maps directory.

# Controls

Walk forwards/backwards: Arrow keys
Change view: W / A / S / D
Open doors: SPACE
Shoot: ENTER
