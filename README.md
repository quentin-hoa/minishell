# Minishell - Unix Shell with Binary Tree Command Orchestration

A fully functional Unix shell interpreter supporting process execution, environment management, and complex command structures through binary tree-based parsing.

## Architecture Overview

Minishell operates in three distinct phases:

1. **Parsing Phase**: Convert command string → binary tree (respecting operator precedence)
2. **Tree Execution Phase**: Recursively traverse tree, executing nodes and managing pipes/redirections
3. **Cleanup Phase**: Deallocate resources, handle zombie processes

## Core Component: Command Parsing via Binary Tree

### Why Binary Tree?

Operators have **different precedences**:
- Semicolon (`;`): lowest precedence — execute left, then right sequentially
- Pipe (`|`): medium precedence — chain left output to right input
- Redirections (`<`, `>`, `<<`, `>>`): highest precedence — bind to adjacent command

Tree structure naturally enforces precedence: higher precedence operators create leaf nodes closer to leaves.

### Parse Procedure: Right-Associative Parsing

Process operators in **reverse precedence order** (lowest first):

```
Input: "ls -l | grep test > output.txt ; echo done"

Step 1: Find semicolon (lowest precedence)
├─ Left: "ls -l | grep test > output.txt"
└─ Right: "echo done"

Step 2a: Parse left side — find redirection '>'
├─ Left: "ls -l | grep test"
└─ Right: "output.txt"

Step 2b: Parse left of redirection — find pipe '|'
├─ Left: "ls -l"
└─ Right: "grep test"

Result tree:
        SEMI_COL
       /        \
    REDIR_R    CMD(echo)
    /    \
  PIPE  output.txt
  / \
CMD CMD
```

### Parsing Code Pattern

```c
// Check operator in precedence order
treenode_t *build_tree(char *line) {
    // 1. Check semicolon (lowest precedence)
    treenode_t *node = check_semi(line, NULL);
    if (node) return node;
    
    // 2. Check pipe
    node = check_pipe(line, NULL);
    if (node) return node;
    
    // 3. Check redirections
    node = check_redir_r(line, NULL);  // > and >>
    if (node) return node;
    
    node = check_redir_l(line, NULL);  // < and <<
    if (node) return node;
    
    // 4. Base case: simple command
    return crea_tree_node(parse_args(line), CMD);
}
```

Each check splits the line at the **first occurrence** of that operator (searching right-to-left to preserve precedence).

## Execution Engine: Recursive Tree Traversal

### Tree Node Types

```c
typedef enum {
    CMD,        // Leaf: execute command
    PIPE,       // Connect stdout of left to stdin of right
    REDIR_R,    // Redirect stdout to file
    APPEND,     // Append stdout to file (>>)
    REDIR_L,    // Redirect file to stdin
    HEREDOC,    // Here-document (<<)
    SEMI_COL    // Execute left, discard output, execute right
} type_t;

typedef struct treenode {
    char **args;              // Command arguments (for CMD nodes)
    type_t type;              // Node type
    struct treenode *left;    // Subtree
    struct treenode *right;   // Subtree
} treenode_t;
```

### Recursive Execution: `execute_tree()`

```c
int execute_tree(treenode_t *node, env_t **env, int *last_status) {
    if (!node) return 0;
    
    if (node->type == SEMI_COL) {
        // Execute left, discard output, execute right
        execute_tree(node->left, env, last_status);
        return execute_tree(node->right, env, last_status);
    }
    
    if (node->type == PIPE) {
        // Fork twice: left process → pipe → right process
        return execute_pipe(node, env, last_status);
    }
    
    if (node->type == REDIR_R || node->type == APPEND) {
        return execute_redir_r(node, env, last_status);
    }
    
    if (node->type == REDIR_L || node->type == HEREDOC) {
        return execute_redir_l(node, env, last_status);
    }
    
    if (node->type == CMD) {
        return run_simple_cmd(node->args, env, last_status);
    }
}
```

### Pipe Execution: Dual-Fork Strategy

For `left | right`:

```
Parent
├─ Fork 1 (left process)
│  ├─ Close reading end of pipe
│  ├─ Redirect stdout to pipe writing end
│  └─ execve() left command
│
├─ Fork 2 (right process)
│  ├─ Close writing end of pipe
│  ├─ Redirect stdin to pipe reading end
│  └─ execve() right command
│
└─ Wait for both children
```

Key: Both processes are **children of the shell** (not parent-child), connected only by the pipe.

## Built-in Commands

### Structure: Linked List Environment

```c
typedef struct env {
    char *var_name;      // "PATH", "HOME", etc.
    char *var_content;   // Value
    struct env *next;
} env_t;
```

Environment is a linked list, modified by:
- `setenv NAME VALUE`: Add/update variable
- `unsetenv NAME`: Remove variable
- `env`: Print all variables

### Command Implementations

1. **`cd`**: Change directory
   - Parse argument
   - Call `chdir()`
   - Update `PWD` in environment
   - Update `OLDPWD` for dash (`cd -`)

2. **`exit`**: Terminate shell
   - Optional argument: exit code
   - Free all memory
   - Exit with status

3. **PATH Resolution**: 
   - Search each directory in `PATH` for executable
   - Use `access()` to check executability
   - Fall back to absolute/relative paths

## Data Flow Example

Input: `ls | wc -l`

1. **Parse**: Build tree
   ```
   PIPE
   ├─ CMD(ls)
   └─ CMD(wc -l)
   ```

2. **Execute**:
   - Create pipe with `pipe()`
   - Fork `ls`: redirect stdout to pipe write end
   - Fork `wc`: redirect stdin to pipe read end
   - Parent waits for both
   - Shell prints final line count

3. **Status**: Set `$?` to exit code of rightmost command (standard behavior)

## How to Use

### Compilation
```bash
make
```

### Execution: Interactive Mode
```bash
./mysh
$> ls -la
$> cd /tmp
$> pwd
$> exit
```

### Execution: Scripted Mode
```bash
echo "mkdir test && cd test && touch file.txt" | ./mysh
./mysh < script.sh
```

### Examples

**Simple command:**
```bash
$> ls /tmp
```

**Pipe chain:**
```bash
$> cat file.txt | grep "pattern" | wc -l
```

**Redirection:**
```bash
$> echo "hello" > output.txt
$> cat < input.txt > output.txt
```

**Complex chain (demonstrating operator precedence):**
```bash
$> (cat file1 | grep x) > result.txt ; echo done
```

The shell correctly parses, builds the tree respecting precedence, executes both branches of the semicolon, and returns the exit code of `echo done`.

## Behavioral Features

- **Prompt**: `$> ` (displayed only in interactive mode)
- **Exit Status**: Propagates from executed commands (`$?`)
- **Path Searching**: Finds executables in `PATH` directories
- **Environment Preservation**: Child processes inherit modified environment
- **Zombie Prevention**: Proper `waitpid()` handling for all forked processes
