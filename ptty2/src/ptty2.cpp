//============================================================================
// Name        : ptty2.cpp
// Author      : Butyaev A.Y.
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>

int ParentLoop(int iPtyfd);
int ChildLoop(void);
pid_t CreatePseudoTerminalPair(int *pPtyfd);
int SetControllingTty(int fd, char *pSlaveName);

int main(int argc, char** argv)
{
  int iPtyfd = -1;
  pid_t pid = CreatePseudoTerminalPair(&iPtyfd);
  if (pid == 0)
  {
    // Child
    ChildLoop();
    return 0;
  }

  ParentLoop(iPtyfd);
  return 0;
}

int ParentLoop(int iPtyfd)
{
  fprintf(stderr, "Starting ParentLoop...\n");
  fd_set rfds;
  int retval;
  char pBuf[256];
  ssize_t sz;
  int greater = iPtyfd;
  greater++;

  while (true)
  {
    FD_ZERO(&rfds);
    FD_SET(iPtyfd, &rfds);

    retval = select(greater, &rfds, NULL, NULL, NULL);
    if (retval == -1)
    {
      fprintf(stderr, "WaitforPipe dead\n");
      break;
    }
    else if (retval)
    {
      memset(pBuf, 0, sizeof(pBuf));
      if (FD_ISSET(iPtyfd, &rfds))
      {
        sz = read(iPtyfd, pBuf, sizeof(pBuf) - 1);
        if (sz <= 0)
          break;

        fprintf(stderr, "From child: %s\n", pBuf);
      }
      else
      {
        fprintf(stderr, "This can't be (WaitforPipe)!\n");
        break;
      }
    }
    else
    {
      fprintf(stderr, "WaitforPipe: No data.\n");
      break;
    }
  }

  close(iPtyfd);

  fprintf(stderr, "exiting ParentLoop\n");
  return 0;
}

int ChildLoop(void)
{
  for (int i = 3; i < 64; i++)
    close(i);

  fprintf(stderr, "Starting ChildLoop...\n");
  sleep(2);
  for (int i = 0; i < 3; i++)
  {
    fprintf(stdout, "hello parent%d\n", i);
    fflush(stdout);
    sleep(2);
  }

  fprintf(stderr, "exiting ChildLoop\n");
  return 0;
}

pid_t CreatePseudoTerminalPair(int *pPtyfd)
{
  int iMaster = open("/dev/ptmx", O_RDWR);
  if (iMaster == -1)
  {
    fprintf(stderr, "master open failed: %s\n", strerror(errno));
    return -1;
  }

  if (grantpt(iMaster) != 0)
  {
    fprintf(stderr, "grantpt failed: %s\n", strerror(errno));
    close(iMaster);
    return -1;
  }

  if (unlockpt(iMaster) != 0)
  {
    fprintf(stderr, "unlockpt failed: %s\n", strerror(errno));
    close(iMaster);
    return -1;
  }

  char *pSlaveName = ptsname(iMaster);
  if (pSlaveName)
  {
    //fprintf(stderr, "pSlaveName: %s\n", pSlaveName);
    int iSlave = open(pSlaveName, O_RDWR | O_NOCTTY);
    if (iSlave != -1)
    {
      pid_t pid;
      switch (pid = fork())
      {
        case -1:
          return -1;
        case 0:
          // Child
          close (iMaster);
          return SetControllingTty(iSlave, pSlaveName);
        default:
          // Parent
          *pPtyfd = iMaster;
          close(iSlave);
          return pid;
      }
    }
    else
      fprintf(stderr, "slave open failed: %s\n", strerror(errno));
  }
  else
    fprintf(stderr, "ptsname failed: %s\n", strerror(errno));

  close(iMaster);
  return 0;
}

int SetControllingTty(int fd, char *pSlaveName)
{
  if (setsid() < 0)
    fprintf(stderr, "setsid failed: %s\n", strerror(errno));

#ifdef TIOCSCTTY
  if (ioctl(fd, TIOCSCTTY, (char *)NULL) == -1)
  {
    fprintf(stderr, "SetControllingTty returning -1\n");
    return -1;
  }
#else
  int fdtmp = open(pSlaveName, O_RDWR);
  if (fdtmp < 0)
    fprintf(stderr, "open failed: %s\n", strerror(errno));
  else
    close(fdtmp);

#endif
  dup2(fd, 0);
  dup2(fd, 1);
  dup2(fd, 2);
  if (fd > 2)
    close(fd);
  return 0;
}
