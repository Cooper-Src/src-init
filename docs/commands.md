# Commands

This document describes every command currently supported by **src-init**.

---

# Overview

```
src-init create
src-init registry build
src-init auth login
src-init auth logout
src-init auth status
src-init help
src-init version
```

---

# create

Generates a `.src` manifest from a public GitHub repository.

## Syntax

```bash
src-init create <repository>
```

## Example

```bash
src-init create https://github.com/raysan5/raylib
```

## Output

```
Created
C:\src-registry\manifests\raylib.src
```

The generated manifest is written directly into the registry's `manifests` directory.

Example output:

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

# registry build

Scans every manifest inside the registry and regenerates the registry index.

## Syntax

```bash
src-init registry build
```

## Output

```
Registry index generated successfully.

Packages : 136
Output   : C:\src-registry\index.json
```

## What it does

- Scans every `.src` file
- Sorts package names alphabetically
- Removes duplicates automatically
- Rebuilds `index.json`

The resulting file is used by the `src` package manager when updating its registry.

---

# auth login

Stores a GitHub Personal Access Token.

Authenticated requests receive GitHub's higher API rate limits.

## Syntax

```bash
src-init auth login
```

Example:

```
Enter GitHub Personal Access Token:

ghp_xxxxxxxxxxxxxxxxxxxxx
```

The token is securely stored in the local configuration directory.

---

# auth logout

Deletes the stored GitHub Personal Access Token.

## Syntax

```bash
src-init auth logout
```

Output:

```
GitHub token removed.
```

---

# auth status

Displays the current authentication status.

## Syntax

```bash
src-init auth status
```

Possible output:

```
GitHub authentication

Status : Logged in
```

or

```
GitHub authentication

Status : Not logged in
```

---

# help

Displays the built-in command reference.

## Syntax

```bash
src-init help
```

---

# version

Displays the current version of src-init.

## Syntax

```bash
src-init version
```

Example

```
src-init v0.3.0
```

---

# Exit Codes

| Code | Meaning |
|------|---------|
| 0 | Success |
| 1 | Invalid arguments |
| 2 | Network error |
| 3 | Authentication failed |
| 4 | Manifest generation failed |
| 5 | Registry build failed |

---

# Typical Workflow

Generate a package:

```bash
src-init create https://github.com/raysan5/raylib
```

Rebuild the registry:

```bash
src-init registry build
```

Commit the changes:

```bash
git add .
git commit -m "Add raylib"
git push
```

Clients can now retrieve the updated registry using:

```bash
src registry update
```