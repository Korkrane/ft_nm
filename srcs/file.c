#include "../includes/ft_nm.h"

bool openFile(char *path, int *fd)
{
	if((*fd = open(path, O_RDONLY)) < 0)
		return false;
	return true;
}

void closeFile(int fd)
{
	if(close(fd) < 0)
		errorExit("close");
}

bool getFileStatus(struct stat *buf, int fd)
{
	if(fstat(fd, buf) < 0)
		return false;
	return true;
}