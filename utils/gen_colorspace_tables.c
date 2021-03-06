/*******************************************************************************
 gen_colorspace_tables.c

 libquicktime - A library for reading and writing quicktime/avi/mp4 files.
 http://libquicktime.sourceforge.net

 Copyright (C) 2002 Heroine Virtual Ltd.
 Copyright (C) 2002-2011 Members of the libquicktime project.

 This library is free software; you can redistribute it and/or modify it under
 the terms of the GNU Lesser General Public License as published by the Free
 Software Foundation; either version 2.1 of the License, or (at your option)
 any later version.

 This library is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 details.

 You should have received a copy of the GNU Lesser General Public License along
 with this library; if not, write to the Free Software Foundation, Inc., 51
 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*******************************************************************************/ 

#include <inttypes.h>
#include <stdio.h>

#define RECLIP(v, min, max) \
  if(v<min) v=min; if(v>max) v=max;

int main(int argc, char ** argv)
  {
  int i;
  int      tmp_int;
  float    tmp_float;

  /* First, emit some #defines */

  printf("#ifdef GAVL\n");

  printf("#define HAVE_YUVJ_TO_YUV_8\n");
  printf("#define HAVE_YUVJ_TO_YUV_16\n");
  printf("#define HAVE_YUV_8_TO_YUVJ\n");
  printf("#define HAVE_RGB_16_TO_RGB_24\n");
  printf("#define HAVE_RGB_16_TO_RGB_48\n");
  printf("#define HAVE_RGB_16_TO_RGB_FLOAT\n");

  printf("#define HAVE_RGB_TO_YUV\n");
  printf("#define HAVE_RGB_TO_YUVJ\n");

  printf("#define HAVE_YUV_TO_RGB\n");
  printf("#define HAVE_YUVJ_TO_RGB\n");

  printf("#define HAVE_YUV_TO_RGB_FLOAT\n");
  printf("#define HAVE_YUVJ_TO_RGB_FLOAT\n");
  
  printf("#endif // GAVL\n");
  
  
  /* JPEG Quantisation <-> MPEG Quantisation */

  printf("#ifdef HAVE_YUVJ_TO_YUV_8\n\n");
    
  /* yj_8 -> y_8 */
  printf("static uint8_t yj_8_to_y_8[256] = \n{\n");
  for(i = 0; i < 256; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i) / 255.0)*219.0 + 16.0;
    tmp_int   = (int)(tmp_float+0.5);
    printf("0x%02x, ", tmp_int);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  /* uvj_8 -> uv_8 */
  printf("static uint8_t uvj_8_to_uv_8[256] = \n{\n");
  for(i = 0; i < 256; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i-128) / 255.0)*224.0 + 128.0;
    tmp_int   = (int)(tmp_float+0.5);
    printf("0x%02x, ", tmp_int);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_YUVJ_TO_YUV_8\n\n");
  
  /* yj_8 -> y_16 */

  printf("#ifdef HAVE_YUVJ_TO_YUV_16\n\n");

  printf("static uint16_t yj_8_to_y_16[256] = \n{\n");
  for(i = 0; i < 256; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i) / 255.0)*219.0 + 16.0;
    tmp_int   = (int)(tmp_float*256.0+0.5);
    printf("0x%04x, ", tmp_int);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  /* uvj_8 -> uv_16 */
  printf("static uint16_t uvj_8_to_uv_16[256] = \n{\n");
  for(i = 0; i < 256; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i-128) / 255.0)*224.0 + 128.0;
    tmp_int   = (int)(tmp_float*256.0+0.5);
    printf("0x%04x, ", tmp_int);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_YUVJ_TO_YUV_16\n\n");
  
  /* y_8 -> yj_8 */

  printf("#ifdef HAVE_YUV_8_TO_YUVJ\n\n");

  printf("static uint8_t y_8_to_yj_8[256] = \n{\n");
  for(i = 0; i < 256; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i - 16) / 219.0)*255.0;
    tmp_int   = (int)(tmp_float+0.5);
    RECLIP(tmp_int, 0, 255);
    printf("0x%02x, ", tmp_int);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  /* uvj_8 -> uv_8 */
  printf("static uint8_t uv_8_to_uvj_8[256] = \n{\n");
  for(i = 0; i < 256; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i-128) / 224.0)*255.0 + 128.0;
    tmp_int   = (int)(tmp_float+0.5);
    RECLIP(tmp_int, 0, 255);
    printf("0x%02x, ", tmp_int);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_YUV_8_TO_YUVJ\n\n");

  /* RGB 5/6 bit -> 8 bit */

  printf("#ifdef HAVE_RGB_16_TO_RGB_24\n\n");
    
  printf("static uint8_t rgb_5_to_8[32] = \n{\n");
  for(i = 0; i < 32; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i) / 31.0 * 255.0);
    tmp_int   = (int)(tmp_float+0.5);
    printf("0x%02x, ", tmp_int);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static uint8_t rgb_6_to_8[64] = \n{\n");
  for(i = 0; i < 64; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i) / 63.0 * 255.0);
    tmp_int   = (int)(tmp_float+0.5);
    printf("0x%02x, ", tmp_int);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_RGB_16_TO_RGB_24\n\n");

  /* RGB 5/6 bit -> 16 bit */

  printf("#ifdef HAVE_RGB_16_TO_RGB_48\n\n");

  printf("static uint16_t rgb_5_to_16[32] = \n{\n");
  for(i = 0; i < 32; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i) / 31.0 * 65535.0);
    tmp_int   = (int)(tmp_float+0.5);
    printf("0x%04x, ", tmp_int);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static uint16_t rgb_6_to_16[64] = \n{\n");
  for(i = 0; i < 64; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i) / 63.0 * 65535.0);
    tmp_int   = (int)(tmp_float+0.5);
    printf("0x%04x, ", tmp_int);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_RGB_16_TO_RGB_48\n\n");
    
  /* RGB 5/6 bit -> float */

  printf("#ifdef HAVE_RGB_16_TO_RGB_FLOAT\n\n");

  printf("static float rgb_5_to_float[32] = \n{\n");
  for(i = 0; i < 32; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i) / 31.0);
    printf("%8.6f, ", tmp_float);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static float rgb_6_to_float[64] = \n{\n");
  for(i = 0; i < 64; i++)
    {
    if(!((i)%8))
      printf("  ");
    tmp_float = ((float)(i) / 63.0);
    printf("%8.6f, ", tmp_float);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_RGB_16_TO_RGB_FLOAT\n\n");
    
  printf("/* RGB -> YUV conversions */\n");

  printf("#ifdef HAVE_RGB_TO_YUV\n\n");
    
  printf("static int r_to_y[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)((0.29900*219.0/255.0)*0x10000 * i + 16 * 0x10000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int g_to_y[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)((0.58700*219.0/255.0)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int b_to_y[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)((0.11400*219.0/255.0)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int r_to_u[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-(0.16874*224.0/255.0)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");
  
  printf("static int g_to_u[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-(0.33126*224.0/255.0)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int b_to_u[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)( (0.50000*224.0/255.0)*0x10000 * i + 0x800000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");
    
  printf("static int r_to_v[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)( (0.50000*224.0/255.0)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int g_to_v[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-(0.41869*224.0/255.0)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int b_to_v[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-(0.08131*224.0/255.0)*0x10000 * i + 0x800000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_RGB_TO_YUV\n\n");

  printf("#ifdef HAVE_RGB_TO_YUVJ\n\n");
  
  printf("static int r_to_yj[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)((0.29900)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int g_to_yj[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)((0.58700)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int b_to_yj[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)((0.11400)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");
    
  printf("static int r_to_uj[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-(0.16874)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int g_to_uj[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-(0.33126)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int b_to_uj[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)( (0.50000)*0x10000 * i + 0x800000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");
    
  printf("static int r_to_vj[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)( (0.50000)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int g_to_vj[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-(0.41869)*0x10000 * i + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int b_to_vj[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-(0.08131)*0x10000 * i + 0x800000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_RGB_TO_YUVJ\n\n");
    
  printf("/* YUV -> RGB conversions */\n");

  // YCbCr (8bit) -> R'G'B' (integer) according to CCIR 601

  printf("#ifdef HAVE_YUV_TO_RGB\n\n");
 
  printf("static int y_to_rgb[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    
    printf("%d, ", (int)(255.0/219.0*(i-16) * 0x10000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");
  
  printf("static int v_to_r[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)( 1.40200*255.0/224.0 * (i - 0x80) * 0x10000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int u_to_g[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-0.34414*255.0/224.0 * (i - 0x80) * 0x10000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int v_to_g[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-0.71414*255.0/224.0 * (i - 0x80) * 0x10000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int u_to_b[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)( 1.77200*255.0/224.0 * (i - 0x80) * 0x10000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_YUV_TO_RGB\n\n");
    
  /* JPEG Quantization */

  printf("#ifdef HAVE_YUVJ_TO_RGB\n\n");
  
  printf("static int yj_to_rgb[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(i * 0x10000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");
    
  printf("static int vj_to_r[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)( 1.40200 * (i - 0x80) * 0x10000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int uj_to_g[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-0.34414 * (i - 0x80) * 0x10000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int vj_to_g[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)(-0.71414 * (i - 0x80) * 0x10000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static int uj_to_b[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%d, ", (int)( 1.77200 * (i - 0x80) * 0x10000 + 0.5));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_YUVJ_TO_RGB\n\n");
  
  // YCbCr (8bit) -> R'G'B' (float) according to CCIR 601

  printf("#ifdef HAVE_YUV_TO_RGB_FLOAT\n\n");
    
  printf("static float y_to_rgb_float[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    
    printf("%f, ", 1.0/219.0*(i-16));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");
  
  printf("static float v_to_r_float[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%f, ",  1.40200/224.0 * (i - 0x80));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static float u_to_g_float[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%f, ", -0.34414/224.0 * (i - 0x80));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static float v_to_g_float[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%f, ", -0.71414/224.0 * (i - 0x80));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static float u_to_b_float[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%f, ",  1.77200/224.0 * (i - 0x80));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_YUV_TO_RGB_FLOAT\n\n");
    
  /* JPEG Quantization */

  printf("#ifdef HAVE_YUVJ_TO_RGB_FLOAT\n\n");
  
  printf("static float yj_to_rgb_float[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%f, ", (float)i/255.0);
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");
    
  printf("static float vj_to_r_float[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%f, ",  1.40200/255.0 * (i - 0x80));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static float uj_to_g_float[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%f, ", -0.34414/255.0 * (i - 0x80));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static float vj_to_g_float[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%f, ", -0.71414/255.0 * (i - 0x80));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("static float uj_to_b_float[256] = \n{\n");
  for(i = 0; i < 0x100; i++)
    {
    if(!((i)%8))
      printf("  ");
    printf("%f, ",  1.77200/255.0 * (i - 0x80));
    if(!((i+1)%8))
      printf("\n");
    }
  printf("};\n\n");

  printf("#endif // HAVE_YUVJ_TO_RGB_FLOAT\n\n");
  return 0;
  }
