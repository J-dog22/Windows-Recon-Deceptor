# Windows-Recon-Deceptor
Spoofs some common functionalities of Windows native tools (Net.exe, whoami.exe, ipconfig.exe) often used for reconaissance on a compromised system.

The three "Deceptive" binaries closely mimic the functionalities of the real tool; however, the binaries will return false information that has been configured beforehand (files found in the **Results_files** directory). This project was written and tested using C++17.

## Startup ##
To implement this project, you will need to execute the batch file: 
```
IFEO_change.bat
```
This batch file makes changes to the registry by modifying the Image File Execution Options (IFEO) by adding a new key. This will allow the system to intercept attempts to execute either of the original binaries and redirect the execution on the "Deceptive" binaries in the project. 

## Usage ##
These tools mimic some of the more common commnads used by the orginial binaries. Less common commands, in terms of their usage for recon, will not be functional. However, they will be listed in the help pages to make the tools more deceptive. The following commands are supported for their perspective binaries:

### Net.exe ###
```
Net.exe[<UserName> <Password>] [/add | /delete]
```
```
Net.exe localgroup [<GroupName> <Name>] {/add | /delete}
```
```
Net.exe group [<GroupName> <UserName>] {/add | /delete}  
```  
```
Net.exe <ShareName> [<Drive>:<DirectoryPath] [/delete]
```
### ipconfig.exe ###
```
ipconfig [/all]
```

### whoami.exe ###
```
whoami {[/user] [/groups] [/priv]} [/all]
```

## Restoring System ##
To return the computer back to normal operation (Before the IFEO keys were modified), simply execute the batch file:
```
IFEO_restore.bat
```


