#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

char *word;

void searchfile(const char* name){
    FILE *fd = fopen(name, "r");
    if (fd < 0){
	perror("Can't open the file");
	exit(1);
    }

    char buf[1024];
    int count = 0;
    while ((fgets(buf, sizeof(buf), fd)) != NULL){
	if (strstr(buf, word)){
	    count++;
	    printf("%s %d строка: %s", name, count, buf);
	}

	else
	    count++;
    }
    
    fclose(fd);
}

void dirlist(const char* name){
    DIR *dir;
    struct dirent* entry;

    if (!(dir = opendir(name))){
	perror("Can't open directory");
	exit(1);
    }

    while ((entry = readdir(dir)) != 0){
	if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
	    continue;
	char path[1024];
	snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
	if (entry->d_type == DT_DIR)
	    dirlist(path);

	else if (entry->d_type == DT_REG)
	    searchfile(path);
    }
    closedir(dir);
}

int main(int argc, char *argv[]){
    char *dir;
    if (argc == 3){
	dir = argv[1];
	word = argv[2];
    }

    else if (argc == 2){
	char *home;
	home = getenv("HOME");
	if(!home){
	    perror("Директория по умолчанию и переменная HOME не заданы");
	    exit(1);
	}

	dir = home;
	word = argv[1];
    }

    else{
	fprintf(stderr, "Использование: %s [директория] слово\n", argv[0]);
	exit(1);
    }

    dirlist(dir);
    return 0;
}
