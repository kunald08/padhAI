# Linux — From Basics to Expert

---

## 1. Introduction to Linux

### What is Linux?

Linux is an **open-source, Unix-like operating system** kernel created by **Linus Torvalds** in 1991. What we commonly call "Linux" is actually **GNU/Linux** — the Linux kernel combined with GNU utilities.

### Under the Hood: How Linux Works

```
┌─────────────────────────────────────────┐
│            User Applications            │  ← Web browsers, editors, etc.
├─────────────────────────────────────────┤
│               Shell (Bash/Zsh)          │  ← Command interpreter
├─────────────────────────────────────────┤
│         System Libraries (glibc)        │  ← C library, system calls wrapper
├─────────────────────────────────────────┤
│              Linux Kernel               │  ← Core OS: memory, process, I/O
│  ┌──────┬──────┬──────┬──────┬───────┐  │
│  │ Proc │ Mem  │ File │  Net │Device │  │
│  │ Mgmt │ Mgmt │  Sys │Stack │Driver │  │
│  └──────┴──────┴──────┴──────┴───────┘  │
├─────────────────────────────────────────┤
│              Hardware (CPU, RAM, Disk)  │
└─────────────────────────────────────────┘
```

### Linux Filesystem Hierarchy

```
/                   ← Root directory (everything starts here)
├── bin/            ← Essential user binaries (ls, cp, mv, cat)
├── sbin/           ← System binaries (fdisk, iptables)
├── etc/            ← Configuration files (passwd, fstab, nginx.conf)
├── home/           ← User home directories (/home/kunal)
├── root/           ← Root user's home directory
├── var/            ← Variable data (logs, databases, mail)
│   ├── log/        ← System log files
│   └── www/        ← Web server files
├── tmp/            ← Temporary files (cleared on reboot)
├── usr/            ← User programs and data
│   ├── bin/        ← User binaries
│   ├── lib/        ← Libraries
│   └── share/      ← Shared data
├── opt/            ← Optional/third-party software
├── dev/            ← Device files (sda, tty, null)
├── proc/           ← Virtual filesystem (process info, kernel info)
├── sys/            ← Virtual filesystem (hardware/driver info)
├── mnt/            ← Mount point for temporary mounts
├── media/          ← Mount point for removable media
└── boot/           ← Boot loader files (vmlinuz, grub)
```

---

## 2. Basic Linux Commands

### Navigation Commands

```bash
# Print working directory
pwd
# Output: /home/kunal

# Change directory
cd /var/log         # Absolute path
cd ..               # Go up one level
cd ~                # Go to home directory
cd -                # Go to previous directory

# List files
ls                  # Basic listing
ls -l               # Long format (permissions, size, date)
ls -la              # Include hidden files (starting with .)
ls -lh              # Human-readable file sizes (KB, MB, GB)
ls -lt              # Sort by modification time
ls -lS              # Sort by size
ls -R               # Recursive listing
```

### Output of `ls -la` Explained

```
drwxr-xr-x  5 kunal kunal 4096 Feb 10 14:30 projects
-rw-r--r--  1 kunal kunal 2048 Feb 10 14:25 notes.txt
│├─┤├─┤├─┤  │ │     │     │    │              │
│ │   │  │  │ │     │     │    │              └── Filename
│ │   │  │  │ │     │     │    └── Last modified date
│ │   │  │  │ │     │     └── File size in bytes
│ │   │  │  │ │     └── Group owner
│ │   │  │  │ └── User owner
│ │   │  │  └── Hard link count
│ │   │  └── Others permissions (r-x)
│ │   └── Group permissions (r-x)
│ └── Owner permissions (rwx)
└── File type (d=directory, -=file, l=symlink)
```

### Information Commands

```bash
# Who am I?
whoami              # Output: kunal

# System info
uname -a            # All system info
hostname            # Machine name
uptime              # How long system has been running
date                # Current date and time
cal                 # Calendar

# Manual pages
man ls              # Manual for ls command
man -k search_term  # Search manuals by keyword
info ls             # Detailed info pages
ls --help           # Quick help

# Command history
history             # Show command history
!123                # Run command number 123 from history
!!                  # Run last command
!ls                 # Run last command starting with "ls"
```

---

## 3. File Management

### Creating Files

