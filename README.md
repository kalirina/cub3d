#  cub3D

![42](https://img.shields.io/badge/42-Project-black?style=flat-square&logo=42)

## 📖 Overview

**cub3D** is a 3D first-person maze explorer built entirely in C using the **miniLibX** graphics library. The project uses the mathematical concept of **Raycasting** to render a 3D perspective from a 2D map, replicating the visual style of early 90s classic games like *Wolfenstein 3D* and *Doom*.

### ✨ Features
* **Raycasting Engine:** Computes 3D graphics on a 2D grid in real-time.
* **Custom Textures:** Different textures for North, South, East, and West facing walls.
* **RGB Parsing:** Parses floor and ceiling colors from `.cub` map files.
* **Collision Detection:** Smooth sliding against walls without clipping.
* **Clean Parsing:** Robust `.cub` file validation and map closure checking.

### 🚀 Bonus Features Included
* **Interactive Doors:** Approach a door and press `E` to seamlessly open/close it.
* **Minimap:** A dynamic, scaled minimap rendered in real-time on the HUD.
* **Mouse Camera Control:** Rotate the camera smoothly using mouse movements.
* **Advanced Collisions:** Proper collision handling for doors and map borders.

---

## 🛠️ Installation & Compilation

### Requirements (Linux)
Since this project uses `minilibx-linux`, you will need to install the required X11 and BSD dependencies before compiling:
```bash
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# Clone the repository
git clone [https://github.com/yourusername/kalirina-cub3d.git](https://github.com/yourusername/kalirina-cub3d.git)
cd kalirina-cub3d

# Compile the mandatory part
make

# OR: Compile the bonus version (includes minimap, mouse support, and doors)
make bonus

# Run standard map
./cub3d maps/subject.cub

# Run a map with bonus features (doors)
./cub3d maps/bonus.cub
