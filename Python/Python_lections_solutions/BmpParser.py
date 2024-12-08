import struct
import sys

def parser():
    file_header = sys.stdin.buffer.read(14)
    if len(file_header) < 14:
        return "Not a Windows BMP"
    signature = file_header[:2].decode("ascii")
    if signature != "BM":
        return "Not a Windows BMP"
    file_size = struct.unpack("<I", file_header[2:6])[0]
    dib_header_size_data = sys.stdin.buffer.read(4)
    if len(dib_header_size_data) < 4:
        return "Incorrect header size"
    dib_header_size = struct.unpack("<I", dib_header_size_data)[0]
    known_dib_sizes = [12, 40, 52, 56, 64, 108, 124]
    if dib_header_size not in known_dib_sizes:
        return "Incorrect header size"
    dib_header = sys.stdin.buffer.read(dib_header_size - 4)
    if len(dib_header) < dib_header_size - 4:
        return "Incorrect header size"
    if dib_header_size == 12:
        width, height, planes, bpp = struct.unpack("<HHHH", dib_header[:8])
    else:
        width, height, planes, bpp = struct.unpack("<iiHH", dib_header[:12])
    if height < 0:
        height = -height
    compression = struct.unpack("<I", dib_header[12:16])[0]
    image_size = struct.unpack("<I", dib_header[16:20])[0]
    row_size = ((width * bpp + 31) // 32) * 4
    calculated_image_size = row_size * height
    pixel_array_offset = struct.unpack("<I", file_header[10:14])[0]
    expected_file_size = pixel_array_offset + image_size
    if file_size != expected_file_size:
        return "Incorrect size"
    if image_size == calculated_image_size + 2:
        padding = 2
    elif image_size == calculated_image_size:
        padding = 0
    else:
        return "Incorrect image size"


    mas = [abs(width), abs(height), bpp, compression, padding]
    return " ".join(map(str, mas))

print(parser())