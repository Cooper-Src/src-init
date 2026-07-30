# Architecture

This document describes the internal architecture of **src-init**, how its components interact, and the complete manifest generation pipeline.

---

# Overview

`src-init` is the official registry maintenance tool for the **src** ecosystem.

Its responsibilities are intentionally limited to:

- retrieving repository metadata
- generating package manifests
- authenticating with GitHub
- maintaining the registry index

It does **not**

- install packages
- build projects
- compile source code
- replace the `src` package manager

---

# High-Level Architecture

```
                    GitHub
                      │
                      │ HTTPS
                      ▼
                HttpClient
                      │
                      ▼
              GitHubProvider
                      │
          RepositoryMetadata
                      │
                      ▼
            ManifestGenerator
                      │
             PackageManifest
                      │
                      ▼
             ManifestWriter
                      │
                      ▼
             manifests/*.src
                      │
                      ▼
           RegistryBuilder
                      │
                      ▼
                index.json
```

---

# Project Structure

```
src-init/
├── include/
│   ├── command.hpp
│   ├── config.hpp
│   ├── github_provider.hpp
│   ├── http_client.hpp
│   ├── manifest_generator.hpp
│   ├── manifest_writer.hpp
│   ├── registry_builder.hpp
│   └── ...
│
├── src/
│   ├── command.cpp
│   ├── config.cpp
│   ├── github_provider.cpp
│   ├── http_client.cpp
│   ├── manifest_generator.cpp
│   ├── manifest_writer.cpp
│   ├── registry_builder.cpp
│   └── ...
│
├── docs/
└── tests/
```

---

# Components

---

## Command

The command layer is the application's entry point.

Responsibilities:

- Parse command line arguments
- Dispatch commands
- Display help
- Return exit codes

Supported commands include:

```
create
registry build
auth login
auth logout
auth status
help
version
```

---

## HttpClient

The HTTP client is a lightweight wrapper around libcurl.

Responsibilities:

- HTTPS requests
- Redirect handling
- User-Agent handling
- GitHub authentication headers

Every network request passes through this component.

---

## Config

The configuration system stores user configuration.

Currently this includes:

- GitHub Personal Access Token

Example:

```json
{
    "github": {
        "token": "ghp_xxxxxxxxx"
    }
}
```

Location:

```
%LOCALAPPDATA%\src-init\
```

---

## GitHubProvider

This component communicates with the GitHub REST API.

Responsibilities:

- Parse repository URLs
- Retrieve repository metadata
- Retrieve latest release
- Build archive URLs

Example:

```
https://github.com/raysan5/raylib
```

↓

```
RepositoryMetadata
```

---

## RepositoryMetadata

This is an internal model representing a repository.

Example fields:

```
name
description
version
license
homepage
owner
repository
defaultBranch
```

The metadata object is never written directly to disk.

Instead, it is transformed into a package manifest.

---

## ManifestGenerator

Converts

```
RepositoryMetadata
```

into

```
PackageManifest
```

Responsibilities:

- Build archive URLs
- Convert licenses
- Normalize metadata
- Generate source section

---

## ManifestWriter

Writes a PackageManifest to disk.

Example output:

```ini
name = raylib
version = 6.0

[source]
type = archive
url = ...
format = zip
```

---

## RegistryBuilder

Maintains the registry index.

Responsibilities:

- Scan manifests directory
- Sort packages
- Generate index.json
- Report package count

Example:

```
Packages : 136
```

---

# Data Flow

## Manifest Generation

```
Repository URL
       │
       ▼
GitHubProvider
       │
RepositoryMetadata
       │
       ▼
ManifestGenerator
       │
PackageManifest
       │
       ▼
ManifestWriter
       │
       ▼
package.src
```

---

## Registry Generation

```
manifests/
     │
     ▼
RegistryBuilder
     │
Sort alphabetically
     │
     ▼
Generate index.json
```

---

# Authentication Flow

```
auth login
      │
      ▼
Config
      │
Store PAT
      │
      ▼
HttpClient
      │
Authorization Header
      │
      ▼
GitHub API
```

If no token exists:

```
HttpClient
      │
      ▼
Unauthenticated request
```

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

# Design Goals

The architecture follows several principles.

## Small Components

Each class performs one task.

Examples:

- HttpClient downloads data
- ManifestWriter writes manifests
- RegistryBuilder builds registries

No component performs multiple unrelated tasks.

---

## Separation of Responsibilities

Repository metadata is never mixed with manifest generation.

```
GitHub
        │
RepositoryMetadata
        │
PackageManifest
```

Each layer has its own representation.

---

## Stateless Processing

Most components have no persistent state.

This makes them:

- easy to understand
- easy to test
- easy to replace

---

## Source-First Philosophy

Unlike traditional package managers, src-init always generates manifests that reference upstream source archives.

Example:

```
[source]
type = archive
url = https://github.com/.../archive/refs/tags/v1.0.zip
format = zip
```

No Git cloning information is stored.

---

# Future Architecture

Future releases may introduce additional providers.

```
             Provider
                ▲
      ┌─────────┼─────────┐
      │         │         │
 GitHub     GitLab    Bitbucket
```

Each provider will produce the same:

```
RepositoryMetadata
```

allowing the rest of the application to remain unchanged.

---

# Summary

The architecture intentionally keeps every layer independent.

```
GitHub
   │
HttpClient
   │
GitHubProvider
   │
RepositoryMetadata
   │
ManifestGenerator
   │
PackageManifest
   │
ManifestWriter
   │
RegistryBuilder
```

This separation makes the project easy to maintain, extend, and test while keeping each component focused on a single responsibility.