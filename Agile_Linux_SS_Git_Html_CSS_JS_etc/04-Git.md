# Git & Source Control Management — From Basics to Expert

---

## 1. Source Control Management (SCM)

### What is SCM?

**Source Control Management** (also called Version Control) is the practice of tracking and managing changes to code. It allows multiple developers to work on the same codebase simultaneously without conflicts.

### Types of Version Control

| Type | Description | Examples |
|------|-------------|---------|
| **Local** | Changes tracked on local machine only | RCS |
| **Centralized (CVCS)** | Single central server, everyone commits there | SVN, CVS, Perforce |
| **Distributed (DVCS)** | Every developer has a full copy of the repo | **Git**, Mercurial |

### Under the Hood: Why Git is Distributed

```
Centralized (SVN):                 Distributed (Git):
                                   
   ┌──────────┐                    ┌──────────┐
   │  Central  │                   │  Remote   │
   │  Server   │                   │  (GitHub) │
   └────┬─────┘                    └──┬──┬──┬──┘
        │                             │  │  │
   ┌────┴────┐                ┌──────┘  │  └──────┐
   │         │                │         │         │
┌──┴──┐  ┌──┴──┐          ┌──┴──┐  ┌──┴──┐  ┌──┴──┐
│Dev A│  │Dev B│          │Dev A│  │Dev B│  │Dev C│
│(no  │  │(no  │          │FULL │  │FULL │  │FULL │
│copy)│  │copy)│          │REPO │  │REPO │  │REPO │
└─────┘  └─────┘          └─────┘  └─────┘  └─────┘

In Git, each developer has the ENTIRE repository history locally.
You can commit, branch, merge — all OFFLINE.
```

---

## 2. Git Fundamentals

### What is Git?

Git is a **distributed version control system** created by **Linus Torvalds** in 2005 (the creator of Linux). It tracks changes in source code during software development.

### Under the Hood: How Git Stores Data

Git doesn't store diffs — it stores **snapshots**:

```
Commit 1:    Commit 2:    Commit 3:
┌────────┐  ┌────────┐  ┌────────┐
│ file A ──→│ file A'──→│ file A'│  (A' = changed, A' = unchanged)
│ file B │  │ file B │  │ file B'│
│ file C │  │ file C'│  │ file C'│
└────────┘  └────────┘  └────────┘

Each commit is a SNAPSHOT of all files at that moment.
Unchanged files are stored as REFERENCES (pointers) to previous versions.
Git uses SHA-1 hashes to identify every object (commit, tree, blob).
```

### Git Objects (Internal Architecture)

```
.git/objects/
├── blob    → File content (the actual data)
├── tree    → Directory listing (maps names to blobs/trees)
├── commit  → Snapshot + metadata (author, message, parent commit)
└── tag     → Named reference to a commit

Commit Object:
┌────────────────────────────────┐
│ tree    → a1b2c3...           │ ← Points to root tree
│ parent  → d4e5f6...           │ ← Points to previous commit
│ author  → Kunal <k@mail.com>  │
│ message → "Add login feature" │
└────────────────────────────────┘
         │
         ▼
Tree Object (root):
┌────────────────────────────────┐
│ blob a1b2... → README.md       │
│ blob c3d4... → App.java        │
│ tree e5f6... → src/            │
└────────────────────────────────┘
```

### The Three Areas of Git

```
┌─────────────┐    git add     ┌─────────────┐   git commit   ┌─────────────┐
│  Working     │ ────────────→ │   Staging    │ ────────────→ │  Repository │
│  Directory   │               │   Area       │               │  (.git)     │
│  (modified)  │ ←──────────── │  (index)     │               │  (history)  │
└─────────────┘    (editing)   └─────────────┘               └─────────────┘

Working Directory: Where you edit files
Staging Area:      Where you prepare changes for commit (also called "index")
Repository:        Where commits are permanently stored
```

---

## 3. Working Locally with Git

### Configuration