```bash
# Create empty file
touch file.txt

# Create file with content
echo "Hello World" > file.txt         # Write (overwrites)
echo "Another line" >> file.txt       # Append

# Create file with multiple lines
cat > file.txt << EOF
Line 1
Line 2
Line 3
EOF

# Create file using editor
nano file.txt
vim file.txt
```

### Reading Files

```bash
# Display entire file
cat file.txt

# Display with line numbers
cat -n file.txt

# Display first/last lines
head file.txt           # First 10 lines (default)
head -n 5 file.txt      # First 5 lines
tail file.txt           # Last 10 lines
tail -n 5 file.txt      # Last 5 lines
tail -f /var/log/syslog  # Follow file in real-time (great for logs)

# Page through file
less file.txt           # Scrollable viewer (q to quit)
more file.txt           # Simpler pager

# Display specific lines
sed -n '5,10p' file.txt  # Lines 5 through 10
```

### Copying, Moving, Renaming, Deleting

```bash
# Copy
cp source.txt dest.txt          # Copy file
cp -r source_dir/ dest_dir/     # Copy directory recursively
cp -i source.txt dest.txt       # Interactive (ask before overwrite)
cp -v source.txt dest.txt       # Verbose (show what's copied)

# Move / Rename
mv oldname.txt newname.txt      # Rename file
mv file.txt /path/to/dir/       # Move file to directory
mv -i file.txt /path/to/dir/    # Ask before overwrite

# Delete
rm file.txt                     # Delete file
rm -i file.txt                  # Interactive delete
rm -r directory/                # Delete directory recursively
rm -rf directory/               # Force delete (⚠️ DANGEROUS — no confirmation)

# ⚠️ NEVER RUN: rm -rf /  (This deletes EVERYTHING on the system)
```

### File Information

```bash
# File type
file document.pdf       # Output: PDF document, version 1.4

# File size
du -h file.txt          # Disk usage of file
du -sh directory/       # Total size of directory
df -h                   # Disk space of all mounted filesystems

# Word/line/character count
wc file.txt             # Lines, words, characters
wc -l file.txt          # Line count only
wc -w file.txt          # Word count only

# Find differences between files
diff file1.txt file2.txt
diff -u file1.txt file2.txt   # Unified format (like git diff)
```

---

## 4. Directory Management

```bash
# Create directory
mkdir mydir                   # Single directory
mkdir -p parent/child/grand   # Create nested directories

# Remove directory
rmdir emptydir                # Only works on empty directories
rm -r mydir                   # Remove non-empty directory

# List directory tree
tree                          # Visual tree structure
tree -L 2                     # Limit depth to 2 levels
tree -d                       # Directories only

# Find files
find / -name "file.txt"              # Find by name (from root)
find . -name "*.java"                # Find all Java files in current dir
find . -type f -size +10M            # Files larger than 10MB
find . -type f -mtime -7             # Modified in last 7 days
find . -type f -name "*.log" -delete # Find and delete all .log files
find . -type f -exec chmod 644 {} \; # Find and execute command on each

# Locate (faster than find — uses database)
locate file.txt              # Quick search using pre-built index
sudo updatedb                # Update the locate database
```

---

## 5. File Permissions / Access Modes

### Understanding Permissions

Every file has three permission categories and three permission types:

```
Categories:  Owner (u)  |  Group (g)  |  Others (o)
Permissions:  r (read)  |  w (write)  |  x (execute)
```

### Permission Values

```
Permission  Symbol  Octal Value
---------  ------  -----------
Read         r        4
Write        w        2
Execute      x        1
None         -        0
```

### Reading Permissions

```
-rwxr-xr--
│ │││ │││ │││
│ ││└─Owner: rwx (4+2+1 = 7) — can read, write, execute
│ │└──Group: r-x (4+0+1 = 5) — can read and execute
│ └───Others: r-- (4+0+0 = 4) — can only read
└────File type: - (regular file)

So this permission = 754
```

### Changing Permissions

