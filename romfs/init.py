import sys

print("This is a test.")
print("This is {} running on 3DS!".format(sys.version))
print("I know this is running kind of slowly, but here is 2^512:")
print(2**512)

with open("sdmc:/hello.txt","w") as f:
    f.write("hello!\n")

print("importing svc...")
import svc
print("svcGetSystemTick() = {}".format(svc.get_system_tick()))
res,timerHandle = svc.create_timer(0)
print("svcCreateTimer(0) = {},{}".format(res, timerHandle))
res,dup = svc.duplicate_handle(timerHandle)
print("svcDuplicateHandle({}) = {},{}".format(timerHandle, res, dup))

print("svcCloseHandle({}) = {}".format(dup, svc.close_handle(dup)))
print("svcCloseHandle({}) = {}".format(timerHandle, svc.close_handle(timerHandle)))
