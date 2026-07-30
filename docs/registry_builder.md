# Registry Builder

The registry builder automatically generates the registry index used by the **src** package manager.

Rather than maintaining `index.json` manually, `src-init` scans every package manifest in the registry and generates a fresh index.

This guarantees that the registry index always matches the manifests present in the repository.

---

# Overview

The registry consists of two parts:

```
src-registry/
├── index.json
└── manifests/
    ├── raylib.src
    ├── fmt.src
    ├── glfw.src
    └── ...
```

Only the contents of the `manifests` directory should ever be edited manually.

`index.json` is generated automatically.

---

# Building the Registry

Generate a new registry index:

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

# Build Process

When executed, the registry builder performs the following steps.

## 1. Scan

The builder scans the registry manifest directory.

Example:

```
C:\src-registry\manifests
```

Every file ending with

```
.src
```

is collected.

---

## 2. Sort

Package filenames are sorted alphabetically.

For example

```
fmt.src
raylib.src
zlib.src
```

Sorting ensures that the registry is deterministic and Git diffs remain clean.

---

## 3. Generate

A new `index.json` is generated.

Example:

```json
{
    "version": 1,
    "manifests": [
        "fmt.src",
        "glfw.src",
        "raylib.src",
        "zlib.src"
    ]
}
```

Each manifest occupies its own line for readability.

---

## 4. Save

The generated registry is written to

```
src-registry/index.json
```

Any previous version is replaced.

---

# Registry Format

The registry index contains two fields.

## version

```json
"version": 1
```

The registry format version.

This is **not** the package version.

It only identifies the registry schema.

---

## manifests

```json
"manifests": [
    "fmt.src",
    "raylib.src",
    "zlib.src"
]
```

An alphabetically sorted list of every manifest contained in the registry.

---

# Registry Workflow

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
```

---

# Why Generate the Registry?

Automatically generating the registry provides several advantages.

- No duplicate entries
- No missing packages
- Alphabetical ordering
- Consistent formatting
- Easier Git reviews
- No manual maintenance

---

# Typical Workflow

Create a package:

```bash
src-init create https://github.com/raysan5/raylib
```

Rebuild the registry:

```bash
src-init registry build
```

Commit:

```bash
git add .
git commit -m "Add raylib"
git push
```

The updated registry is immediately available to every `src` client after running:

```bash
src registry update
```

---

# Best Practices

Always regenerate the registry after:

- adding a package
- removing a package
- renaming a package

Never edit `index.json` manually.

If the registry appears incorrect, simply run:

```bash
src-init registry build
```

to regenerate it.

---

# Future Improvements

Planned enhancements include:

- Registry validation
- Duplicate manifest detection
- Manifest integrity checks
- Package statistics
- Registry schema upgrades
- Automatic version incrementing