```bash
# Set identity (required before first commit)
git config --global user.name "Kunal"
git config --global user.email "kunal@example.com"

# Set default editor
git config --global core.editor "code --wait"   # VS Code

# Set default branch name
git config --global init.defaultBranch main

# View all config
git config --list

# Config levels:
# --system  → /etc/gitconfig (all users)
# --global  → ~/.gitconfig (your user)
# --local   → .git/config (this repo only — highest priority)
```

### Initializing a Repository

```bash
# Create a new repo
mkdir my-project && cd my-project
git init
# Creates .git/ directory with all Git internals

# What's inside .git/?
.git/
├── HEAD            # Points to current branch (ref: refs/heads/main)
├── config          # Repo-specific config
├── objects/        # All Git objects (blobs, trees, commits)
├── refs/           # Branch and tag pointers
│   ├── heads/      # Local branches
│   └── tags/       # Tags
├── index           # Staging area (binary file)
├── hooks/          # Client/server-side scripts
└── logs/           # Reflog (history of HEAD movements)
```

### Basic Workflow

```bash
# 1. Check status
git status

# 2. Stage changes
git add file.txt              # Stage specific file
git add .                     # Stage all changes
git add *.java                # Stage all Java files
git add -p                    # Interactive staging (pick hunks)

# 3. Commit
git commit -m "Add login feature"
git commit -am "Fix bug"      # Stage tracked files + commit (shortcuts)

# 4. View history
git log                       # Full log
git log --oneline             # Compact log
git log --oneline --graph     # Graph view
git log --oneline -5          # Last 5 commits
git log --stat                # Show files changed per commit
git log --author="Kunal"      # Filter by author
git log --since="2025-01-01"  # Filter by date
git log -- file.txt           # History of specific file
```

### Viewing Changes

```bash
# Working directory vs staging area
git diff

# Staging area vs last commit
git diff --staged
git diff --cached             # Same as --staged

# Between two commits
git diff abc123..def456

# Between two branches
git diff main..feature-branch

# Word-level diff
git diff --word-diff

# Summary of changes
git diff --stat
```

### Undoing Changes

```bash
# Discard changes in working directory
git checkout -- file.txt      # Old way
git restore file.txt          # Modern way (Git 2.23+)

# Unstage a file
git reset HEAD file.txt       # Old way
git restore --staged file.txt # Modern way

# Amend last commit (change message or add files)
git add forgotten_file.txt
git commit --amend -m "Updated message"

# Undo last commit (keep changes staged)
git reset --soft HEAD~1

# Undo last commit (keep changes unstaged)
git reset --mixed HEAD~1      # Default behavior
git reset HEAD~1

# Undo last commit (DISCARD changes — ⚠️ DANGEROUS)
git reset --hard HEAD~1

# Revert a commit (creates new "undo" commit — safe for shared branches)
git revert abc123
```

### Under the Hood: `reset` vs `revert`

```
git reset --hard HEAD~1:
Before: A ← B ← C (HEAD)
After:  A ← B (HEAD)         ← C is GONE (rewrites history)

git revert HEAD:
Before: A ← B ← C (HEAD)
After:  A ← B ← C ← C' (HEAD)  ← C' undoes C (safe, history preserved)

Rule: Use REVERT on shared branches, RESET on your own branches.
```

---

## 4. Git Commit Best Practices

### Commit Message Format

```
<type>(<scope>): <subject>

<body — optional, wrap at 72 chars>

<footer — optional>

Types:
  feat:     New feature
  fix:      Bug fix
  docs:     Documentation only
  style:    Formatting (no code change)
  refactor: Code restructuring (no behavior change)
  test:     Adding/fixing tests
  chore:    Build process, dependencies, tooling

Examples:
  feat(auth): add JWT token authentication
  fix(api): resolve null pointer in user service
  docs(readme): update installation instructions
  refactor(db): extract connection pool logic
```

---

## 5. Branching, Merging, and Rebasing

### Branches

A branch is simply a **pointer to a commit**. Creating a branch is instant — Git just creates a new pointer.

