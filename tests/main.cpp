#include <cstdio>

#include "rasterizer.hpp"

int main(int argc, char **argv) {

  FILE* fp = fopen("test.ppm", "wb");
  fprintf(fp, "P6\n %s\n %d\n %d\n %d\n", "", 200, 200, 255);

  fbvg::byte buffer[200 * 200 * 3];
  fbvg::Rasterizer rst (buffer, 200, 200, 3);
  fbvg::Canvas ctx (&rst);

  // Fill with black
  for (int y = 0; y < 200; ++y) {
    for (int x = 0; x < 200; ++x) {
      buffer[(x * 200 + y) * 3 + 0] = 0x00;
      buffer[(x * 200 + y) * 3 + 1] = 0x00;
      buffer[(x * 200 + y) * 3 + 2] = 0x00;
    }
  }

  ctx.state.strokeColor = 0xFFFFFF;
  ctx.moveTo({0,0});
  ctx.lineTo({50, 50});
  ctx.lineTo({150, 50});
  ctx.stroke();

  /* write image data bytes to the file */
  fwrite(buffer, sizeof(buffer), 1, fp);
  fclose(fp);

}