```bash
# Symbolic method
chmod u+x script.sh          # Add execute for owner
chmod g-w file.txt            # Remove write for group
chmod o=r file.txt            # Set others to read only
chmod a+r file.txt            # Add read for all (a = all)
chmod u+rwx,g+rx,o+r file.txt  # Multiple at once

# Numeric (Octal) method — most common
chmod 755 script.sh   # Owner: rwx, Group: r-x, Others: r-x
chmod 644 file.txt    # Owner: rw-, Group: r--, Others: r--
chmod 700 secret.sh   # Owner: rwx, Group: ---, Others: ---
chmod 777 file.txt    # ⚠️ Everyone can read, write, execute

# Common permission patterns
chmod 755 directory/    # Standard directory permission
chmod 644 file.txt      # Standard file permission
chmod 600 id_rsa        # SSH private key (owner only)
chmod 400 id_rsa        # SSH key read-only
```

### Changing Ownership

```bash
# Change owner
chown kunal file.txt

# Change owner and group
chown kunal:developers file.txt

# Recursive ownership change
chown -R kunal:kunal /home/kunal/project/
```

### Under the Hood: Special Permissions

```
SUID (Set User ID)    — 4xxx — File executes as the file owner
SGID (Set Group ID)   — 2xxx — File executes as the file group
Sticky Bit            — 1xxx — Only owner can delete files in directory

# Example: SUID on passwd command
ls -l /usr/bin/passwd
-rwsr-xr-x 1 root root 68208 ... /usr/bin/passwd
   ^
   └── 's' instead of 'x' means SUID is set
        (any user can change their password by temporarily running as root)

# Set SUID
chmod 4755 program

# Sticky bit on /tmp (common)
chmod 1777 /tmp
ls -ld /tmp
drwxrwxrwt 10 root root 4096 ... /tmp
         ^
         └── 't' means sticky bit is set
```

### Default Permissions: umask

```bash
# View current umask
umask
# Output: 0022

# How umask works:
# Default file permission:  666 (rw-rw-rw-)
# Minus umask:             -022
# Result:                   644 (rw-r--r--)

# Default directory permission: 777 (rwxrwxrwx)
# Minus umask:                 -022
# Result:                       755 (rwxr-xr-x)

# Set umask
umask 077    # Very restrictive: new files = 600, dirs = 700
```

---

## 6. Basic Utilities

### Text Display and Manipulation

```bash
# echo — display text
echo "Hello World"
echo -e "Line1\nLine2\tTabbed"    # -e enables escape sequences
echo $HOME                        # Display environment variable

# sort — sort lines
sort file.txt                     # Alphabetical sort
sort -n file.txt                  # Numeric sort
sort -r file.txt                  # Reverse sort
sort -u file.txt                  # Sort and remove duplicates
sort -t',' -k2 data.csv          # Sort by 2nd field (comma-delimited)

# uniq — remove adjacent duplicates (use with sort)
sort file.txt | uniq              # Remove duplicates
sort file.txt | uniq -c           # Count occurrences
sort file.txt | uniq -d           # Show only duplicates

# cut — extract columns
cut -d',' -f1,3 data.csv         # Fields 1 and 3, comma-delimited
cut -c1-10 file.txt              # Characters 1-10 of each line

# tr — translate/replace characters
echo "hello" | tr 'a-z' 'A-Z'    # Convert to uppercase: HELLO
echo "hello   world" | tr -s ' '  # Squeeze repeated spaces
cat file.txt | tr -d '\r'         # Remove carriage returns (Windows→Linux)

# paste — merge files side by side
paste file1.txt file2.txt

# tee — write to file AND stdout simultaneously
ls -la | tee output.txt           # Display and save
ls -la | tee -a output.txt       # Display and append
```

### Searching

```bash
# grep — search text patterns
grep "error" log.txt              # Find lines containing "error"
grep -i "error" log.txt           # Case-insensitive
grep -n "error" log.txt           # Show line numbers
grep -c "error" log.txt           # Count matching lines
grep -r "TODO" ./src/             # Recursive search in directory
grep -v "debug" log.txt           # Invert match (lines NOT containing)
grep -l "error" *.log             # List filenames with matches
grep -E "error|warning" log.txt   # Extended regex (OR)
grep -w "error" log.txt           # Match whole word only
grep -A3 "error" log.txt          # Show 3 lines after match
grep -B2 "error" log.txt          # Show 2 lines before match
grep -C2 "error" log.txt          # Show 2 lines before and after

# Regular expressions with grep
grep "^Start" file.txt            # Lines starting with "Start"
grep "end$" file.txt              # Lines ending with "end"
grep "^$" file.txt                # Empty lines
grep "[0-9]" file.txt             # Lines containing digits
grep -E "[0-9]{3}-[0-9]{4}" file.txt  # Phone number pattern
```

