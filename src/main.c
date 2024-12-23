#include "lib.c"

int main(int argc, char **argv) {

  if (argc == 1) {
    printf("please put a path to file\n");
    return 1;
  }
  char *trimming_file = read_file(argv[1]);
  char *pivot = "submit:function()";
  char *file_trimmed =
      remove_content_from_this_char_to_this_char_after_this_substring(
          trimming_file, pivot, '{', '}');
  FILE *overriding_file = fopen(argv[1], "w");
  fputs(file_trimmed, overriding_file);
  return 0;
}