```bash
# List branches
git branch              # Local branches
git branch -a           # All branches (local + remote)
git branch -v           # Branches with last commit

# Create branch
git branch feature-login

# Switch to branch
git checkout feature-login    # Old way
git switch feature-login      # Modern way (Git 2.23+)

# Create and switch
git checkout -b feature-login # Old way
git switch -c feature-login   # Modern way

# Delete branch
git branch -d feature-login   # Safe delete (must be merged)
git branch -D feature-login   # Force delete

# Rename branch
git branch -m old-name new-name
git branch -m new-name        # Rename current branch
```

### Under the Hood: What a Branch Really Is

```bash
# A branch is just a file containing a commit hash
cat .git/refs/heads/main
# Output: a1b2c3d4e5f6... (40-char SHA-1 hash)

# HEAD points to the current branch
cat .git/HEAD
# Output: ref: refs/heads/main

Branch Diagram:
                     feature
                       ↓
        ┌───┐  ┌───┐  ┌───┐
   ─────│ C │──│ D │──│ E │
        └───┘  └───┘  └───┘
       /
┌───┐  ┌───┐
│ A │──│ B │
└───┘  └───┘
              ↑
             main
              ↑
             HEAD
```

### Merging

```bash
# Merge feature branch into main
git switch main
git merge feature-login

# Merge types:
# 1. Fast-forward (linear history — no merge commit)
# 2. Three-way merge (creates a merge commit)
# 3. Squash merge (combines all commits into one)
```

### Fast-Forward Merge

```
Before:
main:     A ← B
                ↖
feature:          C ← D

After git merge feature (fast-forward):
main:     A ← B ← C ← D
                         ↑
                        HEAD

No merge commit needed — main just "moves forward" to D
```

### Three-Way Merge

```
Before:
main:     A ← B ← E
                ↖
feature:          C ← D

After git merge feature (three-way):
main:     A ← B ← E ──── M (merge commit)
                ↖        ↗
feature:          C ← D

M combines changes from both E and D, using B as the common ancestor
```

### Merge Conflicts

```bash
# Conflicts happen when two branches modify the SAME lines

# Git marks conflicts in the file:
<<<<<<< HEAD
This is the main branch version
=======
This is the feature branch version
>>>>>>> feature-login

# Resolution steps:
# 1. Open the conflicting file
# 2. Decide which version to keep (or combine)
# 3. Remove the conflict markers (<<<<<<, ======, >>>>>>)
# 4. Stage the resolved file
git add resolved_file.txt
# 5. Complete the merge
git commit
```

### Rebasing

Rebase moves your branch's commits **on top of** another branch, creating a linear history:

```bash
# Rebase feature onto main
git switch feature-login
git rebase main

# Before rebase:
main:     A ← B ← E
                ↖
feature:          C ← D

# After rebase:
main:     A ← B ← E
                     ↖
feature:               C' ← D'

# C' and D' are NEW commits (different SHA) — replayed on top of E
```

### Merge vs Rebase

```
Merge:
  - Preserves complete history
  - Creates merge commits (can be noisy)
  - Safe for shared branches
  - Non-destructive

Rebase:
  - Creates linear, clean history
  - No merge commits
  - ⚠️ NEVER rebase shared/public branches
  - Rewrites commit history

Golden Rule: Never rebase commits that have been pushed to a shared branch.
```

### Interactive Rebase (Powerful!)

```bash
# Rewrite the last 3 commits
git rebase -i HEAD~3

# Opens editor with:
pick abc123 First commit
pick def456 Second commit
pick ghi789 Third commit

# Commands:
# pick   — use commit as-is
# reword — change commit message
# edit   — pause for amending
# squash — combine with previous commit
# fixup  — like squash but discard message
# drop   — remove commit
```

---

## 6. Working Remotely with Git

### Remote Repositories

```bash
# Clone a repository
git clone https://github.com/user/repo.git
git clone git@github.com:user/repo.git         # SSH (recommended)

# View remotes
git remote -v
# origin  https://github.com/user/repo.git (fetch)
# origin  https://github.com/user/repo.git (push)

# Add remote
git remote add origin https://github.com/user/repo.git
git remote add upstream https://github.com/original/repo.git

# Remove/rename remote
git remote remove origin
git remote rename origin upstream
```

