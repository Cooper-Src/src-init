# src-init

> Automatically generate `.src` package manifests from GitHub repositories.

`src-init` is a companion tool for the **src** package manager. It connects to the GitHub API, collects repository metadata, and generates ready-to-use `.src` manifests with minimal user input.

---

## Features

- Generate `.src` manifests from any public GitHub repository
- Automatically detect:
  - Package name
  - Latest release version
  - Description
  - License
  - Homepage
  - Default branch
- Output manifests compatible with the `src` package manager
- Fast, lightweight, and written entirely in modern C++

---

## Example

Generate a manifest:

```bash
src-init create https://github.com/raysan5/raylib
```

Output:

```ini
name = raylib
version = 6.0
description = A simple and easy-to-use library to enjoy videogames programming

[source]
type = git
url = https://github.com/raysan5/raylib.git
branch = master

[license]
name = Zlib

[homepage]
url = http://www.raylib.com
```

---

## Installation

### Requirements

- CMake 3.20+
- Visual Studio Build Tools (MSVC)
- C++20 compiler
- vcpkg

### Dependencies

```
curl
cjson
```

Install them with vcpkg:

```bash
vcpkg install curl:arm64-windows
vcpkg install cjson:arm64-windows
```

Configure:

```bash
cmake --preset default
```

Build:

```bash
cmake --build build
```

---

## Usage

### Create a manifest

```bash
src-init create <github-repository>
```

Example:

```bash
src-init create https://github.com/raysan5/raylib
```

---

### Help

```bash
src-init help
```

---

### Version

```bash
src-init version
```

---

## Project Structure

```
src-init/
├── include/
├── src/
├── docs/
├── examples/
├── tests/
├── third_party/
├── CMakeLists.txt
└── README.md
```

---

## Roadmap

### v0.1

- [x] GitHub repository parsing
- [x] GitHub API integration
- [x] Metadata extraction
- [x] Latest release detection
- [x] Default branch detection
- [x] Manifest generation
- [x] Manifest writing

### v0.2

- [ ] Detect build systems
- [ ] Parse CMake projects
- [ ] Dependency detection
- [ ] Automatic language detection
- [ ] Manifest validation

### Future

- [ ] Support GitLab
- [ ] Support Bitbucket
- [ ] Custom manifest templates
- [ ] Repository analysis
- [ ] Batch generation
- [ ] Interactive mode

---

## About src

`src-init` is part of the **src** ecosystem.

While **src** installs packages from source, **src-init** creates the manifests that describe how those packages should be installed.

```
GitHub Repository
        │
        ▼
   src-init
        │
        ▼
    package.src
        │
        ▼
       src
```

---

## Contributing

Contributions are welcome.

If you have an idea, found a bug, or want to add support for additional build systems or package sources, feel free to open an issue or submit a pull request.

---

## License

This project is licensed under the MIT License.
