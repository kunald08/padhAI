# Shell Scripting — From Basics to Expert

---

## 1. Introduction to Shell Scripting

### What is a Shell?

A **shell** is a command-line interpreter that provides an interface between the user and the operating system kernel. It reads commands, interprets them, and executes them.

### Types of Shells

| Shell | Path | Description |
|-------|------|-------------|
| **Bash** | `/bin/bash` | Bourne Again Shell — most popular, default on most Linux distros |
| **sh** | `/bin/sh` | Bourne Shell — original Unix shell |
| **zsh** | `/bin/zsh` | Z Shell — extended Bash with more features |
| **ksh** | `/bin/ksh` | Korn Shell — used in enterprise Unix systems |
| **csh** | `/bin/csh` | C Shell — C-like syntax |

```bash
# Check your current shell
echo $SHELL
# Output: /bin/bash

# List all available shells
cat /etc/shells

# Switch shell temporarily
zsh

# Change default shell permanently
chsh -s /bin/zsh
```

### What is a Shell Script?

A shell script is a **text file** containing a sequence of commands that the shell executes. It automates repetitive tasks.

### Under the Hood: How Shell Scripts Execute

```
┌──────────────┐     ┌──────────────┐     ┌──────────────┐
│  script.sh   │ ──→ │    Shell     │ ──→ │    Kernel    │
│  (text file) │     │ (interprets  │     │ (executes    │
│              │     │  line by     │     │  system      │
│              │     │  line)       │     │  calls)      │
└──────────────┘     └──────────────┘     └──────────────┘

1. Shell reads the first line (shebang) to know which interpreter to use
2. Shell reads each line, parses it, expands variables, and executes
3. Each command translates to system calls to the kernel
4. Kernel interacts with hardware and returns results
```

### Your First Script

```bash
#!/bin/bash
# This is a comment — the first line is the "shebang"
# It tells the OS which interpreter to use

echo "Hello, World!"
echo "Today is: $(date)"
echo "You are logged in as: $(whoami)"
echo "Your home directory is: $HOME"
```

### Making It Executable and Running

```bash
# Method 1: Make executable and run
chmod +x script.sh
./script.sh

# Method 2: Pass to interpreter directly
bash script.sh

# Method 3: Source it (runs in current shell)
source script.sh
. script.sh
```

> **Under the Hood**: `./script.sh` creates a **new child process** (subshell). `source script.sh` runs in the **current shell** — meaning any variables set in the script persist in your terminal.

---

## 2. Basic Shell Scripting Concepts

### Variables

```bash
#!/bin/bash

# Variable assignment — NO SPACES around =
name="Kunal"
age=25
is_admin=true

# Using variables — prefix with $
echo "Name: $name"
echo "Age: $age"

# Curly braces for clarity
echo "Hello, ${name}!"
echo "${name}'s age is ${age}"

# Read-only variables
readonly PI=3.14159
PI=3.0    # Error: PI is a readonly variable

# Unsetting variables
unset age
echo $age   # Nothing — variable is gone
```

### Variable Scoping

```bash
#!/bin/bash

# Global variable (available everywhere in the script)
global_var="I am global"

my_function() {
    # Local variable (only inside this function)
    local local_var="I am local"
    echo $global_var    # Works
    echo $local_var     # Works
}

my_function
echo $global_var        # Works
echo $local_var         # Empty — not accessible outside function
```

### Special Variables

```bash
#!/bin/bash

echo "Script name: $0"           # Name of the script
echo "First argument: $1"        # First positional argument
echo "Second argument: $2"       # Second positional argument
echo "All arguments: $@"         # All arguments as separate strings
echo "All arguments: $*"         # All arguments as single string
echo "Number of arguments: $#"   # Count of arguments
echo "Process ID: $$"            # PID of current script
echo "Last background PID: $!"   # PID of last background process
echo "Exit status: $?"           # Exit code of last command (0=success)
```

### Data Types and Strings

