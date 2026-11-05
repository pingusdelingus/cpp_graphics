# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & run

macOS-only OpenGL 4.1 core-profile app (GLFW + GLAD). Requires Homebrew `glfw` (the makefile uses `brew --prefix` for include/lib paths).

- `make` — builds `opengl_app`
- `make clean` — removes `*.o` and `opengl_app`
- `./opengl_app` — run from this directory; shaders are loaded at runtime via relative paths `./vertex_shader.glsl` and `./fragment_shader.glsl`, so the working directory matters. Shaders are not compiled in: editing them needs no rebuild.

There are no tests or linter. Makefile quirks: `PVMat.o` is compiled with `$(CC)` (clang) and `InitShaders.o` with `$(CC) $(CXXFLAGS)`; clang picks C++ for `.cpp` files, but `-std=c++17` is not passed for `PVMat.cpp`. Headers are not tracked as dependencies, so run `make clean && make` after editing a `.hpp`.

## Architecture

Small learning project (following an Angel-style "rotating square" WebGL/OpenGL course; `rotatingSquare3.html` is the WebGL reference version of what `m.cpp` implements).

- `m.cpp` — `main()`: GLFW/GLAD init, shader setup, one VAO/VBO holding the square's `PV4` vertices, render loop drawing a `GL_TRIANGLE_FAN`. Global state (`theta`, `dummy`, `isClicked`, `clickX/Y`) is shared with `Callbacks.cpp` and uploaded each frame as uniforms (`theta` = rotation angle, `dummy` = direction flag; the loop increments or decrements `theta` by `dummy`). Also defines `canvas2clip` / `clip2canvas` constexpr matrices with a `static_assert` that they are inverses.
- `PVMat.hpp/.cpp` — hand-written math library: `PV2`/`PV3`/`PV4` vectors and `Mat` (4x4) with operator overloading, designed to be memory-compatible with GLSL `vec`/`mat` so `PV4` arrays can be passed directly to `glBufferData`. `Mat` has `constexpr` factories (`Mat::translation`, `Mat::scale`) used at compile time.
- `InitShaders.cpp/.hpp` — `init_shader(program, vert, frag, vertPath, fragPath)` reads, compiles and links the GLSL files.
- `Callbacks.cpp/.hpp` — GLFW key and mouse-button callbacks that mutate the globals declared in `m.cpp`.
- `rstdlib.hpp` — short type aliases (`u32`, `f32`, `b8`, ...) and size/min/max macros used throughout; prefer these over `std` types to match the codebase.
- `src/glad.c`, `include/glad`, `include/KHR` — vendored GLAD loader. OpenGL calls are written as `glad_glXxx(...)`.
- `cc` — an empty/helper file, not part of the build.
- Vertex shader rotates `vPosition` in the xy-plane by `theta`; fragment shader sets the color.
