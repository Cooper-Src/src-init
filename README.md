# src-init

> The official registry maintenance tool for the **src** ecosystem.

`src-init` automates the creation and maintenance of `.src` package manifests used by the **src** package manager.

Given a public GitHub repository, `src-init` retrieves repository metadata using the GitHub API, generates a complete manifest, and can automatically rebuild the registry index used by `src`.

---

# Features

- Generate `.src` manifests from public GitHub repositories
- Automatically detect:
  - Package name
  - Latest release version
  - Description
  - License
  - Homepage
- Generate archive-based manifests compatible with **src**
- Automatically rebuild `index.json`
- GitHub Personal Access Token support
- Lightweight C++20 implementation
- No external scripting required

---

# Installation

## Requirements

- CMake 3.20+
- C++20 compiler
- Visual Studio Build Tools (MSVC)
- vcpkg

## Dependencies

```
curl
cjson
```

Install with vcpkg:

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
cmake --build build --config Release
```

---

# Quick Start

Generate a package manifest:

```bash
src-init create https://github.com/raysan5/raylib
```

Build the registry index:

```bash
src-init registry build
```

Commit and push your registry:

```bash
git add .
git commit -m "Add raylib"
git push
```

---

# Commands

## Create

Generate a manifest from a GitHub repository.

```bash
src-init create <repository>
```

Example:

```bash
src-init create https://github.com/raysan5/raylib
```

---

## Registry

Rebuild the registry index.

```bash
src-init registry build
```

Example output:

```text
Registry index generated successfully.

Packages : 136
Output   : C:\src-registry\index.json
```

---

## Authentication

Login using a GitHub Personal Access Token.

```bash
src-init auth login
```

Show authentication status.

```bash
src-init auth status
```

Remove the stored token.

```bash
src-init auth logout
```

---

## Help

```bash
src-init help
```

---

## Version

```bash
src-init version
```

---

# Example Manifest

```ini
name = raylib
version = 6.0
description = A simple and easy-to-use library to enjoy videogames programming

[source]
type = archive
url = https://github.com/raysan5/raylib/archive/refs/tags/6.0.zip
format = zip

[license]
name = Zlib

[homepage]
url = https://www.raylib.com
```

---

# Workflow

```
GitHub Repository
        │
        ▼
   src-init create
        │
        ▼
   package.src
        │
        ▼
src-registry/manifests
        │
        ▼
src-init registry build
        │
        ▼
    index.json
        │
        ▼
    Git Commit
        │
        ▼
   GitHub Pages
        │
        ▼
 src registry update
        │
        ▼
 Local Registry Cache
        │
        ▼
     src install
```

---

# Project Structure

```
src-init/
├── include/
├── src/
├── docs/
├── tests/
├── CMakeLists.txt
├── README.md
└── LICENSE
```

---

# Documentation

Additional documentation can be found in the `docs` directory.

- Architecture
- Commands
- Authentication
- Registry Builder
- Manifest Format

---

# Project Philosophy

`src-init` exists for one purpose:

> Maintain high-quality registries for the **src** package manager.

It intentionally does **not**

- install packages
- build projects
- compile source code
- replace package managers

Those responsibilities belong to **src**.

---

# Roadmap

## Current

- GitHub metadata retrieval
- Manifest generation
- Registry index generation
- Authentication
- Archive-based manifests

## Planned

- GitLab support
- Bitbucket support
- Batch manifest generation
- Manifest validation
- Interactive mode
- Custom templates

---

# Contributing

Contributions are welcome.

Please read **CONTRIBUTING.md** before submitting pull requests.

---

# License

This project is licensed under the MIT License.