#ifndef _DATAWRAPPER_HPP_
#define _DATAWRAPPER_HPP_

#include <memory>
#include "Process.hpp"

template <uintptr_t maxSize> class DataWrapper : protected ReadWriteFactory
{   
public:
    DataWrapper ();
	DataWrapper(pid_t pid){
		this->procId = pid;
		this->data = std::make_unique<uint8_t[]>(maxSize);
		this->max_offset = maxSize;
	}

    void update(uint64_t baseAddress){
		this->base = baseAddress;
		ReadMemoryChunk(procId, baseAddress, this->data.get(), this->max_offset);		
	}

    template <typename T>
	T read(uint64_t offset){
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(&this->data[offset]));
	}

    template<class T>
	void write(uint64_t offset, T value){
		WriteMemory(procId, base + offset, value);
	}

protected:
	std::unique_ptr<uint8_t[]> data;
	pid_t  procId = 0;
	uint64_t base = 0x0;
	uint64_t max_offset = 0x0;
};
#endif