# Authentication

`src-init` supports authentication using a GitHub Personal Access Token (PAT).

Authenticated requests receive GitHub's higher API rate limits, making manifest generation more reliable when working with large registries or generating many packages.

---

# Why Authentication?

GitHub applies rate limits to all API requests.

Unauthenticated requests are limited to approximately **60 requests per hour** per IP address.

Authenticated requests increase this limit to approximately **5,000 requests per hour** per user.

Using a Personal Access Token is strongly recommended if you regularly maintain a registry.

---

# Creating a Personal Access Token

1. Sign in to GitHub.
2. Open **Settings**.
3. Navigate to:

```
Developer settings
    └── Personal access tokens
            └── Tokens (classic)
```

4. Click **Generate new token (classic)**.
5. Give the token a descriptive name.

Example:

```
src-init
```

6. Set an expiration date.
7. No additional scopes are required for public repositories.
8. Generate the token.
9. Copy the token immediately.

GitHub will only display the token once.

---

# Logging In

Store your token locally:

```bash
src-init auth login
```

Example:

```text
Enter GitHub Personal Access Token:

ghp_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Token saved successfully.
```

---

# Checking Authentication Status

Display the current authentication status.

```bash
src-init auth status
```

Example:

```text
GitHub authentication

Status : Logged in
```

or

```text
GitHub authentication

Status : Not logged in
```

---

# Logging Out

Remove the stored token.

```bash
src-init auth logout
```

Example:

```text
GitHub token removed.
```

---

# Token Storage

`src-init` stores the token in the user's local configuration directory.

Example (Windows):

```
%LOCALAPPDATA%\src-init\config.json
```

Example configuration:

```json
{
    "github": {
        "token": "ghp_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
    }
}
```

---

# Security

The token never leaves your computer except when sent directly to the official GitHub API over HTTPS.

`src-init` does **not**

- upload your token anywhere else
- include it in generated manifests
- include it in registry files
- include it in package metadata

The token is only used to authenticate requests made to GitHub.

---

# API Usage

When a token is available, every GitHub API request automatically includes:

```
Authorization: Bearer <token>
```

If no token is configured, `src-init` falls back to unauthenticated requests.

No user interaction is required once a token has been saved.

---

# Troubleshooting

## Authentication still appears unauthenticated

Check the current status:

```bash
src-init auth status
```

If necessary, log in again:

```bash
src-init auth login
```

---

## Invalid token

If GitHub reports an authentication error:

1. Delete the stored token.

```bash
src-init auth logout
```

2. Generate a new Personal Access Token.
3. Log in again.

---

## Rate limit exceeded

If you encounter GitHub rate limit errors:

- Verify that you are logged in.
- Ensure your token has not expired.
- Generate a new token if necessary.

---

# Future Authentication Providers

Authentication currently supports GitHub only.

Future versions of `src-init` may support additional providers, including:

- GitLab
- Bitbucket
- Self-hosted Git services