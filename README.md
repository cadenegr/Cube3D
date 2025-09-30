# Cub3D - 3D Raycasting Engine

<p align="center">
  <img src="https://img.shields.io/badge/School-42-black?style=flat-square" />
  <img src="https://img.shields.io/badge/Language-C-blue?style=flat-square" />
  <img src="https://img.shields.io/badge/Graphics-MinilibX-green?style=flat-square" />
  <img src="https://img.shields.io/badge/Grade-Completed-success?style=flat-square" />
</p>

A **3D raycasting engine** inspired by classic games like Wolfenstein 3D, built as part of the 42 School curriculum. This project implements real-time 3D rendering using raycasting techniques, texture mapping, and player interaction in a maze-like environment.

![Cub3D Demo](https://via.placeholder.com/800x400/000000/FFFFFF?text=Cub3D+Screenshot)

## ✨ Features

- **Real-time 3D Rendering**: Raycasting algorithm for pseudo-3D visualization
- **Texture Mapping**: Wall textures based on cardinal directions (North, South, East, West)
- **Player Movement**: Smooth WASD movement with mouse-look controls
- **Map Parsing**: Custom `.cub` file format for level configuration
- **Color Customization**: Configurable floor and ceiling colors
- **Error Handling**: Comprehensive validation and user-friendly error messages
- **Performance Optimized**: 60+ FPS rendering at 1920x1080 resolution

## 🛠️ Technical Implementation

### Raycasting Algorithm

The engine uses the **DDA (Digital Differential Analyzer)** algorithm to cast rays from the player's position:

1. **Ray Direction Calculation**: For each screen column, calculate ray direction based on player angle and FOV
2. **Grid Traversal**: Step through the map grid until hitting a wall
3. **Distance Calculation**: Compute perpendicular distance to avoid fisheye effect
4. **Wall Height**: Project 3D wall height based on distance
5. **Texture Mapping**: Sample appropriate texture based on wall orientation

### Key Components

- **Map Parser**: Validates and loads `.cub` configuration files
- **Raycasting Engine**: Core rendering logic with DDA algorithm
- **Texture System**: XPM texture loading and mapping
- **Input Handler**: Keyboard and window event management
- **MLX Integration**: Graphics rendering using MinilibX library

## 🚀 Quick Start

### Prerequisites

- **GCC** compiler with C99 support
- **Make** build system
- **X11 development libraries** (Linux)
- **MinilibX** (included as submodule)

### Installation

```bash
# Clone the repository
git clone https://github.com/cadenegr/Cube3D.git
cd Cube3D

# Build the project
make

# Run with a map file
./cub3D maps_sub/1.cub
```

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `ESC` | Exit game |

## 📁 Project Structure

```
Cube3D/
├── src/
│   ├── main/           # Entry point and initialization
│   ├── parse_map/      # Map file parsing and validation
│   ├── 3d/            # Raycasting and rendering engine
│   ├── keypress/      # Input handling
│   └── line/          # Mathematical utilities
├── include/           # Header files
├── maps_sub/         # Example map files
├── tex/              # Texture assets (XPM format)
├── test/             # Comprehensive testing suite
├── libft/            # Custom C library
└── minilibx-linux/   # Graphics library
```

## 🗺️ Map File Format

Cub3D uses a custom `.cub` file format for level configuration:

```
NO ./tex/north_texture.xpm
SO ./tex/south_texture.xpm
WE ./tex/west_texture.xpm
EA ./tex/east_texture.xpm

F 220,100,0
C 225,30,0

111111111111
100000000001
100N00000001
100000000001
111111111111
```

### Configuration Elements

- **NO/SO/WE/EA**: Texture paths for cardinal directions
- **F**: Floor color (RGB values 0-255)
- **C**: Ceiling color (RGB values 0-255)
- **Map Grid**: 
  - `1`: Wall
  - `0`: Empty space
  - `N/S/E/W`: Player spawn point and initial direction

## 🧪 Testing Suite

The project includes a comprehensive testing framework with both automated and interactive tests:

```bash
# Quick test launcher (recommended)
./test/scripts/test_launcher.sh

# Automated tests only (validation, error handling)
./test/scripts/run_tests.sh

# Interactive tests only (manual gameplay testing)
./test/scripts/interactive_tests.sh
```

### Automated Tests
- Argument validation
- Map format validation  
- Texture loading verification
- Color validation (RGB 0-255)
- Error handling coverage
- Edge case detection

### Interactive Tests
- Manual gameplay verification
- Movement and controls testing
- Rendering performance evaluation
- User experience validation
```

### Test Coverage

- ✅ Argument validation (count, file extension)
- ✅ Map parsing (missing player, open maps, invalid characters)
- ✅ Texture validation (file existence, format)
- ✅ Color validation (RGB range 0-255)
- ✅ Error message clarity and consistency

## 🎯 Implementation Highlights

### Performance Optimizations

- **Efficient Ray Casting**: Optimized DDA algorithm for minimal computational overhead
- **Texture Caching**: Pre-loaded texture data for fast access
- **Memory Management**: Careful allocation and cleanup to prevent leaks

### Error Handling Enhancements

- **Input Validation**: Comprehensive checks for file format, colors, and map structure
- **User-Friendly Messages**: Clear error descriptions with context
- **Graceful Failure**: Proper cleanup on errors

### Code Quality

- **Modular Design**: Separated concerns with clean interfaces
- **42 Norm Compliance**: Follows strict coding standards
- **Comprehensive Testing**: Extensive test coverage for reliability

## 🔧 Build System

The project uses a sophisticated Makefile with:

- **Dependency Management**: Automatic header dependency tracking
- **Submodule Integration**: libft and MinilibX compilation
- **Platform Detection**: Linux-specific optimizations
- **Debug Support**: Optional debug flags for development

```bash
# Available targets
make          # Build the project
make clean    # Remove object files
make fclean   # Full cleanup
make re       # Rebuild from scratch
make debug    # Build with debug flags
```

## 📊 Technical Specifications

| Specification | Value |
|---------------|-------|
| **Resolution** | 1920x1080 (configurable) |
| **Frame Rate** | 60+ FPS |
| **FOV** | 66° (configurable) |
| **Texture Format** | XPM |
| **Map Size** | Variable (validated) |
| **Color Depth** | 24-bit RGB |

## 🎓 Learning Outcomes

This project demonstrates proficiency in:

- **Computer Graphics**: 3D rendering and raycasting algorithms
- **C Programming**: Low-level memory management and optimization
- **Mathematics**: Vector operations, trigonometry, and linear algebra
- **Software Architecture**: Modular design and clean code principles
- **Testing**: Comprehensive validation and edge case handling
- **Graphics Libraries**: MinilibX integration and event handling

## 🚧 Future Enhancements

- [ ] **Minimap Display**: Real-time map overview
- [ ] **Sprite Support**: Animated objects and enemies
- [ ] **Sound System**: 3D positional audio
- [ ] **Level Editor**: Visual map creation tool
- [ ] **Multi-level Support**: Level progression system
- [ ] **Advanced Textures**: Floor and ceiling texturing

## 📄 License

This project is part of the 42 School curriculum and follows the school's academic guidelines.

## 🤝 Contributing

While this is an academic project, feedback and suggestions are welcome! Please feel free to:

- Report bugs or issues
- Suggest improvements
- Share your own implementations

---

**Developed as part of the 42 School curriculum - September 2024**

*Transforming pixels into immersive 3D experiences, one ray at a time.*
