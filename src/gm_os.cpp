#pragma once
#include "gm2.h"

namespace gm
{
	//正确处理lua端字符的函数
	std::wstring Convert(const char* ptr)
	{
		size_t len = mbstowcs(nullptr, ptr, 0);
		wchar_t* str1 = new wchar_t[len + 1];
		mbstowcs(str1, ptr, len + 1);
		const wchar_t* str2 = str1;
		return str2;
	}

	const char* ReConvert(std::wstring str)
	{
		//setlocale(LC_ALL, ".936");  // Windows GBK;
		size_t len = wcstombs(nullptr, str.c_str(), 0);
		char* str1 = new char[len + 1];
		wcstombs(str1, str.c_str(), len + 1);
		const char* str2 = str1;
		return str2;
	}

#ifdef _WIN32
#include<windows.h>
	void GetFullPath(std::string& sname,char* buffer)
	{
		GetFullPathNameA(sname.c_str(), MAX_PATH, buffer, NULL);
	}
#ifdef USER_DEBUG

	std::string OutInfo()
	{
		std::string tem;
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "Pool Memory Used(byte): %lld\n", GetMemoryUsed());
		tem += buffer;
		/*snprintf(buffer, sizeof(buffer), "Pool Memory Capacity(byte): %lld\n", GetPoolCapacity());
		tem += buffer;*/
		snprintf(buffer, sizeof(buffer), "Dynamic Interval(ms): %.2f\n", GetInterval());
		tem += buffer;
		snprintf(buffer, sizeof(buffer), "UpdateData Interval(ms): %.2f\n", GetUInterval());
		tem += buffer;
		snprintf(buffer, sizeof(buffer), "Render Interval(ms): %.2f\n", GetRInterval());
		tem += buffer;
		snprintf(buffer, sizeof(buffer), "Entity count: %lld\n", entity_count);
		tem += buffer;
		snprintf(buffer, sizeof(buffer), "Image count: %lld\n", image_count);
		tem += buffer;
		snprintf(buffer, sizeof(buffer), "Text count: %lld\n", text_count);
		tem += buffer;
		snprintf(buffer, sizeof(buffer), "Audio count: %lld\n", audio_count);
		tem += buffer;
		return tem;

	}

	void pipe_connect()
	{
		while (1)
		{
			HANDLE hPipe = CreateNamedPipe(
				Convert("\\\\.\\pipe\\gm_perf").c_str(),
				PIPE_ACCESS_OUTBOUND,
				PIPE_TYPE_BYTE | PIPE_WAIT,
				1,
				4096,
				4096,
				0,
				NULL);

			if (hPipe == INVALID_HANDLE_VALUE) {
				Sleep(1000);
				continue;
			}

			BOOL connected = ConnectNamedPipe(hPipe, NULL) ?
				TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

			if (!connected) {
				CloseHandle(hPipe);
				Sleep(1000);
				continue;
			}

			while (1)
			{
				std::string msg = OutInfo();
				if (msg.empty() || msg.back() != '\n') msg += '\n';

				DWORD written = 0;
				BOOL ok = WriteFile(hPipe, msg.data(), msg.size(), &written, NULL);

				// 客户端断开 → 跳出内层循环，重新等新客户端
				if (!ok || written != msg.size()) break;

				Sleep(1000);
			}

			DisconnectNamedPipe(hPipe);
			CloseHandle(hPipe);
		}
	}