### Compression and Archiving

```bash
# tar — create archives
tar -cvf archive.tar dir/         # Create tar archive (verbose)
tar -xvf archive.tar              # Extract tar archive
tar -czvf archive.tar.gz dir/     # Create gzipped archive
tar -xzvf archive.tar.gz          # Extract gzipped archive
tar -tf archive.tar               # List contents without extracting

# gzip / gunzip
gzip file.txt                     # Compress → file.txt.gz
gunzip file.txt.gz                # Decompress → file.txt

# zip / unzip
zip archive.zip file1 file2       # Create zip
zip -r archive.zip directory/     # Zip directory
unzip archive.zip                 # Extract zip
unzip -l archive.zip              # List contents
```

---

## 7. Pipes and Filters

### The Pipe `|` Operator

Pipes connect the **stdout** of one command to the **stdin** of the next:

```bash
command1 | command2 | command3
```

### Under the Hood: How Pipes Work

```
┌──────────┐   stdout → stdin    ┌──────────┐   stdout → stdin    ┌──────────┐
│ command1 │ ──────────────────→ │ command2 │ ──────────────────→ │ command3 │
└──────────┘                     └──────────┘                     └──────────┘

The kernel creates an in-memory buffer between commands.
Data flows through without touching the disk.
Both commands run simultaneously (parallel execution).
```

### Practical Examples

```bash
# Count number of files in a directory
ls -1 | wc -l

# Find the 5 largest files in current directory
du -sh * | sort -rh | head -5

# Find all unique IP addresses in a log file
cat access.log | awk '{print $1}' | sort | uniq -c | sort -rn | head -10

# Find running Java processes
ps aux | grep java | grep -v grep

# Monitor log file for errors in real-time
tail -f /var/log/app.log | grep --color "ERROR"

# Count lines of code in a project (excluding blank lines)
find . -name "*.java" | xargs cat | grep -v "^$" | wc -l

# Extract and sort unique email addresses from a file
grep -oE "[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}" file.txt | sort -u

# Disk usage of top 10 largest directories
du -h --max-depth=1 / 2>/dev/null | sort -rh | head -10
```

### Redirection

```bash
# stdout redirection
command > file.txt       # Write stdout to file (overwrite)
command >> file.txt      # Append stdout to file

# stderr redirection
command 2> error.txt     # Write stderr to file
command 2>> error.txt    # Append stderr to file

# Both stdout and stderr
command > output.txt 2>&1      # Both to same file
command > output.txt 2> error.txt  # Separate files
command &> all_output.txt      # Shorthand: both to same file

# Discard output
command > /dev/null            # Discard stdout
command 2> /dev/null           # Discard stderr
command &> /dev/null           # Discard everything

# stdin redirection
command < input.txt            # Read stdin from file
sort < unsorted.txt > sorted.txt  # Sort file using redirection

# Here document
cat << EOF > config.txt
server=localhost
port=8080
debug=true
EOF
```

---

## 8. Process Management

### Viewing Processes

```bash
# ps — snapshot of current processes
ps                    # Processes for current user/terminal
ps aux                # All processes (BSD syntax)
ps -ef                # All processes (System V syntax)
ps aux --sort=-%mem   # Sort by memory usage (descending)
ps aux --sort=-%cpu   # Sort by CPU usage

# top — real-time process monitor
top                   # Interactive process viewer
top -u kunal          # Show only user's processes

# htop — better interactive viewer (install: sudo apt install htop)
htop
```

### Understanding `ps aux` Output

```
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
kunal     1234  2.5  1.2 123456 12345 pts/0    S    10:30   0:05 java -jar app.jar
│         │     │    │    │      │     │        │    │       │    │
│         │     │    │    │      │     │        │    │       │    └── Command
│         │     │    │    │      │     │        │    │       └── CPU time used
│         │     │    │    │      │     │        │    └── Start time
│         │     │    │    │      │     │        └── State (S=sleeping, R=running)
│         │     │    │    │      │     └── Terminal
│         │     │    │    │      └── Resident Set Size (physical memory)
│         │     │    │    └── Virtual Memory Size
│         │     │    └── % of RAM used
│         │     └── % of CPU used
│         └── Process ID
└── User running the process
```

