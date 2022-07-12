# Get next line
This project aims to read from a file every single line individually
### Steps to use it :
#### 1. Clone the repository
```
git clone https://github.com/houssambourkane/42cursus-getnextline.git gnl
```
#### 2. Access the directory
```
cd gnl
```
#### 3. Run the gcc command
```
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=1 -c
```
#### 4. It will generate the object files, and you can run them with your main, for example :
```
gcc -Wall -Wextra -Werror main.c get_next_line.o get_next_line_utils.o -D BUFFER_SIZE=1 -o gnl_exec && ./gnl_exec
 ```

### Main example to try with (you can replace "get_next_line.c" with whatever file you want to read)
```
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
    int fd = open("get_next_line.c", O_RDONLY);
    char *buffer;
    buffer = get_next_line(fd);
    while (buffer)
    {
        printf("%s", buffer);
        free(buffer);
        buffer = get_next_line(fd);
    }
    free(buffer);
}
```
