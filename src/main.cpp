#include <cstdio>
#include <emscripten/emscripten.h>
#include <iostream>
#include <unistd.h>

#ifndef EM_PORT_API
#if defined(__EMSCRIPTEN__)
#if defined(__cplusplus)
#define EM_PORT_API(rettype) extern "C" rettype EMSCRIPTEN_KEEPALIVE
#else
#define EM_PORT_API(rettype) rettype EMSCRIPTEN_KEEPALIVE
#endif
#else
#if defined(__cplusplus)
#define EM_PORT_API(rettype) extern "C" rettype
#else
#define EM_PORT_API(rettype) rettype
#endif
#endif
#endif
void sync_idbfs() {
	EM_ASM(
		FS.syncfs(function (err) {});
	);
}

EM_PORT_API(void) test() {
	FILE* fp = fopen("/data/nodefs_data.txt", "r+t");
	if (fp == NULL) fp = fopen("/data/nodefs_data.txt", "w+t");
	int count = 0;
	if (fp) {
    std::cout << count << "进入了" << std::endl;
    std::cout << fp << std::endl;
		fscanf(fp, "%d", &count);
		count++;
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%d", count);
		fclose(fp);
    std::cout << "准备打印" << std::endl;
		printf("count:%dn", count);
    std::cout << "打印了" << std::endl;
		sync_idbfs();
    std::cout << count << std::endl;
	}
	else {
		printf("fopen failed.n");
    std::cout << count << "进入但失败" << std::endl;
	}
}

int main() {
	EM_ASM(
		FS.mkdir('/data');
		FS.mount(IDBFS, {}, '/data');
		FS.syncfs(true, function (err) {
			assert(!err);
			ccall('test', 'v');
		});
    console.log('hello world');
	);

	return 0;
}