#endif

	int BlockExecuteProcess(const char* path)
	{
		STARTUPINFOA si = { 0 };
		si.cb = sizeof(si);
		PROCESS_INFORMATION pi = { 0 };

		// 注意：lpCommandLine 必须可写，不能用字符串字面量
		size_t size = strlen(path);
		char* temp = (char*)malloc(size+1);
		snprintf(temp, size, path);
		strcpy(temp, path);


		BOOL ok = CreateProcessA(
			NULL,           // 可执行文件路径，NULL 表示从 cmdLine 解析
			temp,        // 命令行（必须可写）
			NULL,           // 进程安全属性
			NULL,           // 线程安全属性
			FALSE,          // 不继承句柄
			0,              // 创建标志
			NULL,           // 继承环境变量
			NULL,           // 继承工作目录
			&si,            // 启动信息
			&pi             // 进程信息（输出）
		);
		free(temp);
		if (!ok) 
		{
			printf("失败: %lu\n", GetLastError());
			return 1;
		}

		// 等待进程结束
		WaitForSingleObject(pi.hProcess, INFINITE);

		DWORD exitCode;
		GetExitCodeProcess(pi.hProcess, &exitCode);

		// 必须关闭句柄
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return exitCode;
	}

	void deletefile(const char* path) 
	{
		if (!DeleteFileA(path)) 
		{
			DWORD err = GetLastError();
			if (err == ERROR_FILE_NOT_FOUND) {
				printf("文件不存在: %s\n", path);
			}
			else {
				printf("删除失败: %s, 错误码: %lu\n", path, err);
			}
		}
	}

	// 获取文件的最后修改时间
	BOOL GetFileWriteTime(const char* path, FILETIME* ft) 
	{
		HANDLE h = CreateFileA(
			path,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		if (h == INVALID_HANDLE_VALUE) 
		{
			return FALSE;
		}
		BOOL ok = GetFileTime(h, NULL, NULL, ft);
		CloseHandle(h);
		return ok;
	}
	
	bool IsNewer(const char* file1, const char* file2)
	{
		FILETIME ft1, ft2;
		if (!GetFileWriteTime(file1, &ft1))
		{
			return FALSE;
		}
		if (!GetFileWriteTime(file2, &ft2))
		{
			return TRUE;
		}
		return CompareFileTime(&ft1, &ft2) > 0;
	}

	void SetConsole()
	{
		// 设置控制台输出代码页为 UTF-8
		SetConsoleOutputCP(65001);
		// 设置控制台输入代码页为 UTF-8
		SetConsoleCP(65001);
	}


	std::vector<std::string>* GetDirectoryFileName(std::string path)
	{

		WIN32_FIND_DATAW  lpFindFileData;
		path += "*";
		std::vector<std::string>* pr1 = new std::vector<std::string>;
		std::wstring str = Convert(path.c_str());
		HANDLE pr = FindFirstFileW(str.c_str(), &lpFindFileData);
		if (pr == INVALID_HANDLE_VALUE)
		{
			std::cout << "对应文件夹不存在" << std::endl;
			return nullptr;
		}
		else
		{

			bool exist = true;
			while (exist != false)
			{
				if (wcscmp(lpFindFileData.cFileName, L".") != 0 && wcscmp(lpFindFileData.cFileName, L"..") != 0)
				{
					pr1->push_back(ReConvert(lpFindFileData.cFileName));
				}
				exist = FindNextFileW(pr, &lpFindFileData);
			}
			FindClose(pr);
			return pr1;
		}

	}



	bool isDirectory(const std::string& path)
	{
		DWORD attributes = GetFileAttributesA(path.c_str());

		if (attributes == INVALID_FILE_ATTRIBUTES) {
			// 文件不存在或无法访问
			return false;
		}

		// 检查是否包含 FILE_ATTRIBUTE_DIRECTORY 标志
		return (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}

	std::vector<std::string>* FGetDirectoryFileName(std::string path)
	{

		WIN32_FIND_DATAW  lpFindFileData;
		std::string tem = path;
		tem += "//";
		std::vector<std::string>* pr1 = new std::vector<std::string>;
		std::vector<std::string> d;
		d.push_back((path + "//*").c_str());
		
		int cnt = 0;
		while (d.size() >= cnt+1)
		{
			
			std::wstring str = Convert(d[cnt].c_str());
			HANDLE pr = FindFirstFileW(str.c_str(), &lpFindFileData);
			if (pr == INVALID_HANDLE_VALUE)
			{
				std::cout << "对应文件夹不存在" << std::endl;
				return nullptr;
			}
			bool exist = true;
			while (exist != false)
			{
				if (wcscmp(lpFindFileData.cFileName, L".") != 0 && wcscmp(lpFindFileData.cFileName, L"..") != 0)
				{
					std::string temp = ReConvert(lpFindFileData.cFileName);
					if (isDirectory(tem + temp) == true)
					{
						std::string tem_val = d[cnt];
						tem_val.pop_back();
						tem_val.pop_back();
						d.push_back(tem_val+temp+"//*");
					}
					else
					{
						std::string tem_val = d[cnt];
						tem_val.pop_back();
						tem_val.pop_back();
						pr1->push_back(tem_val+temp);
						
					}

				}
				exist = FindNextFileW(pr, &lpFindFileData);
			}

			FindClose(pr);
			
			
			cnt++;
			
		}
		return pr1;
	}

	void WriteNewFile(const char* name,void* buffer,size_t size)
	{
		// 1. 创建/打开文件
		HANDLE hFile = CreateFileA(
			name,                 // 文件名
			GENERIC_WRITE,              // 写入权限
			0,                          // 不共享（独占）
			NULL,                       // 默认安全属性
			CREATE_ALWAYS,              // 总是创建新文件（覆盖）
			FILE_ATTRIBUTE_NORMAL,      // 普通文件
			NULL                        // 无模板文件
		);

		if (hFile == INVALID_HANDLE_VALUE) 
		{
			std::cerr << "打开文件失败，错误码: " << GetLastError() << std::endl;
			exit(1);
		}

		// 2. 写入数据
		const char* data = "Hello, Windows API!";
		DWORD bytesWritten = 0;
		BOOL success = WriteFile(
			hFile,                      // 文件句柄
			buffer,                       // 要写入的数据
			size,        // 要写入的字节数
			&bytesWritten,              // 实际写入的字节数（返回）
			NULL                        // 同步模式，不需要OVERLAPPED
		);

		if (success ) 
		{
			if (bytesWritten != size)
			{
				std::cerr << "写入数据缺失 "<< std::endl;
				CloseHandle(hFile);
				exit(1);
			}
			
		}
		else 
		{
			std::cerr << "写入失败，错误码: " << GetLastError() << std::endl;
			CloseHandle(hFile);
			exit(1);
		}

		// 3. 关闭文件句柄
		CloseHandle(hFile);
	}

	size_t ReadFile(const char* name, void** buf)
	{
		// 1. 打开已有文件
		HANDLE hFile = CreateFileA(
			name,
			GENERIC_READ,               // 只读
			FILE_SHARE_READ,            // 允许其他进程同时读取
			NULL,
			OPEN_EXISTING,              // 文件必须存在
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFile == INVALID_HANDLE_VALUE) 
		{
			std::cerr << "打开文件失败，错误码: " << GetLastError() << std::endl;
			exit(1);
		}

		// 2. 获取文件大小（用于分配缓冲区）
		DWORD fileSize = GetFileSize(hFile, NULL);
		void* buffer=malloc(fileSize);  // +1 留个'\0'
		// 3. 读取数据
		DWORD bytesRead = 0;
		BOOL success = ReadFile(
			hFile,
			buffer,
			fileSize,
			&bytesRead,
			NULL
		);

		if (success && bytesRead > 0) 
		{
			if (bytesRead != fileSize)
			{
				std::cerr << "读取数据缺失 " << std::endl;
				CloseHandle(hFile);
				free(buffer);
				exit(1);
			}
		
		}
		else 
		{
			std::cerr << "读取失败，错误码: " << GetLastError() << std::endl;
			CloseHandle(hFile);
			free(buffer);
			exit(1);
		}

		CloseHandle(hFile);
		*buf = buffer;
		return fileSize;
	}

	bool DirectoryExists(const std::wstring& path) 
	{
		DWORD attrs = GetFileAttributesW(path.c_str());

		if (attrs == INVALID_FILE_ATTRIBUTES) 
		{
			return false;  
		}

		return (attrs & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}


	void CreateDirectoryRecursive(const std::string& fullPath) 
	{
		std::vector<std::string> tem;
		int last_count = 0;
		for (int i=0;i<fullPath.size();i++)
		{
			if ((fullPath[i] == '\\' || fullPath[i] == '/')&&i-last_count>1)
			{
				tem.push_back(fullPath.substr(last_count, i - last_count));
				last_count = i;
			}
		}

		int cnt = 0;
		std::string temp;
		for (auto& e:tem)
		{
			temp += e;
			if (cnt != 0)
			{
				std::wstring t = Convert(temp.c_str());
				if (DirectoryExists(t) == false)
				{
					if (CreateDirectory(t.c_str(), NULL)==false)
					{
						//创建失败
						std::cout << "创建目录失败" << std::endl;
						exit(1);
					}
				}
			}
			
			cnt++;
		}
	}
#endif
}