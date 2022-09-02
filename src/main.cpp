#include <iostream>
#include <zlib.h>
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <cassert>

const std::uint32_t CHUNK = 16384;

int do_deflate(std::FILE* source, std::FILE* dest, int level) {
  z_stream stream;
  stream.zalloc = Z_NULL;
  stream.zfree = Z_NULL;
  stream.opaque = Z_NULL;
  int ret { deflateInit(&stream, level) };
  if (ret != Z_OK) {
    return ret;
  }
  int flush;
  do {
    unsigned char in[CHUNK], out[CHUNK];
    stream.avail_in = std::fread(in, 1, CHUNK, source);
    if (std::ferror(source)) {
      deflateEnd(&stream);
      return Z_ERRNO;
    }
    flush = std::feof(source) ? Z_FINISH : Z_NO_FLUSH;
    stream.next_in = in;
    do {
      stream.avail_out = CHUNK;
      stream.next_out = out;
      ret = deflate(&stream, flush);
      assert(ret != Z_STREAM_ERROR);
      std::uint32_t have { CHUNK - stream.avail_out };
      if (std::fwrite(out, 1, have, dest) != have || std::ferror(dest)) {
        deflateEnd(&stream);
        return Z_ERRNO;
      }
    } while (stream.avail_out == 0);
    assert(stream.avail_in == 0);
  } while (flush != Z_FINISH);
  assert(ret == Z_STREAM_END);
  deflateEnd(&stream);
  return Z_OK;
}

int do_inflate(std::FILE* source, std::FILE* dest) {
  unsigned char in[CHUNK], out[CHUNK];
  z_stream stream;
  stream.zalloc = Z_NULL;
  stream.zfree = Z_NULL;
  stream.opaque = Z_NULL;
  stream.avail_in = 0;
  stream.next_in = Z_NULL;
  int ret { inflateInit(&stream) };
  if (ret != Z_OK) {
    return ret;
  }
  do {
    stream.avail_in = std::fread(in, 1, CHUNK, source);
    if (ferror(source)) {
      inflateEnd(&stream);
      return Z_ERRNO;
    }
    if (stream.avail_in == 0) {
      break;
    }
    stream.next_in = in;
    do {
      stream.avail_out = CHUNK;
      stream.next_out = out;
      ret = inflate(&stream, Z_NO_FLUSH);
      switch (ret) {
      case Z_NEED_DICT:
        ret = Z_DATA_ERROR;
      case Z_DATA_ERROR:
      case Z_MEM_ERROR:
        inflateEnd(&stream);
        return ret;
      }
      uint32_t have { CHUNK - stream.avail_out };
      if (std::fwrite(out, 1, have, dest) != have || ferror(dest)) {
        inflateEnd(&stream);
        return Z_ERRNO;
      }
    } while (stream.avail_out == 0);
  } while (ret != Z_STREAM_END);
  inflateEnd(&stream);
  return Z_STREAM_END == ret ? Z_OK : Z_DATA_ERROR;
}

int main(int argc, char** argv) {
  if (argc != 4 || !(strncmp(argv[1], "inflate", 7) != 0 || strncmp(argv[1], "deflate", 7) != 0)) {
    std::cout << "05-zip-a-file deflate/inflate SOURCE_FILE DEST_FILE" << std::endl;
    return 0;
  }
  std::FILE* source { std::fopen(argv[2], "r") };
  if (source == NULL) {
    std::cout << strerror(errno) << std::endl;
    return -1;
  }
  std::FILE* dest { std::fopen(argv[3], "w") };
  if (dest == NULL) {
    std::cout << strerror(errno) << std::endl;
    std::fclose(source);
    return -1;
  }
  if (strncmp(argv[1], "inflate", 7) == 0) {
    int ret { do_inflate(source, dest) };
    if (ret != Z_OK) {
      std::cout << zError(ret) << std::endl;
      return ret;
    }
  } else {
    int ret { do_deflate(source, dest, 9) };
    if (ret != Z_OK) {
      std::cout << zError(ret) << std::endl;
      return ret;
    }
  }
  return 0;
}
