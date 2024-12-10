# Check Password Brute Force Cracker

This project is a simple brute force password cracker that attempts to break a 3-character password by checking all possible combinations of ASCII printable characters. It supports both multi-process and single-process password cracking.

## How It Works

### Brute Force Process
- The program uses nested loops to iterate through all combinations of 3 printable ASCII characters (from ASCII 33 to 126).
- Each process attempts to find the correct password by testing combinations in parallel (if forking is enabled).
- The password is checked using a helper function `checkPassword`, which returns 0 when the correct password is found.

### Multi-Process Cracking (with `-f` flag)
- When the `-f` flag is provided, the program forks into 4 child processes.
- Each process is responsible for a portion of the total search space (i.e., each process checks different sets of password combinations).
- If one of the processes finds the correct password, it reports it and terminates.

### Single-Process Cracking (without `-f` flag)
- Without the `-f` flag, the program runs in a single process and iterates over all the possible combinations of 3 characters.

### Example Execution

1. **Multi-Process Cracking**:
   ```bash
   ./bruteForce -f
### Example Execution

1. **Multi-Process Cracking**:
   - Command:
     ```bash
     ./bruteForce -f
     ```

2. **Single-Process Cracking**:
   - Command:
     ```bash
     ./bruteForce
     ```

Example logs are attached as a photo
