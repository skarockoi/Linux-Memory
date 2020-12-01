#ifndef _PROCESS_HPP_
#define _PROCESS_HPP_

#include <unistd.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/uio.h>

class ReadWriteFactory
{
public:
    void ReadMemoryChunk(uint32_t processid, uint64_t address, void* receiver ,size_t size){
        struct iovec local;
        struct iovec remote;
      
        local.iov_base = (void *) receiver;
        local.iov_len = size;

        remote.iov_base = (void *) address;
        remote.iov_len = size; 

        ssize_t nread = process_vm_readv(processid, &local, 2, &remote, 1, 0);
    }

    template <typename T>
    T ReadMemory(uint32_t processid, uint64_t address){
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

	void WriteBytes(uint32_t processId, uint64_t address, std::vector<uint8_t> patch){
        
        struct iovec local;
        struct iovec remote;
      
        local.iov_base = &patch;
        local.iov_len = patch.size();

        remote.iov_base = (void *) address;
        remote.iov_len = sizeof(address); 

        process_vm_writev(processId, &local, 2, &remote, 1, 0);
    }

    template <typename T>
    void WriteMemory(uint32_t processId, uint64_t address, T value){
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
    pid_t procId = 0; 
    pid_t base = 0;

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

        this->procId = pid;

        char *cstr = new char[procName.length() + 1];
        strcpy(cstr, procName.c_str());
        this->base = this->getModule(cstr);
        delete [] cstr;
    }

    uint64_t getModule(char* name) {
        char cmd[200];
        sprintf(cmd, "cat /proc/%d/maps | grep %s -m1 | cut -d '-' -f1", this->procId, name);
        FILE *f = popen(cmd, "r");
        char line[20];
        fgets(line, 20, f);
        pclose(f);
        return strtoul(line, NULL, 16);
    }
    
    template <typename T>
    T   read(uint64_t addr){
        return ReadMemory<T>(procId, addr);
    }

    template <typename T>
    void write(uint64_t addr, T value){
        WriteMemory<T>(procId, addr, value);      
    }

    void writeBytes(uint64_t address, std::vector<uint8_t> patch){
        WriteBytes(this->procId, address, patch);
    }

    template <typename T>
    T readMulti(uint64_t base, std::vector<uint32_t> offsets){
		uint64_t buffer = base;
		for (int i = 0; i < offsets.size() - 1; i++)      
        {
            buffer = this->read<uint64_t>(buffer + offsets[i]);
        }   
		return this->read<T>(buffer + offsets.back());
	}

    uint64_t readMultiAddr(uint64_t base, std::vector<uint32_t> offsets){
        uint64_t addr = base;
		for (unsigned int i = 0; i < offsets.size() - 1; i++)
		{
            addr = ReadMemory<uint64_t>(this->procId, addr + offsets[i]);
		}
		return addr + offsets.back();
	}
};
#endif