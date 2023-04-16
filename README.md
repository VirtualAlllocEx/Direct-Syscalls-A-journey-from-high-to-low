# Direct-Syscalls-A-journey-from-high-to-low
Start with shellcode execution using Windows APIs (high level), move on to native APIs (medium level) and finally to direct syscalls (low level).

The technique of direct system calls is no longer a new attack technique for Red Teamers today (April 2023). I myself have covered this topic several times (DeepSec Vienna 2020) and there are already a large number of well-written articles and useful code repositories on the Internet. Nevertheless, I would like to revisit the topic and look at various aspects related to direct system calls.

More details in my related blog post https://redops.at/en/blog/direct-syscalls-a-journey-from-high-to-low

# **Disclaimer**
The content and all code examples in this article are for research purposes only and must not be used in an unethical context! The code used is not new and I make no claim to it. Most of the code comes, as so often, from the **ired.team, thank you @spotheplanet for your brilliant work and sharing it with us all!**
For the syscall POCs, **Syswhispers2** was used, also thanks to **@Jackson_T** for providing this very helpful code. 

# **References** 

- https://sevrosecurity.com/2020/04/08/process-injection-part-1-createremotethread/
- https://www.ired.team/offensive-security/code-injection-process-injection/process-injection
- https://www.ired.team/offensive-security/code-injection-process-injection/loading-and-executing-shellcode-from-portable-executable-resources
- https://github.com/jthuraisamy/SysWhispers2
- https://outflank.nl/blog/2019/06/19/red-team-tactics-combining-direct-system-calls-and-srdi-to-bypass-av-edr/
- https://klezvirus.github.io/RedTeaming/AV_Evasion/NoSysWhisper/
