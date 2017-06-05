import sys

print("This is a test.")
print("This is {} running on 3DS!".format(sys.version))
print("I know this is running kind of slowly, but here is 2^512:")
print(2**512)

with open("sdmc:/hello.txt","w") as f:
    f.write("hello!\n")
