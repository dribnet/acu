#include "acSerial.h"


acSerial::acSerial(char *serialPort, int rate) {
  //fprintf(stderr, "CONNECTING VIA PORT %s \n", serialPort);
  comm = CreateFile(serialPort,
		    GENERIC_READ | GENERIC_WRITE,
		    0,    // comm devices must be opened w/exclusive-access
		    NULL, // no security attrs
		    OPEN_EXISTING, // comm devices must use OPEN_EXISTING
		    0,      // not overlapped I/O
		    NULL);  // hTemplate must be NULL for comm devices

  if (comm == INVALID_HANDLE_VALUE) {
    DWORD dwError = GetLastError();
    fprintf(stderr, "acSerial: Error code %ld while opening %s.\n",
	    dwError, serialPort);
    if (dwError == ERROR_FILE_NOT_FOUND) {
    	fprintf(stderr, "ERROR_FILE_NOT_FOUND\n");
    } else  if (dwError == ERROR_NOT_SUPPORTED) {
    	fprintf(stderr, "ERROR_NOT_SUPPORTED\n");
    }
    return; 
  }

  // Omit the call to SetupComm to use the default queue sizes.
  // Get the current configuration.
  DCB dcb;
  BOOL fSuccess = GetCommState(comm, &dcb);
  if (!fSuccess) {
    /* Handle the error. */
    printf("acSerial: Error getting the comm state");
    comm = INVALID_HANDLE_VALUE;
    return;
  }

  // Fill in the DCB: baud=19200, 8 data bits, no parity, 1 stop bit.
  dcb.BaudRate = rate;
  dcb.ByteSize = 8;
  dcb.Parity = NOPARITY;
  dcb.StopBits = ONESTOPBIT;	
  fSuccess = SetCommState(comm, &dcb);

  if (!fSuccess) {
    fprintf(stderr, "acSerial: Error setting the comm state");
    comm = INVALID_HANDLE_VALUE;
    return;
  }

  COMMTIMEOUTS cto;
  cto.ReadIntervalTimeout = 10; 
  cto.ReadTotalTimeoutMultiplier = 1; 
  cto.ReadTotalTimeoutConstant = 200; 
  cto.WriteTotalTimeoutMultiplier = 10; 
  cto.WriteTotalTimeoutConstant = 100;
  if (!SetCommTimeouts(comm, &cto)) {
    fprintf(stderr, "acSerial: Unable to set proper timeouts");
  }
}


acSerial::~acSerial() {
  if (comm != INVALID_HANDLE_VALUE) {
    CloseHandle(comm);
  }
}


int acSerial::write(unsigned char *buffer, int count) {
  DWORD bytes = count;
  bool result = WriteFile(comm, buffer, bytes, &bytes, NULL);
  if (result == 0) {
    // FLAG ERROR HERE... what should we do??
    COMSTAT comstat;
    DWORD errorflags;
    ClearCommError(comm , &errorflags, &comstat);
    fprintf(stderr, "max loves win32, and what the fsck does " 
	    "one do with comm errors?\n");
  }
  return bytes;
}


int acSerial::read(unsigned char *buffer, int count) {
  //bool stat;

  if (comm == INVALID_HANDLE_VALUE) return -1;

  COMSTAT comstat;
  LPDWORD errorflags = 0;
  ClearCommError(comm, errorflags, &comstat);
  // quick hack to allow for hacking... 
  // don't know if this is really necessary...

  while (comstat.cbInQue < count) {
    //fprintf(stderr, "acSerial: only %d bytes available (not %d)\n", 
    //    comstat.cbInQue, count);
    Sleep(2); // used to be 1
    ClearCommError(comm, errorflags, &comstat);
  }
  DWORD length;
  if (ReadFile(comm, buffer, count, &length, NULL) == 0) {
    fprintf(stderr, "acSerial: Readfile failed\n");
    return -1;
  }
  return length;

  /*
  int retryCount = 10;
  while ((comstat.cbInQue < bytestoread) && retryCount) {
    fprintf(stderr, "acSerial:: only %d bytes available (not %d)\n", 
	    comstat.cbInQue, count);
    Sleep(1);
    ClearCommError(comm, errorflags, &comstat);
    retryCount--;
  }  
  if (comstat.cbInQue < bytestoread) {
    byte garbage[1024];
    inlength = MIN(comstat.cbInQue, 1024);
    if (ReadFile(tagCOM, garbage, inlength, &inlength, NULL) == 0) {
      fprintf(stderr, "readResponse(): Readfile failed: ");
      acSocket::printSystemError("miniSerial::readResponse()");      
    }
    return -1;
  } else {
    inlength = bytestoread;
    if (ReadFile(tagCOM, databuffer, inlength, &inlength, NULL) == 0) {
      fprintf(stderr, "readResponse(): Readfile failed: ");
      acSocket::printSystemError("miniSerial::readResponse()");
      return -1;
    }
    return inlength;
  }
  */
}