```bash
#!/bin/bash

# Bash variables are UNTYPED (everything is a string internally)

# String operations
str="Hello World"
echo ${#str}           # Length: 11
echo ${str:0:5}        # Substring: Hello (start:length)
echo ${str:6}          # From position 6: World
echo ${str/World/Bash} # Replace: Hello Bash
echo ${str^^}          # Uppercase: HELLO WORLD
echo ${str,,}          # Lowercase: hello world

# String concatenation
first="Hello"
second="World"
result="${first} ${second}"
echo $result           # Hello World

# Single vs Double quotes
name="Kunal"
echo "Hello $name"     # Hello Kunal (variables expanded)
echo 'Hello $name'     # Hello $name (literal — no expansion)
echo "Today is $(date)" # Command substitution works in double quotes

# Arithmetic
declare -i num=10       # Declare as integer
num=num+5               # Works because declared as integer
echo $num               # 15

# Or use arithmetic expansion
result=$((5 + 3))
echo $result            # 8

result=$(( 10 * 2 + 5 ))
echo $result            # 25

# Floating point (bash doesn't support — use bc)
result=$(echo "scale=2; 10 / 3" | bc)
echo $result            # 3.33
```

### Arrays

```bash
#!/bin/bash

# Indexed array
fruits=("apple" "banana" "cherry" "date" "elderberry")

echo ${fruits[0]}         # First element: apple
echo ${fruits[2]}         # Third element: cherry
echo ${fruits[@]}         # All elements
echo ${#fruits[@]}        # Length: 5
echo ${fruits[@]:1:3}     # Slice: banana cherry date

# Add element
fruits+=("fig")

# Delete element
unset fruits[1]           # Removes "banana" (index remains, value gone)

# Loop through array
for fruit in "${fruits[@]}"; do
    echo "Fruit: $fruit"
done

# Associative array (dictionary/map) — Bash 4+
declare -A person
person[name]="Kunal"
person[age]=25
person[city]="Mumbai"

echo ${person[name]}      # Kunal
echo ${!person[@]}        # All keys: name age city
echo ${person[@]}         # All values: Kunal 25 Mumbai

for key in "${!person[@]}"; do
    echo "$key: ${person[$key]}"
done
```

---

## 3. Control Structures

### If-Else

```bash
#!/bin/bash

# Basic if
age=20

if [ $age -ge 18 ]; then
    echo "Adult"
fi

# If-else
if [ $age -ge 18 ]; then
    echo "Adult"
else
    echo "Minor"
fi

# If-elif-else
score=75

if [ $score -ge 90 ]; then
    echo "Grade: A"
elif [ $score -ge 80 ]; then
    echo "Grade: B"
elif [ $score -ge 70 ]; then
    echo "Grade: C"
elif [ $score -ge 60 ]; then
    echo "Grade: D"
else
    echo "Grade: F"
fi
```

### Comparison Operators

```bash
# Numeric comparisons (use inside [ ])
-eq    # Equal
-ne    # Not equal
-gt    # Greater than
-ge    # Greater than or equal
-lt    # Less than
-le    # Less than or equal

# String comparisons
=      # Equal (or ==)
!=     # Not equal
-z     # String is empty (zero length)
-n     # String is not empty
<      # Less than (alphabetically)
>      # Greater than (alphabetically)

# File tests
-f     # Is a regular file
-d     # Is a directory
-e     # Exists (file or directory)
-r     # Is readable
-w     # Is writable
-x     # Is executable
-s     # File is not empty (size > 0)
-L     # Is a symbolic link

# Logical operators
-a     # AND (inside [ ])
-o     # OR (inside [ ])
!      # NOT

# Examples:
if [ -f "/etc/passwd" ]; then
    echo "File exists"
fi

if [ -z "$name" ]; then
    echo "Name is empty"
fi

if [ "$str1" = "$str2" ]; then
    echo "Strings are equal"
fi
```

### Modern Test: `[[ ]]` (Bash-specific)

```bash
#!/bin/bash

# [[ ]] is the modern version — safer and more features
name="Kunal"

# Pattern matching
if [[ $name == K* ]]; then
    echo "Name starts with K"
fi

# Regex matching
email="kunal@example.com"
if [[ $email =~ ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$ ]]; then
    echo "Valid email"
fi

# No need to quote variables (safer)
if [[ -z $name ]]; then
    echo "Empty"
fi

# Logical operators use && and ||
if [[ $age -ge 18 && $age -le 65 ]]; then
    echo "Working age"
fi
```

