#include <stdio.h>
#include <math.h>

// void bit_set(unsigned char *data, int i)
// {
//   data[i/8] |= 0x80 >> (i%8); 
// }

// void bit_unset(unsigned char *data, int i)
// {
//   data[i/8] &= ~(0x80 >> (i%8)); 
// }

// char bit_get(unsigned char *data, int i)
// {
//   return (data[i/8] & 0x80 >> (i%8));
// }


int main(int argc, char** argv)
{
  if (argc != 2) {
    printf("Usage:\n");
    printf("%s <file>", argv[0]);
    return 1;
  }
  FILE *file_p;
  long filelen;

  file_p = fopen(argv[1], "rb");
  if (!file_p) {
    printf("Failed to open file!\n");
    return 2;
  }
  fseek(file_p, 0, SEEK_END);
  filelen = ftell(file_p);
  rewind(file_p);
  printf("File length is %li bytes\n", filelen);

  int buffer;
  int bytes_found[256] = {0}; // 2^8 possible outcomes, char is 8 bit

  for (long i_byte = 0; i_byte < filelen; i_byte++) {
    buffer = getc(file_p);
    if (buffer == EOF) {
      printf("Unexpected EOF while reading file!\n");
      return 2;
    }
    // printf("%c", (char) buffer); // DEBUG
    bytes_found[buffer] += 1;
  }

  long double p_i;
  long double entropy = 0;
  for (int i = 0; i < 256; i++){
    if (bytes_found[i]) {
      p_i = (long double) bytes_found[i] / filelen;
      // printf("%Lf ", p_i);
      entropy += p_i * log2l(p_i);
    }
  }
  printf("Entropy: %Lf bits\n", -entropy);
  return 0;
}
