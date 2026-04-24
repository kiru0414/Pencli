#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void editor_open() {
  // path /dev/shm/pencli_memo
  int fd = shm_open("/pencli_memo", O_CREAT | O_RDWR, 0666);
  if (fd == -1) {
    perror("shm_open");
    return;
  }
  struct stat st;
  fstat(fd,&st);
  if(st.st_size == 0){
     ftruncate(fd, 0);
  }
  close(fd);
//editor
  char *editor = getenv("EDITOR");
  if (!editor)
    editor = "vi";

  char command[128];
  snprintf(command, sizeof(command), "%s /dev/shm/pencli_memo", editor);

  printf("Opening RAM memo with %s...\n", editor);
  system(command);
}

void print_memo() {
  FILE *fp = fopen("/dev/shm/pencli_memo", "r");
  if (!fp) {
    printf("Memo is empty.\n");
    return;
  }
  char ch;
  while ((ch = fgetc(fp)) != EOF)
    putchar(ch);
  fclose(fp);
}

int main(int argc, char *argv[]) {
  //Open Editor
  if (argc == 1) {
    editor_open();
    return 0;
  }
 
  for (int i = 1; i < argc;i++) {
    if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
      printf("________            __________________   ⬡\n"
             "___  __ \\_____________/ ____/  / /  |_|  ||\n"
             "__  /_/ /  _ \\_  __ \\  /      / /  / /   ||\n"
             "_  ____//  __/  / / / /___   / /  / /    ||\n"
             "/_/     \\___//_/ /_/\\____/  /_/  /_/     ||\n"
             "                                         \\/\n"
             "                                         \'\n"
             "version 1.0\n"
             "commands\n"
             "--help\n"
             "\n");
      return 0;
    }

    if (strcmp(argv[i], "-p") == 0) {
      print_memo();
      return 0;
    }
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
        printf("Usage: pencli [OPTION] [TEXT]\n\n");
        printf("Edit memo (opens $EDITOR):\n");
        printf("  $ pencli\n\n");
        printf("Change editor (example):\n");
        printf("  $ export EDITOR=nano\n\n");
        printf("Add memo:\n");
        printf("  $ pencli -a \"add text\"\n\n");
        printf("Print memo:\n");
        printf("  $ pencli -p\n\n");
        printf("Clear memo:\n");
        printf("  $ pencli -c\n");
        return 0;
    }
    if (strcmp(argv[i], "-c") == 0) {
        shm_unlink("/pencli_memo");
        printf("Memory cleared. (The lead has been broken.)\n");
        return 0;
    }
    if(strcmp(argv[i],"-a")==0 && i+1<argc){
	int fd = shm_open("/pencli_memo",O_CREAT | O_RDWR , 0666);
	struct stat st;
	fstat(fd, &st);
	size_t old_size = st.st_size;
	size_t add_size = strlen(argv[i+1]);
	size_t new_size = old_size + add_size;

	ftruncate(fd,new_size);
	char *ptr = mmap(NULL, new_size,PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr==MAP_FAILED){
		perror("mmap");
		close(fd);
		return 1;
	}
	memcpy(ptr+old_size, argv[i+1], add_size);
	
	munmap(ptr, new_size);
    	close(fd);
	return 0;
     }
  }

  printf("%s: That flag doesn't exist!\n", argv[0]);
  return 0;
}