### Managing Processes

```bash
# Run process in background
command &                         # Run in background
nohup command &                   # Run in background, survives terminal close
nohup command > output.log 2>&1 & # Background with output logging

# Job control
jobs                              # List background jobs
fg %1                             # Bring job 1 to foreground
bg %1                             # Resume job 1 in background
Ctrl+Z                            # Suspend current foreground process
Ctrl+C                            # Kill current foreground process

# Kill processes
kill PID                          # Send SIGTERM (graceful shutdown)
kill -9 PID                       # Send SIGKILL (force kill — last resort)
kill -15 PID                      # Send SIGTERM (same as default)
killall process_name              # Kill all processes by name
pkill -f "java -jar"             # Kill processes matching pattern

# Common signals
# SIGHUP  (1)  — Hangup (reload config)
# SIGINT  (2)  — Interrupt (Ctrl+C)
# SIGKILL (9)  — Force kill (cannot be caught)
# SIGTERM (15) — Graceful termination (default)
# SIGSTOP (19) — Pause process
# SIGCONT (18) — Resume paused process
```

### Process Priority (nice)

```bash
# Run with lower priority (nice value: -20 to 19, higher = lower priority)
nice -n 10 command               # Start with nice value 10
renice 5 -p PID                  # Change priority of running process

# Daemon processes
systemctl start nginx            # Start a service
systemctl stop nginx             # Stop a service
systemctl restart nginx          # Restart a service
systemctl status nginx           # Check service status
systemctl enable nginx           # Start on boot
systemctl disable nginx          # Don't start on boot
```

---

## 9. Network Communication Utilities

### Network Information

```bash
# IP address
ip addr show                      # Modern way
ifconfig                          # Traditional (deprecated)
hostname -I                       # Quick IP display

# Network connections
netstat -tuln                     # Listening ports
ss -tuln                          # Modern alternative to netstat
lsof -i :8080                    # What's using port 8080?

# DNS
nslookup google.com
dig google.com
host google.com

# Connectivity
ping google.com                   # Test connectivity
ping -c 5 google.com              # Send only 5 pings
traceroute google.com             # Trace route to host
```

### Downloading and Transferring

```bash
# wget — download files
wget https://example.com/file.zip
wget -O output.zip https://example.com/file.zip  # Custom output name
wget -q https://example.com/file.zip              # Quiet mode

# curl — transfer data (more versatile than wget)
curl https://api.example.com/data                  # GET request
curl -o file.zip https://example.com/file.zip      # Download file
curl -X POST -d '{"key":"value"}' -H "Content-Type: application/json" https://api.example.com/data
curl -I https://example.com                        # Headers only

# scp — secure copy over SSH
scp file.txt user@remote:/path/to/dest/            # Upload
scp user@remote:/path/to/file.txt ./               # Download
scp -r directory/ user@remote:/path/               # Copy directory

# SSH — secure remote access
ssh user@remote-server
ssh -p 2222 user@remote-server                     # Custom port
ssh -i ~/.ssh/id_rsa user@remote-server            # Specific key
```

---

## 10. Essential One-Liners Cheat Sheet

```bash
# System
free -h                           # Memory usage
df -h                             # Disk usage
lsblk                             # Block devices
cat /etc/os-release               # OS version
cat /proc/cpuinfo | grep "model name" | head -1  # CPU info

# User management
sudo adduser newuser              # Create user
sudo usermod -aG sudo newuser     # Add to sudo group
sudo passwd newuser               # Set password
su - newuser                      # Switch user

# Environment variables
echo $PATH                        # View PATH
export MY_VAR="value"             # Set variable (current session)
echo 'export MY_VAR="value"' >> ~/.bashrc  # Permanent
source ~/.bashrc                  # Reload config

# Cron jobs (scheduled tasks)
crontab -e                        # Edit cron jobs
crontab -l                        # List cron jobs

# Cron format: minute hour day month weekday command
# Example: Run backup every day at 2:30 AM
# 30 2 * * * /path/to/backup.sh
```
