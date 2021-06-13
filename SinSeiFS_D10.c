#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

static const char *dirPath = "/home/tito/Downloads";

void at_bash(char *str, int fileName)
{
	int i, a = 'a', A = 'A', z = 'z', Z = 'Z';
	for (i = 0; i < fileName; i++)
	{
		if (str[i] >= a && str[i] <= z){
			str[i] = a + (z-str[i]);
		}
		else if (str[i] >= A && str[i] <= Z){
			str[i] = A + (Z-str[i]);
		}
	}
}

void rot13(char *str, int fileName){
	int i;
	for (i = 0; i < fileName; i++)
	{
		if ((str[i] >= 'a' && str[i] < 'n') || (str[i] >= 'A' && str[i] < 'N')){
			str[i] += 13;
		}
		else if ((str[i] > 'm' && str[i] <= 'z') || (str[i] > 'M' && str[i] <= 'Z')){
			str[i] -= 13;
		}
	}
}

void encrypt_atoz(char *str)
{
	if (strcmp(str, ".") == 0)
		return;
	if (strcmp(str, "..") == 0)
		return;

	int lastIndex = strlen(str);
	for (int i = lastIndex; i >= 0; i--)
	{
		if (str[i] == '.')
		{
			lastIndex = i;
			break;
		}
	}
	at_bash(str, lastIndex);
}

void decrypt_atoz(char *str)
{
	if (strcmp(str, ".") == 0)
		return;
	if (strcmp(str, "..") == 0)
		return;

	if (strstr(str, "/") == NULL)
		return;

	char *fileName = strstr(str, "/");

	int lastIndex = strlen(fileName);
	for (int i = lastIndex; i >= 0; i--)
	{
		if (fileName[i] == '/')
			break;
		if (fileName[i] == '.')
		{
			lastIndex = i;
			break;
		}
	}
	at_bash(fileName, lastIndex);
}

void encrypt_rx(char *str)
{
	if (strcmp(str, ".") == 0)
		return;
	if (strcmp(str, "..") == 0)
		return;
	int lastIndex = strlen(str);
	for (int i = lastIndex; i >= 0; i--)
	{
		if (str[i] == '.')
		{
			lastIndex = i;
			break;
		}
	}
	at_bash(str, lastIndex);
	rot13(str, lastIndex);
}

