# HyperShell
A command-line tool to run multiple commands in parallel across multiple machines.
## Sample use case
```sh
# Remote
hypershell ssh --user dave --hosts code@server1,code@server2 --cmd "ls -l" --cmd "df -h"

# Local
hypershell local --cmd "ls -l" --cmd "df -h"
```