### Case (Switch) Statement

```bash
#!/bin/bash

read -p "Enter a fruit: " fruit

case $fruit in
    "apple")
        echo "Apples are red"
        ;;
    "banana")
        echo "Bananas are yellow"
        ;;
    "cherry" | "strawberry")     # Multiple patterns
        echo "These are small fruits"
        ;;
    *)                            # Default case
        echo "Unknown fruit: $fruit"
        ;;
esac
```

### Loops

```bash
#!/bin/bash

# For loop — iterate over list
for color in red green blue yellow; do
    echo "Color: $color"
done

# For loop — C-style
for ((i = 0; i < 5; i++)); do
    echo "Number: $i"
done

# For loop — range
for i in {1..10}; do
    echo "Count: $i"
done

# For loop — range with step
for i in {0..100..10}; do
    echo "Tens: $i"       # 0, 10, 20, ... 100
done

# For loop — iterate over files
for file in *.txt; do
    echo "Processing: $file"
done

# While loop
count=1
while [ $count -le 5 ]; do
    echo "Count: $count"
    ((count++))
done

# While loop — read file line by line
while IFS= read -r line; do
    echo "Line: $line"
done < input.txt

# Until loop (opposite of while — runs UNTIL condition is true)
count=1
until [ $count -gt 5 ]; do
    echo "Count: $count"
    ((count++))
done

# Loop control
for i in {1..10}; do
    if [ $i -eq 3 ]; then
        continue    # Skip iteration 3
    fi
    if [ $i -eq 8 ]; then
        break       # Exit loop at 8
    fi
    echo $i         # Prints: 1 2 4 5 6 7
done

# Infinite loop
while true; do
    echo "Press Ctrl+C to stop"
    sleep 1
done
```

### Select (Menu)

```bash
#!/bin/bash

echo "Select your OS:"
select os in "Linux" "macOS" "Windows" "Quit"; do
    case $os in
        "Linux") echo "You chose Linux"; break ;;
        "macOS") echo "You chose macOS"; break ;;
        "Windows") echo "You chose Windows"; break ;;
        "Quit") echo "Goodbye!"; exit 0 ;;
        *) echo "Invalid option" ;;
    esac
done
```

---

## 4. Command-Line Arguments

### Accessing Arguments

```bash
#!/bin/bash
# Save as: greet.sh
# Run as: ./greet.sh Kunal 25

echo "Script: $0"         # ./greet.sh
echo "Name: $1"           # Kunal
echo "Age: $2"            # 25
echo "All args: $@"       # Kunal 25
echo "Arg count: $#"      # 2
```

### Parsing Options with `getopts`

```bash
#!/bin/bash
# Save as: deploy.sh
# Run as: ./deploy.sh -e production -v -p 8080

environment="development"
verbose=false
port=3000

while getopts "e:vp:h" opt; do
    case $opt in
        e) environment=$OPTARG ;;
        v) verbose=true ;;
        p) port=$OPTARG ;;
        h)
            echo "Usage: $0 [-e environment] [-v] [-p port]"
            echo "  -e  Environment (default: development)"
            echo "  -v  Verbose mode"
            echo "  -p  Port number (default: 3000)"
            exit 0
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
    esac
done

echo "Environment: $environment"
echo "Verbose: $verbose"
echo "Port: $port"
```

### Argument Validation

```bash
#!/bin/bash

# Check minimum arguments
if [ $# -lt 2 ]; then
    echo "Usage: $0 <source> <destination>"
    exit 1
fi

source_file=$1
dest_file=$2

# Validate file exists
if [ ! -f "$source_file" ]; then
    echo "Error: Source file '$source_file' not found"
    exit 1
fi

# Validate directory exists
dest_dir=$(dirname "$dest_file")
if [ ! -d "$dest_dir" ]; then
    echo "Error: Destination directory '$dest_dir' does not exist"
    exit 1
fi

cp "$source_file" "$dest_file"
echo "Copied $source_file to $dest_file"
```

