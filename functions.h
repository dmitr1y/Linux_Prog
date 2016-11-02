//
// Created by ilya-kulakov on 30.10.16.
//
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <zconf.h>
#include <pwd.h>
#include "time.h"
#include <sys/vfs.h>
#include <sys/types.h>
#include <time.h>
#include <utime.h>

#ifndef ALCO_FUNCTIONS_H
#define ALCO_FUNCTIONS_H
void showDiscs(){
    // метод для штатных инструментов оболочки
    system("fdisk -l | grep sda");

    printf("\n");
    struct statfs vfs;
    char path[] = "/";
    if (statfs(path, &vfs) != 0) {
        fprintf(stderr, "%s: statfs failed: %s\n",
                "/", strerror(errno));
        exit(0);
    }

    printf("mounted on %s:\n",path);

    printf("\tf_bsize: %ld\n", vfs.f_bsize);
    printf("\tf_blocks: %ld\n", vfs.f_blocks);
    printf("\tf_bfree: %ld\n", vfs.f_bfree);
    printf("\tf_bavail: %ld\n", vfs.f_bavail);
    printf("\tf_files: %ld\n", vfs.f_files);
    printf("\tf_ffree: %ld\n", vfs.f_ffree);
    printf("------------------------------\n");



//    long long Total_Space = vfs.f_blocks;
//    Total_Space *= vfs.f_frsize;
//    Total_Space /= 1024;
//    long long Avail_Space = vfs.f_bfree;
//    Avail_Space *= vfs.f_frsize;
//    Avail_Space /= 1024;
//
//    printf("Total Space=%lldKb Available Space=%lldKB\n",Total_Space,Avail_Space);
}


//создание нового файла
void createFile(){
    char info[50];
    int fdr;
    int rc = mknod("/home/ilya-kulakov/WorkSpace/testfile",'b',0);
    if(rc<0) {
        perror("Error in mknod");
    }
    fdr=open("/home/ilya-kulakov/WorkSpace/testfile",O_RDONLY);
    read(fdr,info,50);
  //  printf("\n Received message=%s",info);
    printf("\nDone\n");
}

//создание новой директории
void makeFolder(){
    mkdir("/home/ilya-kulakov/WorkSpace/testFolder",777);
}

//удаление директории
void removeFolder(){
    rmdir("/home/ilya-kulakov/WorkSpace/testFolder");
}

//Получает атрибуты файла, в том числе время обращения, записи и т.д.
int  getFileAttribute(){
    struct stat fileStat;
    if(stat("/home/ilya-kulakov/WorkSpace/testfile",&fileStat) < 0)
        return 1;
    printf("Information for %s\n", "testFile");
    printf("---------------------------\n");
    printf("File Size: \t\t%d bytes\n",fileStat.st_size);
    printf("Number of Links: \t%d\n",fileStat.st_nlink);
    printf("File inode: \t\t%d\n",fileStat.st_ino);
    printf("File owner: \t\t%d\n",fileStat.st_uid);
    struct passwd *pwd;
    if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
        printf("Owner name: %-15.15s\n", pwd->pw_name);

//    тут начинается дикий хардкор

    printf("\n-------------------------------\n");
    printf("  Last accsess time                 \n");
    int  a = fileStat.st_atim.tv_sec;
    char str[10];
    sprintf(str,"%d",a);
    char date[19] = "date -d @";
    strcat(date,str);
    system(date);
    printf("Unix time\t\t%d\t",fileStat.st_atim.tv_sec);
    printf("\n-------------------------------\n");


    printf("  Last modification time                 \n");
    a = fileStat.st_mtim.tv_sec;
    char str1[10];
    sprintf(str1,"%d",a);
    char date1[19] = "date -d @";
    strcat(date1,str1);
    system(date1);
    printf("Unix time\t\t%d\t",fileStat.st_mtim.tv_sec);
    printf("\n-------------------------------\n");

    printf("  Last attribute modification time                 \n");
    a = fileStat.st_ctim.tv_sec;
    char str2[10];
    sprintf(str2,"%d",a);
    char date2[19] = "date -d @";
    strcat(date2,str2);
    system(date2);
    printf("Unix time\t\t%d\t",fileStat.st_ctim.tv_sec);
    printf("\n-------------------------------\n");


    printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");


    printf("\nThe file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

    return 0;
}

//смена атрибутуво доступа
void changeAttributeAcces(){

    int result;
    //
    result= chmod("/home/ilya-kulakov/WorkSpace/testfile",S_IREAD|S_IWRITE);
    if (result==-1)
        perror("can't change file mode");
}


void setFileTime(){
    struct stat testfile;
    struct utimbuf new_times;

    stat("/home/ilya-kulakov/WorkSpace/testfile", &testfile);

    new_times.actime = testfile.st_atime - 10*72008; // тут  нужно задавать насколько секунд +/- изменить время.
    new_times.modtime = time(NULL);
    utime("/home/ilya-kulakov/WorkSpace/testfile", &new_times);


}
#endif //ALCO_FUNCTIONS_H
