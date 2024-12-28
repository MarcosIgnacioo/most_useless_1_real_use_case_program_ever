#include "./array.c"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_SIZE 1200000
#define MAX_STACK_SIZE 256

int str_cmp(char *str_a, const char *str_b) {
  int a_len = strlen(str_a);
  int b_len = strlen(str_b);
  int i = 0;

  if (a_len != b_len) {
    printf("LENS ARE DIFFERENT a_len: %d != b_len : %d\n", a_len, b_len);
    printf("`str_a[i]`->(%c) != `str_b[i]`->(%c)\n", str_a[i], str_b[i]);
    return 0;
  }

  while (str_a[i] != '\0') {
    if (str_a[i] != str_b[i]) {
      printf("`str_a[i]`->(%c) != `str_b[i]`->(%c)", str_a[i], str_b[i]);
      return 0;
    }
    i++;
  }
  return 1;
}

char *str_substring(char *s, size_t start, size_t end) {
  char *sub_str = malloc(end - start);

  if (!sub_str)
    return NULL;

  if (end > strlen(s) || start >= end)
    return sub_str;

  memcpy(sub_str, &s[start], end - start);
  // sub_str[end - start + 1] = '\0';
  sub_str[end - start] = '\0';

  return sub_str;
}

char *str_join(char *str_a, char *str_b) {
  int a_len = strlen(str_a);
  int b_len = strlen(str_b);
  int total_len = a_len + b_len;
  char *joined_str = malloc(total_len + 1);
  if (!joined_str)
    return NULL;
  // aqui lo que hacia era restarle a a_len - 1 porque pensaba que tenia el null
  // terminating character pero la len de un string no incluye el null character
  // por lo que cuando copiamoss la len estamos copiando solo elo contenido del
  // string y no el null char por lo que no hace falta y pues apaarecia como un
  // 0 porque pues relamente se quedan ocmo 0 si no estan inicializados cuando
  // malloooc
  memcpy(joined_str, str_a, a_len);
  memcpy(joined_str + a_len, str_b, b_len);
  joined_str[total_len] = '\0';
  return joined_str;
}

int where_is_the_end_of_the_needle_in_the_haystack(char *haystack,
                                                   char *needle) {
  int needle_in_haystack_index = 0;
  int haystack_len = strlen(haystack);
  int needle_len = strlen(needle);
  for (size_t i = 0, j = 0; i < haystack_len && !needle_in_haystack_index;
       i++) {
    while (haystack[i] == needle[j]) {
      j += 1;
      i += 1;
      if (j == needle_len) {
        needle_in_haystack_index = i;
        break;
      }
    }
    j = 0;
  }
  return needle_in_haystack_index;
}

char *read_file(char *file_name) {

  FILE *file = fopen(file_name, "r");
  if (!file) {
    printf("failed to oppen file %s \n", file_name);
    return NULL;
  }
  // char *text_from_file = malloc(INT_MAX);
  char *text_from_file = array(char *);
  if (!text_from_file) {
    printf("mallocint this much failed in %s\n", file_name);
    return NULL;
  }
  int c;

  while ((c = fgetc(file)) != EOF) {
    // text_from_file[i++] = c;
    append(text_from_file, c);
  }
  append(text_from_file, '\0');
  return text_from_file;
}

char *remove_content_from_this_char_to_this_char_after_this_substring(
    char *source_text,     //
    char *substring_pivot, //
    char from_char,        //
    char to_char) {

  int where = where_is_the_end_of_the_needle_in_the_haystack(source_text,
                                                             substring_pivot);
  int s_ptr = 0;
  size_t i;
  for (i = where; i < strlen(source_text); i++) {
    if (source_text[i] == from_char) {
      s_ptr++;
    }
    if (source_text[i] == to_char) {
      if (s_ptr == 0) {
        printf("there was a } before an { manage it yourself lolll\n");
        exit(1);
      }
      s_ptr--;
    }
    if (s_ptr == 0) {
      where++;
      break;
    }
  }

  char *sub_a = str_substring(source_text, 0, where);
  if (!sub_a) {
    printf("sub_a is nil\n");
    return NULL;
  }

  char *sub_b = str_substring(source_text, i, strlen(source_text) - 1);
  if (!sub_b) {
    printf("sub_b is nil\n");
    return NULL;
  }

  char *joined = str_join(sub_a, sub_b);
  if (!joined) {
    printf("joined is nil\n");
    return NULL;
  }

  return joined;
}

void start(char *target_substring) {
  char *easy_txt = read_file("texts/easy.txt");
  char *new_text = malloc(sizeof(strlen(easy_txt)));
  char *medium_txt = read_file("texts/medium.txt");
  if (!easy_txt || !new_text || !medium_txt) {
    return;
  }
  // int where_medium = where_is_the_end_of_the_needle_in_the_haystack(
  //     medium_txt, target_substring);
  // printf("%d \n", where_medium);

  char *pivot = "submit:function()";
  char *joined =
      remove_content_from_this_char_to_this_char_after_this_substring(
          medium_txt, pivot, '{', '}');
  printf("%s \n", joined);
}