### Shift — Processing Arguments

```bash
#!/bin/bash

# shift moves arguments left: $2→$1, $3→$2, etc.
while [ $# -gt 0 ]; do
    echo "Processing: $1"
    shift
done

# Example: ./script.sh a b c d
# Output:
# Processing: a
# Processing: b
# Processing: c
# Processing: d
```

---

## 5. Functions

### Defining and Calling Functions

```bash
#!/bin/bash

# Method 1: function keyword
function greet() {
    echo "Hello, $1!"
}

# Method 2: without function keyword (POSIX compatible)
add() {
    local result=$(( $1 + $2 ))
    echo $result
}

# Calling functions
greet "Kunal"           # Hello, Kunal!
sum=$(add 5 3)          # Capture output
echo "Sum: $sum"        # Sum: 8
```

### Return Values

```bash
#!/bin/bash

# Functions can return exit codes (0-255) via 'return'
# For actual values, use echo + command substitution

is_even() {
    if (( $1 % 2 == 0 )); then
        return 0    # 0 = true/success in bash
    else
        return 1    # non-zero = false/failure
    fi
}

# Using return code
is_even 4
if [ $? -eq 0 ]; then
    echo "4 is even"
fi

# Shorter version
if is_even 6; then
    echo "6 is even"
fi

# Returning a string value
get_greeting() {
    local name=$1
    local time_of_day=$2
    echo "Good $time_of_day, $name!"    # "returns" via stdout
}

message=$(get_greeting "Kunal" "morning")
echo $message    # Good morning, Kunal!
```

### Advanced Function Patterns

```bash
#!/bin/bash

# Function with default parameters
connect() {
    local host=${1:-"localhost"}
    local port=${2:-3306}
    local user=${3:-"root"}
    echo "Connecting to $user@$host:$port"
}

connect                           # localhost:3306 as root
connect "db.example.com"          # db.example.com:3306 as root
connect "db.example.com" 5432 "admin"  # Full custom

# Function library — source from another file
# file: lib/utils.sh
log_info() {
    echo "[INFO] $(date '+%Y-%m-%d %H:%M:%S') - $1"
}

log_error() {
    echo "[ERROR] $(date '+%Y-%m-%d %H:%M:%S') - $1" >&2
}

log_warn() {
    echo "[WARN] $(date '+%Y-%m-%d %H:%M:%S') - $1"
}

# file: main.sh
# source lib/utils.sh
# log_info "Application started"
# log_error "Database connection failed"
```

---

## 6. Text Processing

### `sed` — Stream Editor

```bash
#!/bin/bash

# sed performs text transformations on files or streams

# Substitute (replace) — first occurrence per line
sed 's/old/new/' file.txt

# Substitute — all occurrences per line (global)
sed 's/old/new/g' file.txt

# Case-insensitive replace
sed 's/old/new/gi' file.txt

# Replace in-place (edit file directly)
sed -i 's/old/new/g' file.txt

# Delete lines
sed '5d' file.txt           # Delete line 5
sed '3,7d' file.txt         # Delete lines 3-7
sed '/pattern/d' file.txt   # Delete lines matching pattern
sed '/^$/d' file.txt        # Delete empty lines

# Print specific lines
sed -n '10p' file.txt       # Print only line 10
sed -n '5,10p' file.txt     # Print lines 5-10

# Insert/Append
sed '3i\New line before 3' file.txt   # Insert before line 3
sed '3a\New line after 3' file.txt    # Append after line 3

# Multiple operations
sed -e 's/foo/bar/g' -e 's/baz/qux/g' file.txt

# Practical example: Update config file
sed -i 's/port=8080/port=9090/g' config.properties
```

### `awk` — Pattern Scanning and Processing