void decrypt_rx(char *str)
{
	if (strcmp(str, ".") == 0)
		return;
	if (strcmp(str, "..") == 0)
		return;
	if (strstr(str, "/") == NULL)
		return;

	char *fileName = strstr(str, "/");
	int lastIndex = strlen(fileName);
	for (int i = lastIndex; i >= 0; i--)
	{
		if (fileName[i] == '/')
			break;
		if (fileName[i] == '.')
		{
			lastIndex = i;
			break;
		}
	}
	rot13(fileName, lastIndex);
	at_bash(fileName, lastIndex);
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
	char *atoz_str = strstr(path, "AtoZ_");
	if (atoz_str != NULL)
	{
		decrypt_atoz(atoz_str);
	}
	char *rx_str = strstr(path, "RX_");
	if (rx_str != NULL)
	{
		decrypt_rx(rx_str);
	}
	char newPath[500];
	int res;
	sprintf(newPath, "%s%s", dirPath, path);
	res = lstat(newPath, stbuf);
	if (res == -1)
		return -errno;
	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
	char *atoz_str = strstr(path, "AtoZ_");
	if (atoz_str != NULL)
	{
		decrypt_atoz(atoz_str);
	}
	char *rx_str = strstr(path, "RX_");
	if (rx_str != NULL)
	{
		decrypt_rx(rx_str);
	}
	char newPath[500];
	if (strcmp(path, "/") == 0)
	{
		path = dirPath;
		sprintf(newPath, "%s", path);
	}
	else
		sprintf(newPath, "%s%s", dirPath, path);
	int res = 0;
	struct dirent *dir;
	DIR *dp;
	(void)fi;
	(void)offset;
	dp = opendir(newPath);
	if (dp == NULL)
		return -errno;

	while ((dir = readdir(dp)) != NULL)
	{
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = dir->d_ino;
		st.st_mode = dir->d_type << 12;
		if (atoz_str != NULL)
		{
			encrypt_atoz(dir->d_name);
		}
		if (rx_str != NULL)
		{
			encrypt_rx(dir->d_name);
		}
		res = (filler(buf, dir->d_name, &st, 0));
		if (res != 0)
			break;
	}

	closedir(dp);
	return 0;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
	char newPath[500];
	if (strcmp(path, "/") == 0)
	{
		path = dirPath;
		sprintf(newPath, "%s", path);
	}
	else
		sprintf(newPath, "%s%s", dirPath, path);

	int res = mkdir(newPath, mode);
	char *atoz_str = strstr(path, "AtoZ_");
	if (atoz_str != NULL)
	{
		decrypt_atoz(atoz_str);
	}
	char *rx_str = strstr(path, "RX_");
	if (rx_str != NULL)
	{
		decrypt_rx(rx_str);
	}

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
	char newPath[500];
	if (strcmp(path, "/") == 0)
	{
		path = dirPath;
		sprintf(newPath, "%s", path);
	}
	else
		sprintf(newPath, "%s%s", dirPath, path);
	int res;

	if (S_ISREG(mode))
	{
		res = open(newPath, O_CREAT | O_EXCL | O_WRONLY, mode);
		if (res >= 0)
			res = close(res);
	}
	else if (S_ISFIFO(mode))
		res = mkfifo(newPath, mode);
	else
		res = mknod(newPath, mode, rdev);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_unlink(const char *path)
{
	char newPath[500];
	if (strcmp(path, "/") == 0)
	{
		path = dirPath;
		sprintf(newPath, "%s", path);
	}
	else
		sprintf(newPath, "%s%s", dirPath, path);
	int res;
	res = unlink(newPath);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_rmdir(const char *path)
{
	char newPath[500];
	sprintf(newPath, "%s%s", dirPath, path);
	int res;
	res = rmdir(newPath);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	int fd;
	int res;
	(void)fi;
	char newPath[500];
	sprintf(newPath, "%s%s", dirPath, path);
	fd = open(newPath, O_WRONLY);
	if (fd == -1)
		return -errno;
	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;
	close(fd);
	return res;
}

static int xmp_rename(const char *from, const char *to)
{
	char dari[500], ke[500];
	sprintf(dari, "%s%s", dirPath, from);
	sprintf(ke, "%s%s", dirPath, to);
	int res;
	res = rename(dari, ke);
	if (res == -1)
		return -errno;
	return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
	int res;
	char newPath[500];
	sprintf(newPath, "%s%s", dirPath, path);
	res = open(newPath, fi->flags);
	if (res == -1)
		return -errno;
	close(res);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	int fd;
	int res;
	(void)fi;
	char newPath[500];
	sprintf(newPath, "%s%s", dirPath, path);
	fd = open(newPath, O_RDONLY);
	if (fd == -1)
		return -errno;
	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;
	close(fd);
	return res;
}

static int xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
	int res;
	char newPath[500];
	sprintf(newPath, "%s%s", dirPath, path);
	res = open(newPath, fi->flags, mode);
	if (res == -1)
		return -errno;

	fi->fh = res;
	return 0;
}

static struct fuse_operations xmp_oper = {
		.getattr = xmp_getattr,
		.readdir = xmp_readdir,
		.read = xmp_read,
		.mkdir = xmp_mkdir,
		.mknod = xmp_mknod,
		.unlink = xmp_unlink,
		.rmdir = xmp_rmdir,
		.rename = xmp_rename,
		.open = xmp_open,
		.write = xmp_write,
		.create = xmp_create,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
