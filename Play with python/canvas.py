record = [1,2,3,4]
try:
    record_ip = record[4]
except IndexError:
    print("new record")
    record_ip = "empty"

print("here")
print(record_ip)