```bash
#!/bin/bash

# awk processes text line by line, splitting each into fields

# Basic syntax: awk 'pattern {action}' file

# Print specific fields (default delimiter: whitespace)
echo "John 25 Engineer" | awk '{print $1}'       # John
echo "John 25 Engineer" | awk '{print $1, $3}'   # John Engineer

# Custom delimiter
echo "John,25,Engineer" | awk -F',' '{print $1, $3}'  # John Engineer

# Print with formatting
awk '{printf "%-15s %5d\n", $1, $2}' data.txt

# Filter by condition
awk '$3 > 50000 {print $1, $3}' employees.txt    # Salary > 50000

# Built-in variables
awk '{print NR": "$0}' file.txt      # NR = line number, $0 = whole line
awk 'END {print NR}' file.txt        # Total number of lines
awk '{print NF}' file.txt            # NF = number of fields per line

# Sum a column
awk '{sum += $2} END {print "Total:", sum}' data.txt

# Average
awk '{sum += $2; count++} END {print "Average:", sum/count}' data.txt

# Practical: Parse CSV and generate report
awk -F',' '
    NR > 1 {
        sum += $3
        count++
        if ($3 > max) max = $3
        if (min == "" || $3 < min) min = $3
    }
    END {
        print "Records:", count
        print "Total:", sum
        print "Average:", sum/count
        print "Max:", max
        print "Min:", min
    }
' sales.csv

# Print lines between two patterns
awk '/START/,/END/' file.txt
```

### Combining Tools

```bash
#!/bin/bash

# Parse Apache access log — top 10 IPs
cat access.log | awk '{print $1}' | sort | uniq -c | sort -rn | head -10

# Find all TODO comments in code
grep -rn "TODO" --include="*.java" src/ | awk -F: '{printf "%s (line %s): %s\n", $1, $2, $3}'

# CSV to formatted table
cat data.csv | awk -F',' '{printf "| %-15s | %-10s | %8s |\n", $1, $2, $3}'

# Extract email addresses from a file
grep -oE '[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}' file.txt | sort -u

# Replace multiple spaces with single space
sed 's/  */ /g' file.txt

# Count word frequency in a file
cat file.txt | tr '[:upper:]' '[:lower:]' | tr -s ' ' '\n' | sort | uniq -c | sort -rn | head -20
```

---

## 7. Error Handling and Debugging

### Exit Codes

```bash
#!/bin/bash

# Every command returns an exit code:
# 0 = success
# 1-255 = failure (different codes mean different errors)

ls /nonexistent 2>/dev/null
echo "Exit code: $?"    # 2 (No such file or directory)

# Set exit codes in your scripts
exit 0    # Success
exit 1    # General error

# Custom exit codes
readonly E_SUCCESS=0
readonly E_FILE_NOT_FOUND=2
readonly E_PERMISSION_DENIED=3
readonly E_INVALID_ARGS=4
```

### Error Handling Patterns

```bash
#!/bin/bash

# Method 1: Check $? after each command
cp source.txt dest.txt
if [ $? -ne 0 ]; then
    echo "Copy failed!" >&2
    exit 1
fi

# Method 2: Short-circuit with || 
cp source.txt dest.txt || { echo "Copy failed!" >&2; exit 1; }

# Method 3: set -e (exit on any error)
set -e          # Script exits immediately if any command fails
set -u          # Treat unset variables as errors
set -o pipefail # Pipe fails if any command in pipe fails

# Combine all three (best practice)
set -euo pipefail

# Method 4: trap — execute on error/exit
cleanup() {
    echo "Cleaning up temporary files..."
    rm -f /tmp/myapp_*
}

error_handler() {
    echo "Error on line $1" >&2
    cleanup
    exit 1
}

trap 'error_handler $LINENO' ERR
trap cleanup EXIT

# Method 5: Try-catch equivalent
{
    # Try
    risky_command
} || {
    # Catch
    echo "risky_command failed, trying alternative..."
    alternative_command
}
```

### Debugging Techniques

```bash
#!/bin/bash

# Method 1: Run with debug flag
bash -x script.sh          # Print each command before executing

# Method 2: Enable debug in script
set -x      # Turn on debug (shows each command)
# ... code ...
set +x      # Turn off debug

# Method 3: Debug specific sections
set -x
problematic_code_here
set +x

# Method 4: PS4 — customize debug prompt
export PS4='+(${BASH_SOURCE}:${LINENO}): ${FUNCNAME[0]:+${FUNCNAME[0]}(): }'
set -x
# Now debug output shows file, line number, and function name

# Method 5: Logging function
DEBUG=true

debug_log() {
    if [ "$DEBUG" = true ]; then
        echo "[DEBUG] $(date '+%H:%M:%S') - $1" >&2
    fi
}

debug_log "Processing file: $filename"
debug_log "Variable value: count=$count"

# Method 6: Validate with shellcheck (external tool)
# Install: sudo apt install shellcheck
# Run: shellcheck script.sh
```

