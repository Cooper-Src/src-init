# Contributing

First of all, thank you for your interest in contributing to **src-init**.

Whether you're fixing a bug, improving documentation, or implementing a new feature, your contributions are greatly appreciated.

---

# Project Goals

`src-init` exists to make maintaining **src** registries simple, reliable, and reproducible.

The project is intentionally small and focused.

Its responsibilities are limited to:

- generating manifests
- maintaining registries
- communicating with repository providers
- validating registry data

It should **not** become a package manager.

Package installation belongs to **src**.

---

# Development Environment

## Requirements

- CMake 3.20+
- C++20
- Visual Studio Build Tools (MSVC)
- Git
- vcpkg

Required libraries:

- curl
- cJSON

---

# Building

Configure

```bash
cmake --preset default
```

Build

```bash
cmake --build build --config Release
```

Debug build

```bash
cmake --build build --config Debug
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

# Coding Style

The project follows a consistent C++ style.

## Language

- C++20
- Standard Library first
- Prefer modern language features

---

## Formatting

Opening braces appear on their own line.

```cpp
if (condition)
{
    doSomething();
}
```

Namespaces are never indented.

```cpp
namespace srcinit
{

}
```

---

## Naming

Classes

```cpp
ManifestWriter
RegistryBuilder
GitHubProvider
```

Methods

```cpp
build()
generate()
write()
```

Variables

```cpp
package
manifest
repository
```

Private members

```cpp
m_token
```

if required.

---

## Includes

Project headers first

```cpp
#include "manifest_writer.hpp"
```

Then standard library headers

```cpp
#include <filesystem>
#include <fstream>
```

Then third-party libraries

```cpp
#include <curl/curl.h>
```

---

# Design Principles

Every class should have one responsibility.

Good examples

```
HttpClient
```

Downloads HTTP resources.

```
ManifestWriter
```

Writes manifests.

```
RegistryBuilder
```

Builds registry indexes.

Avoid creating large classes that perform multiple unrelated tasks.

---

# Error Handling

Recoverable failures should return useful error messages.

Fatal failures should throw exceptions only when recovery is impossible.

Avoid silently ignoring errors.

---

# Documentation

Public classes should be documented.

New commands should be added to

```
docs/commands.md
```

New manifest fields should be documented in

```
docs/manifest-format.md
```

Architecture changes should update

```
docs/architecture.md
```

---

# Commit Messages

Keep commit messages short and descriptive.

Good

```
Add registry builder

Support archive manifests

Implement GitHub authentication

Improve manifest validation

Update documentation
```

Avoid

```
fixed stuff

update

changes
```

---

# Pull Requests

Before opening a pull request

- Build successfully
- Test the new feature
- Update documentation
- Keep commits focused
- Ensure formatting matches the project

Describe

- what changed
- why it changed
- whether documentation was updated

---

# Feature Requests

Features should align with the project's philosophy.

Good examples

- New repository providers
- Better validation
- Registry improvements
- Manifest improvements
- Better authentication

Poor examples

- Package installation
- Build systems
- Dependency resolution
- Binary package support

Those belong in **src**, not **src-init**.

---

# Reporting Bugs

Include

- src-init version
- operating system
- compiler
- steps to reproduce
- expected behaviour
- actual behaviour

If possible, include the generated manifest or relevant console output.

---

# Documentation Contributions

Documentation improvements are always welcome.

Examples

- Fixing grammar
- Clarifying workflows
- Adding examples
- Improving diagrams
- Expanding technical explanations

---

# Testing

When adding new functionality

- Build Debug
- Build Release
- Test with authenticated GitHub requests
- Test without authentication
- Test registry generation
- Verify generated manifests

---

# Philosophy

The best features are often the simplest.

When contributing, ask yourself

> Does this make maintaining a src registry easier?

If the answer is **yes**, it's probably a good addition.

If the answer is **no**, it may belong in another project.

---

# Questions

If you're unsure about a change, open an issue before beginning implementation.

Discussion is encouraged before large architectural changes.

---

Thank you for helping improve **src-init**.