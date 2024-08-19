#include "s21_string.h"
void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *result = s21_NULL;

  for (s21_size_t i = 0; (i < n) && (result == s21_NULL); ++i) {
    if (*((char *)str + i) == c) {
      result = (char *)str + i;
    }
  }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  int result = 0;
  for (s21_size_t i = 0; (i < n) && (result == 0); ++i) {
    if (*((char *)str1 + i) < *((char *)str2 + i)) {
      result = -1;
    } else if (*((char *)str1 + i) > *((char *)str2 + i)) {
      result = 1;
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if ((char *)dest != s21_NULL) {
    for (s21_size_t i = 0; (i < n) && ((char *)src + i) != s21_NULL; ++i) {
      if ((char *)dest + i == s21_NULL) {
        dest = (char *)realloc(dest, i + 1);
      }
      *((char *)dest + i) = *((char *)src + i);
    }
  }
  return dest;
}

void *s21_memset(void *str, int c, size_t n) {
  if ((char *)str != s21_NULL) {
    for (s21_size_t i = 0; i < n; ++i) {
      if ((char *)str + i == s21_NULL) {
        str = (char *)realloc(str, i + 1);
      }
      *((char *)str + i) = c;
    }
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, size_t n) {
  s21_size_t dest_index = s21_strlen(dest);
  for (s21_size_t i = 0; i < n && src[i] != '\0'; i++) {
    dest[dest_index] = src[i];
    dest_index++;
  }
  dest[dest_index] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *temp = (char *)str;
  void *res = ((char)c == '\0') ? "\0" : s21_NULL;
  s21_size_t i = 0;
  while (*(temp + i) != '\0' && *(temp + i) != c) i++;
  if (*(temp + i) != '\0') res = temp + i;
  return res;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  int result = 0;
  for (s21_size_t i = 0; (i < n) && (result == 0); ++i) {
    if (*((char *)str1 + i) < *((char *)str2 + i)) {
      result = -1;
    } else if (*((char *)str1 + i) > *((char *)str2 + i)) {
      result = 1;
    }
  }
  return result;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
  if (dest != s21_NULL) {
    for (s21_size_t i = 0; (i < n) && (src + i) != s21_NULL; ++i) {
      if (dest + i == s21_NULL) {
        dest = realloc(dest, i + 1);
      }
      *(dest + i) = *(src + i);
    }
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  for (s21_size_t i = 0; str1[i] != '\0'; ++i) {
    for (s21_size_t j = 0; str2[j] != '\0'; ++j) {
      if (str1[i] == str2[j]) {
        return result;
      }
    }
    result++;
  }
  return result;
}

char *s21_strerror(int errnum) {
#if defined(__APPLE__)
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1
#define ERROR "Unknown error: "

  const char *maserror[] = {"Undefined error: 0",
                            "Operation not permitted",
                            "No such file or directory",
                            "No such process",
                            "Interrupted system call",
                            "Input/output error",
                            "Device not configured",
                            "Argument list too long",
                            "Exec format error",
                            "Bad file descriptor",
                            "No child processes",
                            "Resource deadlock avoided",
                            "Cannot allocate memory",
                            "Permission denied",
                            "Bad address",
                            "Block device required",
                            "Resource busy",
                            "File exists",
                            "Cross-device link",
                            "Operation not supported by device",
                            "Not a directory",
                            "Is a directory",
                            "Invalid argument",
                            "Too many open files in system",
                            "Too many open files",
                            "Inappropriate ioctl for device",
                            "Text file busy",
                            "File too large",
                            "No space left on device",
                            "Illegal seek",
                            "Read-only file system",
                            "Too many links",
                            "Broken pipe",
                            "Numerical argument out of domain",
                            "Result too large",
                            "Resource temporarily unavailable",
                            "Operation now in progress",
                            "Operation already in progress",
                            "Socket operation on non-socket",
                            "Destination address required",
                            "Message too long",
                            "Protocol wrong type for socket",
                            "Protocol not available",
                            "Protocol not supported",
                            "Socket type not supported",
                            "Operation not supported",
                            "Protocol family not supported",
                            "Address family not supported by protocol family",
                            "Address already in use",
                            "Can't assign requested address",
                            "Network is down",
                            "Network is unreachable",
                            "Network dropped connection on reset",
                            "Software caused connection abort",
                            "Connection reset by peer",
                            "No buffer space available",
                            "Socket is already connected",
                            "Socket is not connected",
                            "Can't send after socket shutdown",
                            "Too many references: can't splice",
                            "Operation timed out",
                            "Connection refused",
                            "Too many levels of symbolic links",
                            "File name too long",
                            "Host is down",
                            "No route to host",
                            "Directory not empty",
                            "Too many processes",
                            "Too many users",
                            "Disc quota exceeded",
                            "Stale NFS file handle",
                            "Too many levels of remote in path",
                            "RPC struct is bad",
                            "RPC version wrong",
                            "RPC prog. not avail",
                            "Program version wrong",
                            "Bad procedure for program",
                            "No locks available",
                            "Function not implemented",
                            "Inappropriate file type or format",
                            "Authentication error",
                            "Need authenticator",
                            "Device power is off",
                            "Device error",
                            "Value too large to be stored in data type",
                            "Bad executable (or shared library)",
                            "Bad CPU type in executable",
                            "Shared library version mismatch",
                            "Malformed Mach-o file",
                            "Operation canceled",
                            "Identifier removed",
                            "No message of desired type",
                            "Illegal byte sequence",
                            "Attribute not found",
                            "Bad message",
                            "EMULTIHOP (Reserved)",
                            "No message available on STREAM",
                            "ENOLINK (Reserved)",
                            "No STREAM resources",
                            "Not a STREAM",
                            "Protocol error",
                            "STREAM ioctl timeout",
                            "Operation not supported on socket",
                            "Policy not found",
                            "State not recoverable",
                            "Previous owner died",
                            "Interface output queue is full"};

#elif defined(__linux__)
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1
#define ERROR "Unknown error "

  static const char *maserror[] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Device or resource busy",
      "File exists",
      "Invalid cross-device link",
      "No such device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Numerical result out of range",
      "Resource deadlock avoided",
      "File name too long",
      "No locks available",
      "Function not implemented",
      "Directory not empty",
      "Too many levels of symbolic links",
      "Unknown error 41",
      "No message of desired type",
      "Identifier removed",
      "Channel number out of range",
      "Level 2 not synchronized",
      "Level 3 halted",
      "Level 3 reset",
      "Link number out of range",
      "Protocol driver not attached",
      "No CSI structure available",
      "Level 2 halted",
      "Invalid exchange",
      "Invalid request descriptor",
      "Exchange full",
      "No anode",
      "Invalid request code",
      "Invalid slot",
      "Unknown error 58",
      "Bad font file format",
      "Device not a stream",
      "No data available",
      "Timer expired",
      "Out of streams resources",
      "Machine is not on the network",
      "Package not installed",
      "Object is remote",
      "Link has been severed",
      "Advertise error",
      "Srmount error",
      "Communication error on send",
      "Protocol error",
      "Multihop attempted",
      "RFS specific error",
      "Bad message",
      "Value too large for defined data type",
      "Name not unique on network",
      "File descriptor in bad state",
      "Remote address changed",
      "Can not access a needed shared library",
      "Accessing a corrupted shared library",
      ".lib section in a.out corrupted",
      "Attempting to link in too many shared libraries",
      "Cannot exec a shared library directly",
      "Invalid or incomplete multibyte or wide character",
      "Interrupted system call should be restarted",
      "Streams pipe error",
      "Too many users",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol",
      "Address already in use",
      "Cannot assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Transport endpoint is already connected",
      "Transport endpoint is not connected",
      "Cannot send after transport endpoint shutdown",
      "Too many references: cannot splice",
      "Connection timed out",
      "Connection refused",
      "Host is down",
      "No route to host",
      "Operation already in progress",
      "Operation now in progress",
      "Stale file handle",
      "Structure needs cleaning",
      "Not a XENIX named type file",
      "No XENIX semaphores available",
      "Is a named type file",
      "Remote I/O error",
      "Disk quota exceeded",
      "No medium found",
      "Wrong medium type",
      "Operation canceled",
      "Required key not available",
      "Key has expired",
      "Key has been revoked",
      "Key was rejected by service",
      "Owner died",
      "State not recoverable",
      "Operation not possible due to RF-kill",
      "Memory page has hardware error"};
#endif

  char *result = s21_NULL;
  if (errnum <= MAX_ERRLIST && errnum >= MIN_ERRLIST) {
    result = (char *)maserror[errnum];
  } else {
    int temp_errnum = errnum, log_errnum = 0;
    if (temp_errnum < 0) {
      temp_errnum *= -1;
      log_errnum += 1;
    }
    while (temp_errnum != 0) {
      ++log_errnum;
      temp_errnum /= 10;
    }

    temp_errnum = errnum;
    if (temp_errnum < 0) {
      temp_errnum *= -1;
    }
    result = (char *)malloc(sizeof(char) * log_errnum);
    if (result) {
      for (int i = 0; temp_errnum != 0; ++i) {
        result[log_errnum - i - 1] = temp_errnum % 10 + '0';
        temp_errnum /= 10;
      }
      result[0] = '-';
    }
  }
  return result;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t result;
  for (result = 0; str + result != s21_NULL && *(str + result) != '\0';
       ++result) {
  }
  return result;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  for (s21_size_t i = 0; str1[i] != '\0' && result == s21_NULL; ++i) {
    for (s21_size_t j = 0; str2[j] != '\0' && result == s21_NULL; ++j) {
      if (str1[i] == str2[j]) {
        result = (char *)&str1[i];
      }
    }
  }
  return result;
}

char *s21_strrchr(const char *str, int c) {
  const char *rez = s21_NULL;
  if (str != s21_NULL) {
    while (*str != '\0') {
      if (*str == c) {
        rez = str;
      }
      str++;
    }
  }
  if (*str == c) {
    rez = (char *)str;
  }
  return (char *)rez;
}

char *s21_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') {
    return (char *)haystack;
  }
  for (; *haystack != '\0'; ++haystack) {
    const char *h = haystack;
    const char *n = needle;

    while (*n != '\0' && *h == *n) {
      h++;
      n++;
    }
    if (*n == '\0') {
      return (char *)haystack;
    }
  }
  return s21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last;
  char *result = s21_NULL;

  if (str != s21_NULL) {
    last = str;
  }

  if (last == s21_NULL || *last == '\0') {
    return s21_NULL;
  }

  while (*last != '\0') {
    const char *d = delim;
    int is_delim = 0;
    while (*d != '\0') {
      if (*last == *d) {
        last++;
        is_delim = 1;
        break;
      }
      d++;
    }
    if (!is_delim) {
      break;
    }
  }

  if (*last == '\0') {
    return s21_NULL;
  }

  result = last;

  while (*last != '\0') {
    const char *d = delim;
    while (*d != '\0') {
      if (*last == *d) {
        *last = '\0';
        last++;
        return result;
      }
      d++;
    }
    last++;
  }

  return result;
}

