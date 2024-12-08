import sys
import tarfile
import io

s = sys.stdin.read()
s = ''.join(s.split())
data = bytes.fromhex(s)
with tarfile.open(fileobj=io.BytesIO(data), mode="r") as tar:
    n = 0
    sm = 0
    for i in tar.getmembers():
        if i.isfile():
            n += 1
            sm += i.size
print(sm, n)