### Push, Pull, Fetch

```bash
# Push to remote
git push origin main              # Push main branch
git push origin feature-login     # Push feature branch
git push -u origin main           # Set upstream (first push)
git push                          # After -u, just use this

# Fetch (download but don't merge)
git fetch origin                  # Fetch all branches
git fetch origin main             # Fetch specific branch

# Pull (fetch + merge)
git pull origin main              # Pull and merge
git pull --rebase origin main     # Pull and rebase (cleaner)

# Push a new branch
git push -u origin feature-login

# Delete remote branch
git push origin --delete feature-login
```

### Under the Hood: `fetch` vs `pull`

```
git fetch:
Remote:  A ← B ← C ← D ← E
Local:   A ← B ← C
                    ↖
origin/main:          D ← E  (updated, but YOUR branch unchanged)

git pull (= fetch + merge):
Remote:  A ← B ← C ← D ← E
Local:   A ← B ← C ← D ← E  (your branch is updated)
```

### Collaborative Workflow (GitHub Flow)

```
1. Create a branch from main
   git switch -c feature/user-auth

2. Make changes and commit
   git add . && git commit -m "feat(auth): add login endpoint"

3. Push to remote
   git push -u origin feature/user-auth

4. Open a Pull Request (PR) on GitHub

5. Code review by team members

6. Merge PR into main (on GitHub)

7. Delete feature branch
   git branch -d feature/user-auth
   git push origin --delete feature/user-auth

8. Update local main
   git switch main && git pull origin main
```

---

## 7. Useful Git Commands

### Stashing (Temporary Save)

```bash
# Stash current changes (save and clean working directory)
git stash
git stash save "WIP: login feature"

# List stashes
git stash list
# stash@{0}: WIP on main: abc123 Last commit message

# Apply stash
git stash pop               # Apply and remove from stash list
git stash apply             # Apply but keep in stash list
git stash apply stash@{1}   # Apply specific stash

# Drop stash
git stash drop stash@{0}
git stash clear             # Remove all stashes
```

### Tagging

```bash
# Create tag
git tag v1.0.0                           # Lightweight tag
git tag -a v1.0.0 -m "Release v1.0.0"   # Annotated tag (recommended)

# List tags
git tag
git tag -l "v1.*"

# Push tags
git push origin v1.0.0
git push origin --tags                    # Push all tags

# Delete tag
git tag -d v1.0.0                        # Local
git push origin --delete v1.0.0          # Remote
```

### Cherry-Pick

```bash
# Apply a specific commit from another branch
git cherry-pick abc123

# Cherry-pick without committing
git cherry-pick --no-commit abc123
```

### Git Log Tips

```bash
# Beautiful graph log
git log --oneline --graph --all --decorate

# Git alias for pretty log
git config --global alias.lg "log --oneline --graph --all --decorate"
git lg    # Now works as shortcut

# Search commit messages
git log --grep="login"

# Search code changes
git log -S "function_name"     # Pickaxe — find when code was added/removed
```

### `.gitignore`

```gitignore
# Compiled files
*.class
*.o
*.pyc
__pycache__/

# Build directories
target/
build/
dist/
node_modules/

# IDE files
.idea/
.vscode/
*.iml
.project
.settings/

# OS files
.DS_Store
Thumbs.db

# Environment files
.env
.env.local
*.log

# Secrets
*.key
*.pem
credentials.json
```

---

## 8. Quick Reference

```bash
# Essential daily commands
git status                    # What's changed?
git add .                     # Stage everything
git commit -m "message"       # Commit
git push                      # Push to remote
git pull                      # Get latest changes
git switch -c branch-name     # Create and switch branch
git merge branch-name         # Merge branch
git log --oneline -10         # Recent history
git stash / git stash pop     # Temporary save
git diff                      # View changes
```