void *s21_to_upper(const char *str) {
  if (str == s21_NULL || str[0] == '\0') {
    char *empty_str = (char *)malloc(sizeof(char));
    if (empty_str) {
      empty_str[0] = '\0';
      return empty_str;
    }
  }
  int length = s21_strlen(str);
  char *result = (char *)malloc(sizeof(char) * (length + 1));
  if (result) {
    for (int i = 0; i < length; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        result[i] = str[i] - 32;
      } else {
        result[i] = str[i];
      }
    }
    result[length] = '\0';
  }
  return result;
}

void *s21_to_lower(const char *str) {
  if (str == s21_NULL || str[0] == '\0') {
    char *empty_str = (char *)malloc(sizeof(char));
    if (empty_str) {
      empty_str[0] = '\0';
      return empty_str;
    }
  }
  int length = s21_strlen(str);
  char *result = (char *)malloc(sizeof(char) * (length + 1));
  if (result) {
    for (int i = 0; i < length; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        result[i] = str[i] + 32;
      } else {
        result[i] = str[i];
      }
    }
    result[length] = '\0';
  }
  return result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  void *insert = s21_NULL;
  if (src == s21_NULL || str == s21_NULL) {
    return s21_NULL;
  }
  int src_length = s21_strlen(src);
  int str_length = s21_strlen(str);
  if (start_index > (long unsigned int)src_length) {
    return s21_NULL;
  }
  insert = malloc(str_length + src_length + 1);
  if (insert != s21_NULL) {
    char *insert_ptr = (char *)insert;
    s21_memcpy(insert_ptr, src, start_index);
    s21_memcpy(insert_ptr + start_index, str, str_length);
    s21_memcpy(insert_ptr + start_index + str_length, src + start_index,
               src_length - start_index);
    insert_ptr[str_length + src_length] = '\0';
  }
  return insert;
}

void *s21_trim(const char *src, const char *trim_ch) {
  char *res = s21_NULL;
  if (src != s21_NULL) {
    if (trim_ch == s21_NULL || trim_ch[0] == '\0') {
      trim_ch = " ";
    }
    s21_size_t len = s21_strlen(src);
    if (len) {
      int start = -1, end = -1, flagf = 1, flagl = 1, flag_break = 1;
      for (s21_size_t i = 0, j = len - 1; i < len && flag_break; i++, j--) {
        if (s21_strchr(trim_ch, src[i]) == s21_NULL && flagf) {
          start = i;
          flagf = 0;
        }
        if (s21_strchr(trim_ch, src[j]) == s21_NULL && flagl) {
          end = j;
          flagl = 0;
        }
        if (!flagf && !flagl) {
          flag_break = 0;
        }
      }
      res = calloc(end - start + 2, sizeof(char));
      if (res != s21_NULL) {
        for (int i = start, j = 0; i <= end; i++, j++) {
          res[j] = src[i];
        }
      }
    } else {
      res = calloc(2, sizeof(char));
    }
  }
  return res;
}
