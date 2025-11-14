# HyperShell
A command-line tool to run multiple commands in parallel across multiple machines.
## Sample use case
```sh
# Remote
hypershell ssh --user dave password Oces2023 --hosts code@server1 "ls -l" --cmd "df -h"

# Local
hypershell local --cmd "ls -l" --cmd "df -h"
```