---

## 8. Real-World Script Examples

### Example 1: Automated Backup Script

```bash
#!/bin/bash
set -euo pipefail

# Configuration
BACKUP_DIR="/backups"
SOURCE_DIR="/home/kunal/projects"
DATE=$(date +%Y%m%d_%H%M%S)
BACKUP_FILE="${BACKUP_DIR}/backup_${DATE}.tar.gz"
MAX_BACKUPS=7

# Logging
log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $1"
}

# Create backup directory if not exists
mkdir -p "$BACKUP_DIR"

# Create backup
log "Starting backup of $SOURCE_DIR"
tar -czf "$BACKUP_FILE" -C "$(dirname "$SOURCE_DIR")" "$(basename "$SOURCE_DIR")"
log "Backup created: $BACKUP_FILE ($(du -h "$BACKUP_FILE" | cut -f1))"

# Remove old backups (keep only last N)
backup_count=$(ls -1 "$BACKUP_DIR"/backup_*.tar.gz 2>/dev/null | wc -l)
if [ "$backup_count" -gt "$MAX_BACKUPS" ]; then
    remove_count=$((backup_count - MAX_BACKUPS))
    ls -1t "$BACKUP_DIR"/backup_*.tar.gz | tail -n "$remove_count" | xargs rm -f
    log "Removed $remove_count old backup(s)"
fi

log "Backup complete. Total backups: $(ls -1 "$BACKUP_DIR"/backup_*.tar.gz | wc -l)"
```

### Example 2: System Health Check

```bash
#!/bin/bash

echo "========================================="
echo "  System Health Check — $(date)"
echo "========================================="

# CPU Usage
echo ""
echo "--- CPU Usage ---"
top -bn1 | head -5

# Memory Usage
echo ""
echo "--- Memory Usage ---"
free -h

# Disk Usage
echo ""
echo "--- Disk Usage ---"
df -h | grep -E '^/dev'

# Check if disk usage > 80%
echo ""
echo "--- Disk Alerts ---"
df -h | awk 'NR>1 {
    gsub(/%/,"",$5)
    if ($5+0 > 80)
        printf "⚠️  WARNING: %s is %s%% full (%s)\n", $6, $5, $1
}'

# Top 5 processes by memory
echo ""
echo "--- Top 5 Processes (Memory) ---"
ps aux --sort=-%mem | head -6

# Network connectivity
echo ""
echo "--- Network ---"
ping -c 1 -W 2 google.com > /dev/null 2>&1 && echo "Internet: Connected" || echo "Internet: Disconnected"

echo ""
echo "========================================="
echo "  Check complete"
echo "========================================="
```

### Example 3: Log Analyzer

```bash
#!/bin/bash
set -euo pipefail

LOG_FILE=${1:-"/var/log/syslog"}

if [ ! -f "$LOG_FILE" ]; then
    echo "Error: Log file not found: $LOG_FILE" >&2
    exit 1
fi

echo "Analyzing: $LOG_FILE"
echo "========================"

echo ""
echo "Total lines: $(wc -l < "$LOG_FILE")"

echo ""
echo "--- Error Summary ---"
grep -ci "error" "$LOG_FILE" 2>/dev/null && true
echo "errors found"

echo ""
echo "--- Warning Summary ---"
grep -ci "warning" "$LOG_FILE" 2>/dev/null && true
echo "warnings found"

echo ""
echo "--- Last 10 Errors ---"
grep -i "error" "$LOG_FILE" | tail -10

echo ""
echo "--- Errors by Hour ---"
grep -i "error" "$LOG_FILE" | awk '{print $3}' | cut -d: -f1 | sort | uniq -c | sort -rn
```
