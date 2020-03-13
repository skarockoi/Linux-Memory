#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/uio.h>

class ReadWriteFactory
{
public:
    template <typename T>
    T ReadMemoryRaw(int processid, ulong address)
    {
        T buf = 0;
          
        struct iovec local;
        struct iovec remote;
      
        local.iov_base = &buf;
        local.iov_len = sizeof(T);

        remote.iov_base = (void *) address;
        remote.iov_len = sizeof(T); 

        ssize_t nread = process_vm_readv(processid, &local, 2, &remote, 1, 0);
        
        return buf;
    }

    template <typename T>
    void WriteMemoryRaw(int processId, ulong address, T value)
    {
        T   buf = 0;
        T   newVal = value;
        
        struct iovec local;
        struct iovec remote;
      
        local.iov_base = &newVal;
        local.iov_len = sizeof(T);

        remote.iov_base = (void *) address;
        remote.iov_len = sizeof(T); 

        process_vm_writev(processId, &local, 2, &remote, 1, 0);
    }
};



class Process : public ReadWriteFactory
{
public:
    void getProcess(std::string procName)
    {
        int pid = -1;
        DIR *dp = opendir("/proc");
        if (dp != NULL)
        {
            struct dirent *dirp;
            while (pid < 0 && (dirp = readdir(dp)))
            {
                int id = atoi(dirp->d_name);
                if (id > 0)
                {
                    std::string cmdPath = std::string("/proc/") + dirp->d_name + "/cmdline";
                    std::ifstream cmdFile(cmdPath.c_str());
                    std::string cmdLine;
                    std::getline(cmdFile, cmdLine);
                    if (!cmdLine.empty())
                    {
                        size_t pos = cmdLine.find('\0');
                        if (pos != std::string::npos)
                            cmdLine = cmdLine.substr(0, pos);
                        pos = cmdLine.rfind('/');
                        if (pos != std::string::npos)
                            cmdLine = cmdLine.substr(pos + 1);
                        if (procName == cmdLine)
                            pid = id;
                    }
                }
            }
        }
        closedir(dp);
        procId = pid;
    }
    
    int* getProcId()
    {
        return &procId;
    }
    
    template <typename T>
    T   read(ulong addr)
    {
        return ReadMemoryRaw<T>(procId, addr);
    }

    template <typename T>
    void write (ulong addr, T value)
    {
        WriteMemoryRaw<T>(procId, addr, value);      
    }
    
private:
    int procId = 0; 
};


Process mem;

int main ()
{
    mem.getProcess("RestingGame");

    int   readInt = mem.read<int>(0x7fffffffde00);
    float readFloat = mem.read<float>(0x7fffffffde04);
    bool  readBool = mem.read<bool>(0x7fffffffddff);
    
    std::cout << readInt << std::endl;
    std::cout << readFloat << std::endl;
    std::cout << readBool << std::endl; 
    
    mem.write<int>(0x7fffffffde00, 500);
    mem.write<float>(0x7fffffffde04, 300.6);
    mem.write<bool>(0x7fffffffddff, 0);
}
